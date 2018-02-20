//
// Created by Dawid Drozd aka Gelldur on 07/11/16.
//

#pragma once

#include <cassert>
#include <crosslayout/geometry/Rect.h>

namespace CrossLayout
{

/**
 * Explicity implement NodeWrapper specialization if you need to.
 * Checkout wrapper/cocos2d-x-v2/crosslayout/CocosNodeWrapper.h
 * or
 * crosslayout/NodeWrapperPlain.h
 */
template<class T>
class NodeWrapper
{
public:
	using Rect = CrossLayout::Rect<float>;
	using Size = CrossLayout::Size<float>;
	using Point = CrossLayout::Point<float>;
	using wrap_t = T;

	constexpr NodeWrapper(wrap_t* node = nullptr)
			: _node(node)
	{
	}

	constexpr NodeWrapper(const NodeWrapper& node)
			: _node(node._node)
	{
	}

	constexpr NodeWrapper(NodeWrapper&& node)
		: _node(node._node)
	{
	}

	NodeWrapper& operator=(const NodeWrapper& node)
	{
		_node = node._node;
		return *this;
	}

	/**
	 * Bounding box is box that will contain our whole content. Simply bounding box takes
	 * into account things like: rotation, scale, scale by parent hierarchy other transformations
	 *
	 * Simply this is rect that we will see on screen
	 * @return rect that will say how much space we take
	 */
	const Rect getBoundingBox()
	{
		assert(_node);
		return _node->getBoundingBox();
	}

	void setPosition(const Point& position)
	{
		assert(_node);
		_node->setPosition(position);
	}

	const Point getPosition()
	{
		assert(_node);
		return _node->getPosition();
	}

	const Size getParentSize()
	{
		assert(_node);
		return {_node->getParent()->getSize()};
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

}
