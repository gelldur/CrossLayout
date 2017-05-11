OPTION(COCOS2D_X "Build for cocos2d-x" OFF)

ADD_SUBDIRECTORY(wrapper)

SET(CrossLayout_SRC
		src/crosslayout/Composer.cpp src/crosslayout/Composer.h
		src/crosslayout/geometry/GeometryToString.h
		src/crosslayout/geometry/Point.cpp src/crosslayout/geometry/Point.h
		src/crosslayout/geometry/Rect.cpp src/crosslayout/geometry/Rect.h
		src/crosslayout/geometry/Size.cpp src/crosslayout/geometry/Size.h
		src/crosslayout/NodeWrapper.h
		src/crosslayout/Pixel.cpp src/crosslayout/Pixel.h
		)

ADD_LIBRARY(CrossLayout STATIC ${CrossLayout_SRC})

TARGET_LINK_LIBRARIES(CrossLayout PUBLIC wrapper)

#Add -Werror
TARGET_COMPILE_OPTIONS(CrossLayout PRIVATE
		-Wall -pedantic
		-Wno-unused-private-field -Wnon-virtual-dtor)

IF(TARGET gtest)
	ADD_SUBDIRECTORY(test/)
ENDIF()

TARGET_INCLUDE_DIRECTORIES(CrossLayout PUBLIC src/)
