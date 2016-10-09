/*
 * Positioner.h
 *
 *  Created on: May 12, 2013
 *      Author: Dawid Drozd
 */
#pragma once

//Source code from: https://github.com/gelldur/GKoala/blob/master/src/Positioner.h
//Refactor this $hit :)
//Moved to coco2dx-v3

#include <cocos2d.h>

namespace CrossLayout
{

namespace Positioner
{

cocos2d::Point getLeftBottomCorner(cocos2d::Node* pNode);
cocos2d::Point getLeftTopCorner(cocos2d::Node* pNode);
cocos2d::Point getRightTopCorner(cocos2d::Node* pNode);
cocos2d::Point getRightBottomCorner(cocos2d::Node* pNode);

cocos2d::Point getCenterPoint(cocos2d::Node* pNode);
cocos2d::Point getCenterPoint(const cocos2d::Size& size);

void setCornerToPosition(cocos2d::Node* pNode, const cocos2d::Point& cornerPosition, const cocos2d::Point& position);

float getScaledWidth(cocos2d::Node* pNode);
float getScaledHeight(cocos2d::Node* pNode);
cocos2d::Size getScaledSize(cocos2d::Node* pNode);

void centerInParent(cocos2d::Node* pChildNode);
void leftEdge(cocos2d::Node* pChildNode, const float margin = 0);
void rightEdge(cocos2d::Node* pChildNode, const float margin = 0);
void topEdge(cocos2d::Node* pChildNode, const float margin = 0);
void bottomEdge(cocos2d::Node* pChildNode, const float margin = 0);
void centerInParentVertically(cocos2d::Node* pChildNode, const float margin = 0);
void centerInParentHorizontally(cocos2d::Node* pChildNode, const float margin = 0);

void toLeftOf(cocos2d::Node* pToLeft, cocos2d::Node* pOf, const float margin = 0);
void toRightOf(cocos2d::Node* pToRight, cocos2d::Node* pOf, const float margin = 0);
void toAboveOf(cocos2d::Node* pToAbove, cocos2d::Node* pOf, const float margin = 0);
void toBelowOf(cocos2d::Node* pToBelow, cocos2d::Node* pOf, const float margin = 0);
void toCenterHorizontalOf(cocos2d::Node* pToCenterHorizontal, cocos2d::Node* pOf, const float margin = 0);
void toCenterVerticalOf(cocos2d::Node* pToCenterVertical, cocos2d::Node* pOf, const float margin = 0);

}

} /* namespace CrossLayout */

