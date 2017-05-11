IF(COCOS2D_X)
	ADD_LIBRARY(wrapper STATIC
			cocos2d-x-v3/crosslayout/CocosNodeWrapper.h
			cocos2d-x-v3/crosslayout/ComposerCocos.h
			cocos2d-x-v3/Positioner.cpp cocos2d-x-v3/Positioner.h
			)
	TARGET_INCLUDE_DIRECTORIES(wrapper PUBLIC cocos2d-x-v3/)
	TARGET_LINK_LIBRARIES(wrapper PRIVATE cocos2d)
ELSEIF(COCOS2DOW)
	ADD_LIBRARY(wrapper STATIC
			cocos2d-x-v2/crosslayout/CocosNodeWrapper.h
			cocos2d-x-v2/crosslayout/ComposerCocos.h
			)
	TARGET_INCLUDE_DIRECTORIES(wrapper PUBLIC cocos2d-x-v2/)
	TARGET_LINK_LIBRARIES(wrapper PRIVATE Cocos2Dx)
ELSE()
	ADD_LIBRARY(wrapper INTERFACE)
ENDIF()

#Add -Werror
TARGET_COMPILE_OPTIONS(wrapper PRIVATE
		-Wall -pedantic
		-Wno-unused-private-field -Wnon-virtual-dtor)
