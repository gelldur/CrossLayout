//
// Created by Dawid Drozd aka Gelldur on 03/11/16.
//

#include <gtest/gtest.h>

#include <memory>
#include <ostream>

#include <crosslayout/Composer.h>

#include "TestNode.h"

template<class T>
std::ostream& operator<<(std::ostream& stream, const CrossLayout::Point<T>& point)
{
	return stream << "Point (x=" << point.x << ", y=" << point.y << ")";
}

TEST(TestComposer, doNothing)
{
	using Point = CrossLayout::Point<float>;
	using Rect = CrossLayout::Rect<float>;

	auto fooInitPosition = Point(10, 5);
	auto barInitPosition = Point(0, 2);

	auto parentNode = std::make_shared<CrossLayout::TestNode>(Rect{{0, 0}, {100, 400}});
	auto fooNode = std::make_shared<CrossLayout::TestNode>(Rect{fooInitPosition, {4, 2}});
	auto barNode = std::make_shared<CrossLayout::TestNode>(Rect{barInitPosition, {6, 5}});

	parentNode->addChild(barNode).addChild(fooNode);

	auto foo = fooNode.get();
	auto bar = barNode.get();

	EXPECT_EQ(fooInitPosition, foo->getPosition());
	EXPECT_EQ(barInitPosition, bar->getPosition());

	CrossLayout::Composer<CrossLayout::NodeWrapper<CrossLayout::TestNode>> composer;
	composer.center(foo);//Do nothing
	EXPECT_EQ(fooInitPosition, foo->getPosition());
	composer.center(foo).inParent();//Do nothing
	EXPECT_EQ(fooInitPosition, foo->getPosition());
	composer.center(foo).in(bar);//Do nothing
	EXPECT_EQ(fooInitPosition, foo->getPosition());
	composer.center(foo).in(foo->getParent());//Do nothing
	EXPECT_EQ(fooInitPosition, foo->getPosition());

	composer.leftEdge(foo);//Do nothing
	EXPECT_EQ(fooInitPosition, foo->getPosition());
	composer.leftEdge(foo).moveTo();//Do nothing
	EXPECT_EQ(fooInitPosition, foo->getPosition());

	composer.rightEdge(foo);//Do nothing
	EXPECT_EQ(fooInitPosition, foo->getPosition());
	composer.rightEdge(foo).moveTo();//Do nothing
	EXPECT_EQ(fooInitPosition, foo->getPosition());
}

TEST(TestComposer, center)
{
	using Point = CrossLayout::Point<float>;
	using Rect = CrossLayout::Rect<float>;

	auto fooInitPosition = Point(10, 5);
	auto barInitPosition = Point(0, 2);

	auto parentNode = std::make_shared<CrossLayout::TestNode>(Rect{{0, 0}, {100, 400}});
	auto fooNode = std::make_shared<CrossLayout::TestNode>(Rect{fooInitPosition, {4, 2}});
	auto barNode = std::make_shared<CrossLayout::TestNode>(Rect{barInitPosition, {6, 5}});

	parentNode->addChild(barNode).addChild(fooNode);

	auto foo = fooNode.get();
	auto bar = barNode.get();

	EXPECT_EQ(fooInitPosition, foo->getPosition());
	EXPECT_EQ(barInitPosition, bar->getPosition());

	CrossLayout::Composer<CrossLayout::NodeWrapper<CrossLayout::TestNode>> composer;
	composer.center(foo).inParent().center();//Move foo to parent center
	EXPECT_EQ(Point(50, 200), foo->getBoundingBox().getPoint(0.5F, 0.5F));
}

TEST(TestComposer, left)
{
	using Point = CrossLayout::Point<float>;
	using Rect = CrossLayout::Rect<float>;

	auto fooInitPosition = Point(10, 5);
	auto barInitPosition = Point(0, 2);

	auto parentNode = std::make_shared<CrossLayout::TestNode>(Rect{{0, 0}, {100, 400}});
	auto fooNode = std::make_shared<CrossLayout::TestNode>(Rect{fooInitPosition, {4, 2}});
	auto barNode = std::make_shared<CrossLayout::TestNode>(Rect{barInitPosition, {6, 5}});

	parentNode->addChild(barNode).addChild(fooNode);

	auto foo = fooNode.get();
	auto bar = barNode.get();

	EXPECT_EQ(fooInitPosition, foo->getPosition());
	EXPECT_EQ(barInitPosition, bar->getPosition());

	CrossLayout::Composer<CrossLayout::NodeWrapper<CrossLayout::TestNode>> composer;
	composer.leftEdge(foo).moveTo().parentLeftEdge();//Move foo to parent left edge
	EXPECT_EQ(Point(0, fooInitPosition.y), foo->getBoundingBox().point);

	composer.leftEdge(bar).moveTo().rightEdge(foo);
	EXPECT_EQ(Point(foo->getBoundingBox().getPoint(1, 0).x, barInitPosition.y), bar->getBoundingBox().point);

	composer.rightEdge(bar).moveTo().rightEdge(foo);
	EXPECT_EQ(Point(foo->getBoundingBox().getPoint(1, 0).x, barInitPosition.y), bar->getBoundingBox().getPoint(1, 0));
}


