//
// Created by Dawid Drozd aka Gelldur on 07/11/16.
//

#pragma once

#include <crosslayout/geometry/Rect.h>

namespace CrossLayout
{

/**
 * Explicity implement NodeWrapprt specialization if you need to.
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

	const Rect<float>& getBoundingBox()
	{
		return _node->getBoundingBox();
	}

	void setPosition(const Point<float>& position)
	{
		_node->setPosition(position);
	}

	const Point<float>& getPosition()
	{
		return _node->getPosition();
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
	wrap_t* const _node = nullptr;
};

}
