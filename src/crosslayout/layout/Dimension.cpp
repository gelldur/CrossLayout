//
// Created by Dawid Drozd aka Gelldur on 22.06.17.
//
#include "Dimension.h"
//////////////////////////////////

Dimension::Dimension(CrossLayout::CocosNodeWrapper node)
		: _node(std::move(node))
{
}

void Dimension::setPolicy(Dimension::Policy width, Dimension::Policy height)
{
	_width = width;
	_height = height;
}

void Dimension::setSize(CrossLayout::Size<float> size)
{
	_size = size;
}

CrossLayout::Size<float> Dimension::getSize()
{
	auto size = _size;
	updateSize(_width, size, &CrossLayout::Size<float>::width, &CrossLayout::Size<float>::height);
	updateSize(_height, size, &CrossLayout::Size<float>::height, &CrossLayout::Size<float>::width);
	return size;
}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "DuplicateSwitchCase"

void Dimension::updateSize(Dimension::Policy policy
						   , CrossLayout::Size<float>& size
						   , SizeMember prime
						   , SizeMember second)
{
	switch (policy)
	{

		case Policy::exact:
			//Skip
			break;
		case Policy::wrapContent:
			break;
		case Policy::screenPercent:
			size.*prime *= _screenSize.*prime;
			break;
		case Policy::scaled:
			size.*prime *= _scale;
			break;
		case Policy::parentPercent:
			size.*prime *= _node.getParentSize().*prime;
			break;
		default:
			assert(false && "Missing something ?");
			break;
	}
}

void Dimension::update(float scale, const CrossLayout::Size<float>& screenSize)
{
	_scale = scale;
	_screenSize = screenSize;
}

#pragma clang diagnostic pop
