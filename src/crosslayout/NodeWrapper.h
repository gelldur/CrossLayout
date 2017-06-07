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

	NodeWrapper& operator=(const NodeWrapper& node)
	{
		_node = node._node;
	}

	const Rect getBoundingBox()
	{
		assert(_node);
		return _node->getBoundingBox();
	}

	const Size getSize()
	{
		assert(_node);
		return _node->getSize();
	}

	void setSize(const Size& size)
	{
		assert(_node);
		_node->setSize(size);
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

private:
	wrap_t* _node = nullptr;
};

}
