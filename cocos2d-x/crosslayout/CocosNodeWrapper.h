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

	constexpr static NodeWrapper<cocos2d::Node> wrap(wrap_t* const node)
	{
		return {node};
	}

	constexpr NodeWrapper(wrap_t* node)
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

	const Rect<float>& getBoundingBox()
	{
		assert(_node);
		auto cocosBox = _node->getBoundingBox();
		_box.point = {cocosBox.origin.x, cocosBox.origin.y};
		_box.size = {cocosBox.size.width, cocosBox.size.height};

		return _box;
	}

	void setPosition(const Point<float>& position)
	{
		assert(_node);
		auto anchor = _node->isIgnoreAnchorPointForPosition() ? cocos2d::Vec2{}
															  : _node->getAnchorPointInPoints();
		anchor.x *= _node->getScaleX();
		anchor.y *= _node->getScaleY();
		_node->setPosition(position.x + anchor.x, position.y + anchor.y);
	}

	const Point<float>& getPosition()
	{
		assert(_node);
		auto cocosBox = _node->getBoundingBox();
		_box.point = {cocosBox.origin.x, cocosBox.origin.y};
		_box.size = {cocosBox.size.width, cocosBox.size.height};
		return _box.point;
	}

	NodeWrapper getParent()
	{
		assert(_node);
		return {_node->getParent()};
	}

	NodeWrapper getChild(const std::string& tag)
	{
		assert(_node);
		return {_node->getChildByName(tag)};
	}

	bool isValid() const
	{
		return _node != nullptr;
	}

private:
	Rect<float> _box;
	wrap_t* _node = nullptr;
};

using CocosNodeWrapper = NodeWrapper<cocos2d::Node>;

}
