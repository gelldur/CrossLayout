//
// Created by Dawid Drozd aka Gelldur on 9/27/16.
//
#include "Pixel.h"

namespace CrossLayout
{
int Pixel::_screenDpi = 0;
int Pixel::_screenWidth = 0;

void Pixel::setDeviceDPI(const int dpi)
{
	_screenDpi = dpi;
}

void Pixel::setScreenWidth(const int width)
{
	_screenWidth = width;
}
}
