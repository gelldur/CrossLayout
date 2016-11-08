//
// Created by Dawid Drozd aka Gelldur on 03/11/16.
//


#include <gtest/gtest.h>

GTEST_API_ int main(int argc, char** argv)
{
	printf("Running main() from gtest.cpp\n");
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
