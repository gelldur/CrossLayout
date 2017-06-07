//
// Created by Dawid Drozd aka Gelldur on 8/17/16.
//

#pragma once

namespace CrossLayout
{

template<class T>
class Size
{
public:
	T width;
	T height;

	constexpr Size(T width = 0, T height = 0)
			: width(width)
			, height(height)
	{
	}

	template<class From>
	constexpr Size(const From& from)
			: width(from.width)
			, height(from.height)
	{
	}

	Size<T>& operator+=(const CrossLayout::Size<T>& right)
	{
		width += right.width;
		height += right.height;
		return *this;
	}
};

template<class T>
bool operator<(const CrossLayout::Size<T>& left, const CrossLayout::Size<T>& right)
{
	return left.width < right.width || left.height < right.height;
}

template<class T>
bool operator==(const CrossLayout::Size<T>& left, const CrossLayout::Size<T>& right)
{
	return left.width == right.width && left.height == right.height;
}

template<class T>
bool operator!=(const CrossLayout::Size<T>& left, const CrossLayout::Size<T>& right)
{
	return !(left == right);
}

}
