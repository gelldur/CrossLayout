//
// Created by Dawid Drozd aka Gelldur on 07/11/16.
//

#pragma once

#include <2d/CCNode.h>

#include <crosslayout/NodeWrapper.h>

namespace CrossLayout
{

template<>
class NodeWrapper<cocos2d::Node>
{
public:
	using wrap_t = cocos2d::Node;

	constexpr static NodeWrapper wrap(wrap_t* const node)
	{
		return {node};
	}

	constexpr NodeWrapper(wrap_t* node)
			: _node(node)
	{
	}

	const Rect<float>& getBoundingBox()
	{
		auto cocosBox = _node->getBoundingBox();
		_box.point = {cocosBox.origin.x, cocosBox.origin.y};
		_box.size = {cocosBox.size.width, cocosBox.size.height};

		return _box;
	}

	void setPosition(const Point<float>& position)
	{
		_node->setPosition(position.x, position.y);
	}

	const Point<float>& getPosition()
	{
		_box.point.x = _node->getPosition().x;
		_box.point.y = _node->getPosition().y;
		return _box.point;
	}

	NodeWrapper getParent()
	{
		return {_node->getParent()};
	}

	bool hasParent(wrap_t* node)
	{
		return getParent()._node != nullptr;
	}

private:
	Rect<float> _box;
	wrap_t* const _node = nullptr;
};

}
