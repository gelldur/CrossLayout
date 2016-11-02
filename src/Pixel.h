//
// Created by Dawid Drozd aka Gelldur on: Dec 7, 2014
//

#pragma once

namespace CrossLayout
{

class Pixel
{
public:
	using Converter = const int (*)(const float);

	constexpr Pixel(float value, Converter defaultConverter)
			: _value(value)
			, _defaultConvert(defaultConverter)
	{
	}

	operator int() const
	{
		return (*_defaultConvert)(_value);
	}

	static const int convertDpToPixel(const float dp)
	{
		return dp * _screenDpi / 160.F;
	}

	static const int convertSwpToPixel(const float swp)
	{
		return swp * _screenWidth / 100.F;
	}

	static void setDeviceDPI(const int dpi);
	static void setScreenWidth(const int width);

private:
	static int _screenDpi;
	static int _screenWidth;

	const float _value;
	const Converter _defaultConvert;
};

}

// @formatter:off
//Userdefined literals: http://en.cppreference.com/w/cpp/language/user_literal
constexpr inline CrossLayout::Pixel operator "" _dp(const long double densityIndependentPixel)
{
	return CrossLayout::Pixel(static_cast<float>(densityIndependentPixel),&CrossLayout::Pixel::convertDpToPixel);
}
constexpr inline CrossLayout::Pixel operator "" _dp(const unsigned long long int densityIndependentPixel)
{
	return CrossLayout::Pixel(static_cast<int>(densityIndependentPixel),&CrossLayout::Pixel::convertDpToPixel);
}

constexpr inline CrossLayout::Pixel operator "" _swp(const long double screenWidthPercent)
{
	return CrossLayout::Pixel(static_cast<float>(screenWidthPercent),&CrossLayout::Pixel::convertSwpToPixel);
}
constexpr inline CrossLayout::Pixel operator "" _swp(const unsigned long long int screenWidthPercent)
{
	return CrossLayout::Pixel(static_cast<float>(screenWidthPercent),&CrossLayout::Pixel::convertSwpToPixel);
}
// @formatter:on
