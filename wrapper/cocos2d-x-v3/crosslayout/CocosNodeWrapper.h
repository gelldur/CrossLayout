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
	using Rect = CrossLayout::Rect<float>;
	using Size = CrossLayout::Size<float>;
	using Point = CrossLayout::Point<float>;
	using wrap_t = cocos2d::Node;

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
		return {_node->getBoundingBox()};
	}

	const Size getSize()
	{
		assert(_node);
		return {_node->getContentSize()};//TODO is it a bug? Should be box size?
	}

	void setSize(const Size& size)
	{
		assert(_node);
		_node->setContentSize({size.width, size.height});
	}

	void setPosition(const Point& position)
	{
		assert(_node);
		auto anchor = cocos2d::Vec2{};
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
		assert(_node);
		auto cocosBox = _node->getBoundingBox();
		_box.point = {cocosBox.origin.x, cocosBox.origin.y};
		_box.size = {cocosBox.size.width, cocosBox.size.height};
		return _box.point;
	}

	const Size getParentSize()
	{
		assert(_node);
		return {_node->getParent()->getContentSize()};
	}

	bool isValid() const
	{
		return _node != nullptr;
	}

private:
	wrap_t* _node = nullptr;
};

using CocosNodeWrapper = NodeWrapper<cocos2d::Node>;

}
