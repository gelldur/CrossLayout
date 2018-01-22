//
// Created by Dawid Drozd aka Gelldur on 07.06.17.
//
#pragma once

#include <base_nodes/CCNode.h>

#include <crosslayout/ComposerCocos.h>
#include <crosslayout/layout/Linear.h>

namespace CrossLayout
{
namespace Layout
{

class CocosLinear
{
public:
	using Rect = Linear::Rect;
	using Size = Linear::Size;
	using Point =Linear::Point;
	using Wrap = CrossLayout::ComposerCocos::Wrap;
	using Orientation = Linear::Orientation;
	using Gravity = Linear::Gravity;

	Linear linear;

	operator cocos2d::CCNode*() const { return _parent; }

	CocosLinear(cocos2d::CCNode* parent
				, Linear::Orientation orientation = Linear::Orientation::horizontal
				, int gravity = (Linear::Gravity::left | Linear::Gravity::top))
			: linear(orientation, gravity)
			, _parent(parent)
	{
	}

	CocosLinear(cocos2d::CCNode* parent, Size desiredSize
				, Linear::Orientation orientation = Linear::Orientation::horizontal
				, int gravity = (Linear::Gravity::left | Linear::Gravity::top))
			: linear(orientation, gravity)
			, _parent(parent)
			, _size(desiredSize)
	{
	}

	CocosLinear copy() const
	{
		return CocosLinear{_parent, _size, linear.getOrientation(), linear.getGravity()};
	}

	void add(cocos2d::CCNode* child, Margin margin = {})
	{
		_parent->addChild(child);
		linear.addItem<Wrap>(child, margin);
	}

	void remove(cocos2d::CCNode* node)
	{
		_parent->removeChild(node);
		linear.removeItem<Wrap>(node);
	}

	template<class N>
	void nest(N& layout)
	{
		linear.nest<N>(layout);
	}

	void layout()
	{
		layout(getSize());
	}

	void layout(Size size)
	{
		linear.layout(size);
	}

	NodeGroup getNodePack()
	{
		return linear.getNodePack();
	}

	Size getSize()
	{
		return _size == Size{} ? _parent->getContentSize() : _size;
	}

	//Helper method
	bool pleaseConsiderMeAsLayout()
	{
		return true;
	}

private:
	cocos2d::CCNode* _parent = nullptr;
	Size _size;
};

}
}
