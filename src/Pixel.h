//
// Created by Dawid Drozd aka Gelldur on: Dec 7, 2014
//

#pragma once

namespace CrossLayout
{

class Pixel
{
public:
	constexpr Pixel(int value)
			: _value(value)
	{
	}

	operator int() const
	{
		return convertDpToPixel(_value);
	}

	static const int convertDpToPixel(const int dp)
	{
		return dp * _screenDpi / 160.F;
	}

	static void setDeviceDPI(const int dpi);

private:
	static int _screenDpi;
	int _value;
};

}

// @formatter:off
//Userdefined literals: http://en.cppreference.com/w/cpp/language/user_literal
constexpr inline CrossLayout::Pixel operator "" _dp(const long double densityIndependentPixel)
{
	return CrossLayout::Pixel(static_cast<int>(densityIndependentPixel));
}
constexpr inline CrossLayout::Pixel operator "" _dp(const unsigned long long int densityIndependentPixel)
{
	return CrossLayout::Pixel(static_cast<int>(densityIndependentPixel));
}
// @formatter:on
