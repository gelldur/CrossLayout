SET(WRAPPER_SRC)
SET(WRAPPER_INCLUDE)

IF(COCOS2D_X_V2)
	SET(WRAPPER_SRC
			wrapper/cocos2d-x-v2/crosslayout/CocosNodeWrapper.h
			wrapper/cocos2d-x-v2/crosslayout/ComposerCocos.h
			wrapper/cocos2d-x-v2/crosslayout/WrapGeometry.h
			)
	SET(WRAPPER_INCLUDE wrapper/cocos2d-x-v2/)
ELSEIF(COCOS2D_X_V3)
	SET(WRAPPER_SRC
			wrapper/cocos2d-x-v3/crosslayout/CocosNodeWrapper.h
			wrapper/cocos2d-x-v3/crosslayout/ComposerCocos.h
			wrapper/cocos2d-x-v3/Positioner.cpp cocos2d-x-v3/Positioner.h
			)
	SET(WRAPPER_INCLUDE wrapper/cocos2d-x-v3/)
ENDIF()
