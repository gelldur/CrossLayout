//
// Created by Dawid Drozd aka Gelldur on 14/01/17.
//
#pragma once

#include <ostream>

#include "Point.h"
#include "Size.h"
#include "Rect.h"

template<class T>
std::ostream& operator<<(std::ostream& stream, const CrossLayout::Point<T>& point)
{
	return stream << "Point (x=" << point.x << ", y=" << point.y << ")";
}

template<class T>
std::ostream& operator<<(std::ostream& stream, const CrossLayout::Rect<T>& rect)
{
	return stream << "Rect (" << rect.point << ", " << rect.size << ")";
}

template<class T>
std::ostream& operator<<(std::ostream& stream, const CrossLayout::Size<T>& size)
{
	return stream << "Size (width=" << size.width << ", height=" << size.height << ")";
}
