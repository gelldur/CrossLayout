//
// Created by Dawid Drozd aka Gelldur on 08/01/17.
//

#include "SampleScene.h"
//////////////////////////////////

#include <crosslayout/ComposerCocos.h>

#include <acme/CocosAcme.h>

#include <script_support/CCScriptSupport.h>
//#include <lua.h>
#include <selene.h>

using namespace cocos2d;

struct MyComposer
{
	CCNode* node;
	//CrossLayout::ComposerCocos::MoveHorizontal moveHorizontal;
	//CrossLayout::ComposerCocos::MoveVertical moveVertical;
	CrossLayout::ComposerCocos composer;

	MyComposer(CCNode* node)
			: node(node)
	{
	}

	MyComposer* moveLeftEdge(const char* name)
	{
	//	auto nameNode = node->getChildByTag(1);
	//	moveHorizontal = composer.leftEdge(nameNode);
		return this;
	}

	MyComposer* moveRightEdge(const char* name)
	{
	//	auto nameNode = node->getChildByTag(1);
	//	moveHorizontal = composer.rightEdge(nameNode);
		return this;
	}

	MyComposer* moveTopEdge(const char* name)
	{
	//	auto nameNode = node->getChildByTag(1);
		//moveVertical = composer.topEdge(nameNode);
		return this;
	}

	MyComposer* moveBottomEdge(const char* name)
	{
	//	auto nameNode = node->getChildByTag(1);
	//	moveVertical = composer.bottomEdge(nameNode);
		return this;
	}

	void toParentLeftEdge()
	{
		//moveHorizontal.moveTo().parentLeftEdge();
	}

	void toParentRightEdge()
	{
	//	moveHorizontal.moveTo().parentRightEdge();
	}

	void toParentTopEdge()
	{
		//moveVertical.moveTo().parentTopEdge();
	}

	void toParentBottomEdge()
	{
		//moveVertical.moveTo().parentBottomEdge();
	}
	cocos2d::CCTexture2D::

};

bool SampleScene::init()
{
	if (inherited::init() == false)
	{
		return false;
	}

	auto redSquare = CCLayerColor::create(cocos2d::ccColor4B{0xff, 0x00, 0x00, 0xff}, 100, 100);
	addChild(redSquare, 0, 1);
	redSquare->setAssignedName("red");

//	auto blueSquare = CCLayerColor::create(cocos2d::ccColor4B{0x00, 0x00, 0xff, 0xff}, 50, 150);
//	addChild(blueSquare, 0, 2);
//	redSquare->setAssignedName("blue");

	//CrossLayout::LayoutParser<cocos2d::CCNode> parser{this};
	//parser.parse(content).layout();

	sel::State state{true};

	CrossLayout::ComposerCocos composer;
	composer.center(redSquare).inParent();


	MyComposer myComposer{this};

	state["composer"].SetObj(myComposer
							 , "moveLeftEdge", &MyComposer::moveLeftEdge
							 , "moveRightEdge", &MyComposer::moveRightEdge
							 , "moveTopEdge", &MyComposer::moveTopEdge
							 , "moveBottomEdge", &MyComposer::moveBottomEdge
							 , "toParentLeftEdge", &MyComposer::toParentLeftEdge
							 , "toParentRightEdge", &MyComposer::toParentRightEdge
							 , "toParentTopEdge", &MyComposer::toParentTopEdge
							 , "toParentBottomEdge", &MyComposer::toParentBottomEdge
	);

	state.Load("/home/gelldur/Projects/Playsoft/pandemic2/pandemic/lib/CrossLayout/test/layout/sample2.layout");
	return true;
}
