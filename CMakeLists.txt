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
		src/crosslayout/geometry/GeometryToString.h
		src/crosslayout/geometry/Point.cpp src/crosslayout/geometry/Point.h
		src/crosslayout/geometry/Rect.cpp src/crosslayout/geometry/Rect.h
		src/crosslayout/geometry/Size.cpp src/crosslayout/geometry/Size.h
		src/crosslayout/NodeWrapper.h
		src/crosslayout/Pixel.cpp src/crosslayout/Pixel.h
		)

ADD_LIBRARY(CrossLayout ${CrossLayout_SRC} ${EXTRA_SRC})

IF(COCOS2D_X)
	TARGET_INCLUDE_DIRECTORIES(CrossLayout PUBLIC
			${COCOS2D_ROOT}/cocos
			${COCOS2D_ROOT}/cocos/audio/include/
			${COCOS2D_ROOT}/cocos/platform
			/usr/include/GLFW
			/usr/local/include/GLFW
			)
	TARGET_LINK_LIBRARIES(CrossLayout cocos2d)
ENDIF()

#Add -Werror
TARGET_COMPILE_OPTIONS(CrossLayout PRIVATE
		-Wall -pedantic
		-Wno-unused-private-field -Wnon-virtual-dtor)

IF(TARGET gtest)
	ADD_SUBDIRECTORY(test/)
ENDIF()

TARGET_INCLUDE_DIRECTORIES(CrossLayout
		PUBLIC src
		PUBLIC ${EXTRA_INCLUDE})
