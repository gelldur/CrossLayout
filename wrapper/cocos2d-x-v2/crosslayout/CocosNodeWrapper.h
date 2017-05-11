//
// Created by Dawid Drozd aka Gelldur on 11.05.17.
//

#pragma once

#include <functional>

#include <base_nodes/CCNode.h>

#include <crosslayout/NodeWrapper.h>

namespace CrossLayout
{

template<>
class NodeWrapper<cocos2d::CCNode>
{
public:
	using wrap_t = cocos2d::CCNode;

	constexpr static NodeWrapper<cocos2d::CCNode> wrap(wrap_t* const node)
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
		auto cocosBox = _node->boundingBox();
		_box.point = {cocosBox.origin.x, cocosBox.origin.y};
		_box.size = {cocosBox.size.width, cocosBox.size.height};

		return _box;
	}

	const Size<float>& getSize()
	{
		assert(_node);
		_box.size = {_node->getContentSize().width, _node->getContentSize().height};
		return _box.size;
	}

	void setPosition(const Point<float>& position)
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

	const Point<float>& getPosition()
	{
		assert(_node);
		auto cocosBox = _node->boundingBox();
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
		return {_node->getChildByTag(std::hash<std::string>{}(tag))};
	}

	bool isValid() const
	{
		return _node != nullptr;
	}

private:
	Rect<float> _box;
	wrap_t* _node = nullptr;
};

using CocosNodeWrapper = NodeWrapper<cocos2d::CCNode>;

}
