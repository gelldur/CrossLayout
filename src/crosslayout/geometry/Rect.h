//
// Created by Dawid Drozd aka Gelldur on 8/17/16.
//

#pragma once

#include "Point.h"
#include "Size.h"

namespace Dexode
{

template<class T>
class Rect
{
public:
	Point<T> point;
	Size<T> size;

	constexpr Rect(const Point<T>& point, const Size<T>& size)
			: point(point)
			, size(size)
	{
	}

	constexpr Rect(const T x = 0, const T y = 0, const T width = 0, const T height = 0)
			: point(x, y)
			, size(width, height)
	{
	}

	const T x() const
	{
		return point.x;
	}

	const T y() const
	{
		return point.y;
	}

	const T width() const
	{
		return size.width;
	}

	const T height() const
	{
		return size.height;
	}

	const T left() const
	{
		return point.x;
	}

	const T bottom() const
	{
		return point.y;
	}

	const T right() const
	{
		return point.x + size.width;
	}

	const T top() const
	{
		return point.y + size.height;
	}

	/**
	 * @param xAnchor value from 0 to 1. Simple: point.x + (width() * xAnchor)
	 * @param yAnchor value from 0 to 1. Simple: point.y + (height() * yAnchor)
	 * @return point scaled by anchor
	 */
	const Point<T> getPoint(float xAnchor, float yAnchor) const
	{
		return point + Point<float>{width() * xAnchor, height() * yAnchor};
	}
};

}
