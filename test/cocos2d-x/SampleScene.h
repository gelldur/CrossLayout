//
// Created by Dawid Drozd aka Gelldur on 08/01/17.
//
#pragma once

#include <cocos2d.h>

class SampleScene : public cocos2d::CCScene
{
	using inherited = cocos2d::CCScene;
public:
	CREATE_FUNC(SampleScene);
	virtual bool init() override;
};


