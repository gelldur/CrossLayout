CMAKE_MINIMUM_REQUIRED(VERSION 3.1)

SET(CrossLayout_SRC_TEST
		gtest/TestComposer.cpp
		gtest/TestNode.cpp gtest/TestNode.h
		gtest/geometry/TestRect.cpp)

ADD_EXECUTABLE(CrossLayout-Test ${CrossLayout_SRC_TEST})

TARGET_INCLUDE_DIRECTORIES(CrossLayout-Test PRIVATE ${gtest_INCLUDE})

TARGET_LINK_LIBRARIES(CrossLayout-Test gtest gtest_main)
TARGET_LINK_LIBRARIES(CrossLayout-Test CrossLayout)

