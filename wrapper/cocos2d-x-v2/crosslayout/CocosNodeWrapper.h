//
// Created by Dawid Drozd aka Gelldur on 11.05.17.
//

#pragma once

#include <base_nodes/CCNode.h>

#include <crosslayout/NodeWrapper.h>

#include "WrapGeometry.h"

namespace CrossLayout
{

template<>
class NodeWrapper<cocos2d::CCNode>
{
public:
	using Rect = CrossLayout::Rect<float>;
	using Size = CrossLayout::Size<float>;
	using Point = CrossLayout::Point<float>;
	using wrap_t = cocos2d::CCNode;

	constexpr static NodeWrapper<cocos2d::CCNode> wrap(wrap_t* const node)
	{
		return {node};
	}

	constexpr NodeWrapper(wrap_t* node = nullptr)
			: _node(node)
	{
	}

	constexpr NodeWrapper(const NodeWrapper& node)
			: _node(node._node)
	{
	}

	NodeWrapper& operator=(const NodeWrapper& node)
	{
		_node = node._node;
		return *this;
	}

	const Rect getBoundingBox()
	{
		assert(_node);
		return {_node->boundingBox()};
	}

	const Size getParentSize()
	{
		assert(_node);
		return {_node->getParent()->getContentSize()};
	}

	void setPosition(const Point& position)
	{
		assert(_node);
		auto anchor = cocos2d::CCPoint{};
		if (_node->isIgnoreAnchorPointForPosition() == false)
		{
			anchor = _node->getAnchorPointInPoints();
			anchor.x *= _node->getScaleX();
			anchor.y *= _node->getScaleY();
		}
		_node->setPosition(position.x + anchor.x, position.y + anchor.y);
	}

	const Point getPosition()
	{
		//Position isn't the same as getBoundingBox().point
		//position is more raw thing
		const auto position = _node->getPosition();
		if (_node->isIgnoreAnchorPointForPosition() == false)
		{
			auto anchor = _node->getAnchorPointInPoints();
			anchor.x *= _node->getScaleX();
			anchor.y *= _node->getScaleY();
			return position - anchor;
		}
		return position;
	}

	bool isValid() const
	{
		return _node != nullptr;
	}

	void* getAddress() const
	{
		return _node;
	}

private:
	wrap_t* _node = nullptr;
};

using CocosNodeWrapper = NodeWrapper<cocos2d::CCNode>;

}
