//
// Created by Dawid Drozd aka Gelldur on 06.06.17.
//
#include "Linear.h"
//////////////////////////////////

#include <crosslayout/Composer.h>

namespace CrossLayout
{
namespace Layout
{

void Linear::setOrientation(Linear::Orientation orientation)
{
	_orientation = orientation;
}

void Linear::setGravity(int gravity)
{
	_gravity = gravity;
}

void Linear::setAvailableSpace(Size size)
{
	_availableSize = size;
}

void Linear::layout()
{
	if (_items.empty())
	{
		return;
	}
	//set default
	if ((_gravity & Gravity::centerHorizontal) == 0)
	{
		_gravity |= Gravity::left;
	}
	if ((_gravity & Gravity::centerVertical) == 0)
	{
		_gravity |= Gravity::top;
	}

	onMeasure();
	onLayout();
}

void Linear::onMeasure()
{
	_itemsTotalSize = {};
	assert(_items.size() == _margins.size());
	for (uint i = 0; i < _items.size(); ++i)
	{
		_items[i] = {_items[i].getBoundingBox(), _availableSize};
		auto size = _items[i].getSize();
		size.width += (_margins[i].left + _margins[i].right);
		size.height += (_margins[i].top + _margins[i].bottom);
		_itemsTotalSize += size;
	}
}

void Linear::onLayout()
{
	if (_orientation == Orientation::horizontal)
	{
		onLayoutHorizontal();
	}
	else
	{
		onLayoutVertical();
	}
}

void Linear::onLayoutHorizontal()
{
	CrossLayout::Composer<Rect> composer;
	if ((_gravity & Gravity::centerVertical) == Gravity::centerVertical)
	{
		for (uint i = 0; i < _items.size(); ++i)
		{
			//TODO composer could return position?
			composer.center(_items[i]).inParent().vertically(_margins[i].top - _margins[i].bottom);
		}
	}
	else if ((_gravity & Gravity::top) != 0)
	{
		for (uint i = 0; i < _items.size(); ++i)
		{
			composer.topEdge(_items[i]).moveTo().parentTopEdge(_margins[i].top);
		}
	}
	else if ((_gravity & Gravity::bottom) != 0)
	{
		for (uint i = 0; i < _items.size(); ++i)
		{
			composer.bottomEdge(_items[i]).moveTo().parentBottomEdge(_margins[i].bottom);
		}
	}

	float offset = 0;
	if ((_gravity & Gravity::centerHorizontal) == Gravity::centerHorizontal)
	{
		offset = (_availableSize.width - _itemsTotalSize.width) / 2.F;
	}
	else if ((_gravity & Gravity::left) != 0)
	{
		offset = _margins.front().left;
	}
	else if ((_gravity & Gravity::right) != 0)
	{
		offset = (_availableSize.width - _itemsTotalSize.width) + _margins.front().left;
	}

	composer.leftEdge(_items.front()).moveTo().parentLeftEdge(offset);

	for (uint i = 1; i < _items.size(); ++i)
	{
		composer.leftEdge(_items[i]).moveTo().rightEdge(_items[i - 1], _margins[i - 1].right + _margins[i].left);
	}

	updatePositions();
}

void Linear::onLayoutVertical()
{
	CrossLayout::Composer<Rect> composer;
	if ((_gravity & Gravity::centerHorizontal) == Gravity::centerHorizontal)
	{
		for (uint i = 0; i < _items.size(); ++i)
		{
			//TODO composer could return position?
			composer.center(_items[i]).inParent().horizontally(_margins[i].left - _margins[i].right);
		}
	}
	else if ((_gravity & Gravity::left) != 0)
	{
		for (uint i = 0; i < _items.size(); ++i)
		{
			composer.leftEdge(_items[i]).moveTo().parentLeftEdge(_margins[i].left);
		}
	}
	else if ((_gravity & Gravity::right) != 0)
	{
		for (uint i = 0; i < _items.size(); ++i)
		{
			composer.rightEdge(_items[i]).moveTo().parentRightEdge(_margins[i].right);
		}
	}

	float offset = 0;
	if ((_gravity & Gravity::centerVertical) == Gravity::centerVertical)
	{
		offset = (_availableSize.height - _itemsTotalSize.height) / 2.F;
	}
	else if ((_gravity & Gravity::top) != 0)
	{
		offset = _margins.front().top;
	}
	else if ((_gravity & Gravity::bottom) != 0)
	{
		offset = (_availableSize.height - _itemsTotalSize.height) + _margins.front().top;
	}

	composer.topEdge(_items.front()).moveTo().parentTopEdge(offset);

	for (uint i = 1; i < _items.size(); ++i)
	{
		composer.topEdge(_items[i]).moveTo().bottomEdge(_items[i - 1], _margins[i - 1].bottom + _margins[i].top);
	}

	updatePositions();
}

bool Linear::validate() const
{
	return true;
}

NodeGroup Linear::getNodePack()
{
	NodeGroup group;
	for (uint i = 0; i < _items.size(); ++i)
	{
		auto box = _items[i].getBoundingBox();
//		box.point.x -= _margins[i].left;
//		box.point.y -= _margins[i].top;
//		box.size.width += _margins[i].right;
//		box.size.height += _margins[i].bottom;
		group.add(box, _updatePositions[i]);
	}
	group.setBox({{}, _availableSize});
	return group;
}

void Linear::layout(Size size)
{
	setAvailableSpace(size);
	layout();
}

void Linear::updatePositions()
{
	for (uint i = 0; i < _items.size(); ++i)
	{
		_updatePositions[i](_items[i].getPosition());
	}
}

Linear::Size Linear::getSize()
{
	return _availableSize;
}

Linear::Orientation Linear::getOrientation() const
{
	return _orientation;
}

int Linear::getGravity() const
{
	return _gravity;
}

}
}
