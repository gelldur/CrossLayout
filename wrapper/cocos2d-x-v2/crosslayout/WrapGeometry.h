//
// Created by Dawid Drozd aka Gelldur on 06.06.17.
//
#pragma once

#include <crosslayout/geometry/Rect.h>

#include <cocoa/CCGeometry.h>

namespace CrossLayout
{

//cpp doesn't support partly specialized templates
template<>
template<>
inline Rect<float>::Rect(const cocos2d::CCRect& from)
		: point{from.origin}
		, size{from.size}
{
}

}
