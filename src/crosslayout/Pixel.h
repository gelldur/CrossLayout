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

	static constexpr Pixel shp(float value)
	{
		return {value, &CrossLayout::Pixel::convertShpToPixel};
	}

	static constexpr Pixel swp(float value)
	{
		return {value, &CrossLayout::Pixel::convertSwpToPixel};
	}

	operator int() const
	{
		return (*_defaultConvert)(_value);
	}

	operator float() const
	{
		return (*_defaultConvert)(_value);
	}

	Pixel operator-() const
	{
		return {-_value, _defaultConvert};
	}

	static const int convertDpToPixel(const float dp)
	{
		return dp * _screenDpi / 160.F;
	}

	static const int convertSwpToPixel(const float swp)
	{
		return swp * _screenWidth / 100.F;
	}

	static const int convertShpToPixel(const float shp)
	{
		return shp * _screenHeight / 100.F;
	}

	static void setDeviceDPI(const int dpi);
	static void setScreenSize(const int width, const int height);

private:
	static int _screenDpi;
	static int _screenWidth;
	static int _screenHeight;

	float _value;
	Converter _defaultConvert;
};

}

//Userdefined literals: http://en.cppreference.com/w/cpp/language/user_literal
constexpr inline CrossLayout::Pixel operator "" _dp(const long double densityIndependentPixel)
{
	return CrossLayout::Pixel(static_cast<float>(densityIndependentPixel), &CrossLayout::Pixel::convertDpToPixel);
}

constexpr inline CrossLayout::Pixel operator "" _dp(const unsigned long long int densityIndependentPixel)
{
	return CrossLayout::Pixel(static_cast<int>(densityIndependentPixel), &CrossLayout::Pixel::convertDpToPixel);
}

constexpr inline CrossLayout::Pixel operator "" _swp(const long double screenWidthPercent)
{
	return CrossLayout::Pixel(static_cast<float>(screenWidthPercent), &CrossLayout::Pixel::convertSwpToPixel);
}

constexpr inline CrossLayout::Pixel operator "" _swp(const unsigned long long int screenWidthPercent)
{
	return CrossLayout::Pixel(static_cast<float>(screenWidthPercent), &CrossLayout::Pixel::convertSwpToPixel);
}

constexpr inline CrossLayout::Pixel operator "" _shp(const long double screenHeightPercent)
{
	return CrossLayout::Pixel(static_cast<float>(screenHeightPercent), &CrossLayout::Pixel::convertShpToPixel);
}

constexpr inline CrossLayout::Pixel operator "" _shp(const unsigned long long int screenHeightPercent)
{
	return CrossLayout::Pixel(static_cast<float>(screenHeightPercent), &CrossLayout::Pixel::convertShpToPixel);
}
