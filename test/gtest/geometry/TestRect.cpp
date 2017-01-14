//
// Created by Dawid Drozd aka Gelldur on 14/01/17.
//
#include <gtest/gtest.h>

#include <crosslayout/geometry/Rect.h>
#include <crosslayout/geometry/GeometryToString.h>

using namespace CrossLayout;

TEST(TestRect, mergeSticky)
{
	Rect<int> rectA{0, 0, 10, 10};
	Rect<int> rectB{10, 10, 10, 10};
	EXPECT_EQ((Rect<int>{0, 0, 20, 20}), rectA.merge(rectB));
}

TEST(TestRect, mergeSpace)
{
	Rect<int> rectA{5, 5, 10, 10};
	Rect<int> rectB{20, 20, 10, 10};
	EXPECT_EQ((Rect<int>{5, 5, 25, 25}), rectA.merge(rectB));
	EXPECT_EQ((Rect<int>{5, 5, 25, 25}), rectB.merge(rectA));
}

TEST(TestRect, mergeIntersect)
{
	Rect<int> rectA{15, 15, 10, 10};
	Rect<int> rectB{20, 20, 10, 10};
	EXPECT_EQ((Rect<int>{15, 15, 15, 15}), rectA.merge(rectB));
	EXPECT_EQ((Rect<int>{15, 15, 15, 15}), rectB.merge(rectA));
}

TEST(TestRect, mergeUnion)
{
	Rect<int> rectA{20, 20, 10, 10};
	Rect<int> rectB{20, 20, 10, 10};
	EXPECT_EQ((Rect<int>{20, 20, 10, 10}), rectA.merge(rectB));
	EXPECT_EQ((Rect<int>{20, 20, 10, 10}), rectB.merge(rectA));
}

TEST(TestRect, mergeWithSelf)
{
	Rect<int> rectA{20, 20, 10, 10};
	EXPECT_EQ(rectA, rectA.merge(rectA));
}
