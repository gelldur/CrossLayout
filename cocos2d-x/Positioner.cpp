/*
 * Positioner.cpp
 *
 *  Created on: May 12, 2013
 *      Author: Dawid Drozd
 */

#include "Positioner.h"

using namespace cocos2d;

namespace CrossLayout
{
//TODO Change getScaledHeight to beoundingbox
Point Positioner::getLeftBottomCorner(Node* pNode)
{
	CCASSERT (pNode != nullptr, "Node* pNode cannot be nullptr!");
	Point point = pNode->getBoundingBox().origin;
	//For now commented because changed getPosition to boundingBox
	//point.x -= pNode->getAnchorPointInPoints().x * pNode->getScaleX();
	//point.y -= pNode->getAnchorPointInPoints().y * pNode->getScaleY();
	return point;
}

Point Positioner::getLeftTopCorner(Node* pNode)
{
	CCASSERT (pNode != nullptr, "Node* pNode cannot be nullptr!");
	Point point = getLeftBottomCorner(pNode);
	point.y += getScaledHeight(pNode);

	return point;
}

Point Positioner::getRightTopCorner(Node* pNode)
{
	CCASSERT (pNode != nullptr, "Node* pNode cannot be nullptr!");
	Point point = getLeftTopCorner(pNode);
	point.x += getScaledWidth(pNode);
	return point;
}

Point Positioner::getRightBottomCorner(Node* pNode)
{
	CCASSERT (pNode != nullptr, "Node* pNode cannot be nullptr!");
	Point point = getRightTopCorner(pNode);
	point.y -= getScaledHeight(pNode);
	return point;
}

Point Positioner::getCenterPoint(Node* pNode)
{
	CCASSERT (pNode != nullptr, "Node* pNode cannot be nullptr!");
	Point point = getLeftBottomCorner(pNode);
	point.x += (getScaledWidth(pNode) * 0.5F);
	point.y += (getScaledHeight(pNode) * 0.5F);
	return point;
}

Point Positioner::getCenterPoint(const Size& size)
{
	return Point(size.width * 0.5F, size.height * 0.5F);
}

void Positioner::setCornerToPosition(Node* pNode, const Point& cornerPosition, const Point& position)
{
	pNode->setPosition((position - cornerPosition) + pNode->getPosition());
}

void Positioner::centerInParent(Node* pChildNode)
{
	CCASSERT (pChildNode, "Can't be null");

	CCASSERT (pChildNode->getParent() != nullptr, "Parent can't be nullptr!");

	centerInParentHorizontally(pChildNode);
	centerInParentVertically(pChildNode);
}

void Positioner::leftEdge(Node* pChildNode, const float margin)
{
	CCASSERT (pChildNode, "Can't be null");

	CCASSERT (pChildNode->getParent() != nullptr, "Parent can't be nullptr!");

	Point leftChildTopCorner = getLeftTopCorner(pChildNode);
	leftChildTopCorner.y = pChildNode->getPositionY();
	setCornerToPosition(pChildNode, leftChildTopCorner, Point(0 + margin, leftChildTopCorner.y));
}

void Positioner::rightEdge(Node* pChildNode, const float margin)
{
	CCASSERT (pChildNode, "Can't be null");

	CCASSERT (pChildNode->getParent() != nullptr, "Parent can't be nullptr!");

	const Point corner = getRightTopCorner(pChildNode);

	setCornerToPosition(pChildNode, corner, Point((pChildNode->getParent()->getContentSize().width) - margin, corner
			.y));
}

void Positioner::topEdge(Node* pChildNode, const float margin)
{
	CCASSERT (pChildNode, "Can't be null");

	CCASSERT (pChildNode->getParent() != nullptr, "Parent can't be nullptr!");

	const Point corner = getRightTopCorner(pChildNode);

	setCornerToPosition(pChildNode, corner, Point(corner.x, (pChildNode->getParent()->getContentSize().height) -
															margin));
}

void Positioner::bottomEdge(Node* pChildNode, const float margin)
{
	CCASSERT (pChildNode, "Can't be null");

	CCASSERT (pChildNode->getParent() != nullptr, "Parent can't be nullptr!");

	const Point corner = getRightBottomCorner(pChildNode);
	setCornerToPosition(pChildNode, corner, Point(corner.x, 0 + margin));
}

void Positioner::centerInParentVertically(Node* pChildNode, const float margin)
{
	CCASSERT (pChildNode, "Can't be null");

	CCASSERT (pChildNode->getParent() != nullptr, "Parent can't be nullptr!");

	const Point corner = getCenterPoint(pChildNode);
	setCornerToPosition(pChildNode, corner, Point(corner.x, pChildNode->getParent()->getContentSize().height * 0.5F +
															margin));
}

void Positioner::centerInParentHorizontally(Node* pChildNode, const float margin)
{
	CCASSERT (pChildNode, "Can't be null");

	CCASSERT (pChildNode->getParent() != nullptr, "Parent can't be nullptr!");

	const Point corner = getCenterPoint(pChildNode);

	setCornerToPosition(pChildNode, corner, Point(pChildNode->getParent()->getContentSize().width * 0.5F + margin
												  , corner.y));
}

float Positioner::getScaledWidth(Node* pNode)
{
	CCASSERT (pNode != nullptr, "Node can't be nullptr");
	return pNode->getContentSize().width * pNode->getScaleX();
}

float Positioner::getScaledHeight(Node* pNode)
{
	CCASSERT (pNode != nullptr, "Node can't be nullptr");
	return pNode->getContentSize().height * pNode->getScaleY();
}

Size Positioner::getScaledSize(Node* pNode)
{
	CCASSERT (pNode != nullptr, "Node can't be nullptr");
	return Size(getScaledWidth(pNode), getScaledHeight(pNode));
}

void Positioner::toLeftOf(Node* pToLeft, Node* pOf, const float margin)
{
	CCASSERT (pToLeft->getParent() != pOf, "This doesn't work in parent. Different coordinate system");
	assert (pToLeft->getParent() != nullptr);
	assert (pOf->getParent() != nullptr);
	assert (pToLeft->getParent() == pOf->getParent());

	Point corner = Positioner::getRightBottomCorner(pToLeft);
	Positioner::setCornerToPosition(pToLeft, corner, Point(Positioner::getLeftBottomCorner(pOf).x - margin, corner
			.y));
}

void Positioner::toRightOf(Node* pToRight, Node* pOf, const float margin)
{
	CCASSERT (pToRight->getParent() != pOf, "This doesn't work in parent. Different coordinate system");
	assert (pToRight->getParent() != nullptr);
	assert (pOf->getParent() != nullptr);
	assert (pToRight->getParent() == pOf->getParent());

	Point corner = Positioner::getLeftBottomCorner(pToRight);
	Positioner::setCornerToPosition(pToRight, corner, Point(Positioner::getRightBottomCorner(pOf).x + margin, corner
			.y));
}

void Positioner::toAboveOf(Node* pToAbove, Node* pOf, const float margin)
{
	CCASSERT (pToAbove->getParent() != pOf, "This doesn't work in parent. Different coordinate system");
	assert (pToAbove->getParent() != nullptr);
	assert (pOf->getParent() != nullptr);
	assert (pToAbove->getParent() == pOf->getParent());

	Point corner = Positioner::getLeftBottomCorner(pToAbove);
	Positioner::setCornerToPosition(pToAbove, corner, Point(corner.x, Positioner::getLeftTopCorner(pOf).y + margin));
}

void Positioner::toBelowOf(Node* pToBelow, Node* pOf, const float margin)
{
	CCASSERT (pToBelow->getParent() != pOf, "This doesn't work in parent. Different coordinate system");
	assert (pToBelow->getParent() != nullptr);
	assert (pOf->getParent() != nullptr);
	assert (pToBelow->getParent() == pOf->getParent());

	Point corner = Positioner::getLeftTopCorner(pToBelow);
	Positioner::setCornerToPosition(pToBelow, corner, Point(corner.x, Positioner::getLeftBottomCorner(pOf).y - margin));
}

void Positioner::toCenterHorizontalOf(Node* pToCenterHorizontal, Node* pOf, const float margin)
{
	CCASSERT (pToCenterHorizontal->getParent() != pOf
			  , "This doesn't work in parent. Different coordinate system");
	assert (pToCenterHorizontal->getParent() != nullptr);
	assert (pOf->getParent() != nullptr);
	assert (pToCenterHorizontal->getParent() == pOf->getParent());

	Point corner = Positioner::getCenterPoint(pToCenterHorizontal);
	Positioner::setCornerToPosition(pToCenterHorizontal, corner, Point(Positioner::getCenterPoint(pOf).x + margin
																	   , corner.y));
}

void Positioner::toCenterVerticalOf(Node* pToCenterVertical, Node* pOf, const float margin)
{
	CCASSERT (pToCenterVertical->getParent() != pOf
			  , "This doesn't work in parent. Different coordinate system");
	assert (pToCenterVertical->getParent() != nullptr);
	assert (pOf->getParent() != nullptr);
	assert (pToCenterVertical->getParent() == pOf->getParent());

	Point corner = Positioner::getCenterPoint(pToCenterVertical);
	Positioner::setCornerToPosition(pToCenterVertical, corner, Point(corner.x,
			Positioner::getCenterPoint(pOf).y + margin));
}

void Positioner::toCenterOf(Node* pToCenter, Node* pOf)
{
	assert(pToCenter);
	assert(pOf);
	Positioner::toCenterHorizontalOf(pToCenter, pOf, 0.0f);
	Positioner::toCenterVerticalOf(pToCenter, pOf, 0.0f);
}

} /* namespace CrossLayout */
