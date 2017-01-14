//
// Created by Dawid Drozd aka Gelldur on 07/11/16.
//

#pragma once

#include <crosslayout/geometry/Rect.h>

namespace CrossLayout
{

/**
 * Explicity implement NodeWrapper specialization if you need to.
 * Checkout cocos2d-x/crosslayout/CocosNodeWrapper.h
 */
template<class T>
class NodeWrapper
{
public:
	using wrap_t = T;

	constexpr static NodeWrapper wrap(wrap_t* const node)
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
	}

	const Rect<float>& getBoundingBox()
	{
		assert(_node);
		return _node->getBoundingBox();
	}

	void setPosition(const Point<float>& position)
	{
		assert(_node);
		_node->setPosition(position);
	}

	const Point<float>& getPosition()
	{
		assert(_node);
		return _node->getPosition();
	}

	NodeWrapper getParent()
	{
		assert(_node);
		return {_node->getParent()};
	}

	NodeWrapper getChild(const std::string& tag)
	{
		assert(_node);
		return {_node->getChild(tag)};
	}

	bool isValid() const
	{
		return _node != nullptr;
	}

private:
	wrap_t* _node = nullptr;
};

}
