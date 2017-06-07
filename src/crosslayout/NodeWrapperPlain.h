//
// Created by Dawid Drozd aka Gelldur on 06.06.17.
//
#pragma once

#include <memory>

#include <crosslayout/NodeWrapper.h>

namespace CrossLayout
{

template<>
class NodeWrapper<CrossLayout::Rect<float>>
{
public:
	using Rect = CrossLayout::Rect<float>;
	using Size = CrossLayout::Size<float>;
	using Point = CrossLayout::Point<float>;

	NodeWrapper()
	{
	}

	NodeWrapper(Rect node, Size parent = {})
			: _node(new Rect(node))
			, _parent(parent)
	{
	}

	NodeWrapper(const NodeWrapper& node)
			: _node(node._node)
			, _parent(node._parent)
	{
	}

	NodeWrapper& operator=(const NodeWrapper& node)
	{
		_node = node._node;
		_parent = node._parent;
		return *this;
	}

	const Rect getBoundingBox()
	{
		assert(_node);
		return *_node;
	}

	const Size getSize()
	{
		assert(_node);
		return _node->size;
	}

	void setSize(const Size& size)
	{
		assert(_node);
		_node->size = size;
	}

	void setPosition(const Point& position)
	{
		assert(_node);
		_node->point = position;
	}

	const Point getPosition()
	{
		assert(_node);
		return _node->point;
	}

	const Size getParentSize()
	{
		return _parent;
	}

	bool isValid() const
	{
		return _node != nullptr;
	}

private:
	std::shared_ptr<Rect> _node;
	Size _parent;
};

}
