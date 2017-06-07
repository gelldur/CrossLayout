//
// Created by Dawid Drozd aka Gelldur on 06.06.17.
//
#pragma once

#include <cassert>
#include <vector>
#include <functional>

#include <crosslayout/NodeWrapper.h>
#include "Composer.h"

namespace CrossLayout
{

class NodeGroup //TODO change to NodePack?
{
public:
	using Rect = CrossLayout::Rect<float>;
	using Size = CrossLayout::Size<float>;
	using Point = CrossLayout::Point<float>;

	NodeGroup& add(Rect item, std::function<void(const Point&)> updatePositionCallback)
	{
		if (_nodes.empty())
		{
			_box = item;
		}
		else
		{
			_box = _box.merge(item);
		}

		_nodes.emplace_back(std::move(item));
		_updatePositions.emplace_back(std::move(updatePositionCallback));
		return *this;
	}

	void setBox(const Rect& box)
	{
		_box = box;
	}

	const Rect& getBoundingBox()
	{
		return _box;
	}

	const Size& getSize()
	{
		return _box.size;
	}

	void setPosition(const Point& position)
	{
		const auto offset = position - _box.point;
		_box.point = position;
		for (unsigned i = 0; i < _nodes.size(); ++i)
		{
			_nodes[i].point += offset;
			_updatePositions[i](_nodes[i].point);
		}
	}

	const Point& getPosition()
	{
		return getBoundingBox().point;
	}

	bool isValid() const
	{
		return _nodes.empty() == false;
	}

private:
	Rect _box;
	std::vector<Rect> _nodes;
	std::vector<std::function<void(const Point&)>> _updatePositions;
};

}

