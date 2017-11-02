//
// Created by Dawid Drozd aka Gelldur on 8/17/16.
//

#pragma once

#include "Point.h"
#include "Size.h"
#include <algorithm>

namespace CrossLayout
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

	template<class From>
	constexpr Rect(const From& from)
			: point(from.point)
			, size(from.size)
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

	/**
	 * Compute the min rect which can contain this and rect, assign it to this.
	 */
	Rect merge(const Rect& other) const
	{
		const float minX = std::min(point.x, other.point.x);
		const float minY = std::min(point.y, other.point.y);
		const float maxX = std::max(right(), other.right());
		const float maxY = std::max(top(), other.top());
		return {minX, minY, maxX - minX, maxY - minY};
	}

	bool operator==(const Rect<T>& other) const
	{
		return point == other.point &&
			   size == other.size;
	}

	bool operator!=(const Rect<T>& other) const
	{
		return !(other == *this);
	}

	Rect& operator=(const Rect<T>& other)
	{
		point = other.point;
		size = other.size;
		return *this;
	}
};

}
