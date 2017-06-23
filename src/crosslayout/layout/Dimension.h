//
// Created by Dawid Drozd aka Gelldur on 22.06.17.
//
#pragma once

#include <crosslayout/ComposerCocos.h>
#include <crosslayout/CocosNodeWrapper.h>

class Dimension
{
	using SizeMember = float CrossLayout::Size<float>::*;
public:
	enum class Policy
	{
		exact, wrapContent, screenPercent, scaled, parentPercent
	};

	Dimension(CrossLayout::CocosNodeWrapper node);
	void setPolicy(Policy width, Policy height);
	void setSize(CrossLayout::Size<float> size);

	void update(float scale, const CrossLayout::Size<float>& screenSize);

	CrossLayout::Size<float> getSize();
private:
	static float _scale;
	static CrossLayout::Size<float> _screenSize;

	Policy _width = Policy::exact;
	Policy _height = Policy::exact;
	CrossLayout::CocosNodeWrapper _node;
	CrossLayout::Size<float> _size;

	void updateSize(Policy policy, CrossLayout::Size<float>& size, SizeMember prime, SizeMember second);
};


