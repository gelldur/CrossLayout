OPTION(COCOS2D_X "Build for cocos2d-x" OFF)

SET(EXTRA_SRC)
SET(EXTRA_INCLUDE)

IF(COCOS2D_X)
	SET(EXTRA_SRC
			cocos2d-x/crosslayout/CocosNodeWrapper.h
			cocos2d-x/crosslayout/ComposerCocos.h
			cocos2d-x/Positioner.cpp cocos2d-x/Positioner.h
			)
	SET(EXTRA_INCLUDE cocos2d-x/)
ENDIF()

SET(CrossLayout_SRC
		src/crosslayout/Composer.cpp src/crosslayout/Composer.h
		src/crosslayout/geometry/Point.cpp src/crosslayout/geometry/Point.h
		src/crosslayout/geometry/Rect.cpp src/crosslayout/geometry/Rect.h
		src/crosslayout/geometry/Size.cpp src/crosslayout/geometry/Size.h
		src/crosslayout/NodeWrapper.h
		src/crosslayout/Pixel.cpp src/crosslayout/Pixel.h
		)

ADD_LIBRARY(CrossLayout ${CrossLayout_SRC} ${EXTRA_SRC})


SET(CrossLayout_SRC_TEST
		test/gtest/gtest.cpp
		test/gtest/TestComposer.cpp
		test/gtest/TestNode.cpp test/gtest/TestNode.h
		)

IF(TARGET gtest)
	ADD_EXECUTABLE(CrossLayout-Test ${CrossLayout_SRC_TEST})
	TARGET_LINK_LIBRARIES(CrossLayout-Test CrossLayout)
	TARGET_LINK_LIBRARIES(CrossLayout-Test gtest)
ENDIF()

TARGET_INCLUDE_DIRECTORIES(CrossLayout
		PUBLIC src
		PUBLIC ${EXTRA_INCLUDE})
