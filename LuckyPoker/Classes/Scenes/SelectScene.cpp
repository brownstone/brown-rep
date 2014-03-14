#include "SelectScene.h"
#include "GameScene.h"
#include "../ResourceString.h"

USING_NS_CC;

// on "init" you need to initialize your instance
bool SelectLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }

    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
        "CloseNormal.png",
        "CloseSelected.png",
        this,
        menu_selector(SelectScene::menuCloseCallback));

    pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
        origin.y + pCloseItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label

    CCLabelTTF* pLabel = CCLabelTTF::create("Game Select Scene", "Arial", 24);

    // position the label on the center of the screen
    pLabel->setPosition(ccp(origin.x + visibleSize.width/2,
        origin.y + visibleSize.height - pLabel->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(pLabel, 1);


    CCMenuItem* btn1 = CCMenuItemImage::create(s_pPathPoStartOn,   s_pPathPoStartSel,   s_pPathPoStartOff, this, menu_selector(SelectLayer::menuCallbackMenuBtns));
    btn1->setUserData((void*)1);    btn1->setTag(101);
    CCMenuItem* btn2 = CCMenuItemImage::create(s_pPathHoStartOff, s_pPathHoStartOff, s_pPathHoStartOff, this, menu_selector(SelectLayer::menuCallbackMenuBtns));
    btn2->setUserData((void*)2);    btn2->setTag(102); btn2->setEnabled(false);
    CCMenuItem* btn3 = CCMenuItemImage::create(s_pPathQuitOn,   s_pPathQuitSel, this, menu_selector(SelectLayer::menuCallbackMenuBtns));
    btn3->setUserData((void*)3);    btn3->setTag(103);
    CCMenu* menu = CCMenu::create(btn1, btn2, btn3, NULL);

    static const int BTN_HEIGHT = 64 + 2;
    btn1->setPosition(ccp(0, BTN_HEIGHT * 2));// btn1->setAnchorPoint(ccp(0, 0));
    btn2->setPosition(ccp(0, BTN_HEIGHT * 1));// btn2->setAnchorPoint(ccp(0, 0));
    btn3->setPosition(ccp(0, BTN_HEIGHT * 0));// btn3->setAnchorPoint(ccp(0, 0));

    addChild(menu, 1, 100);
    //menu->setPosition(ccp(origin.x + visibleSize.width/2,
    //    origin.y + visibleSize.height - pLabel->getContentSize().height));

	_hasBeenSkiped = false;
	//this->setTouchEnabled(true);


    return true;
}

void SelectLayer::menuCallbackMenuBtns(CCObject* pSender)
{
    void* userData = ((CCNode*)pSender)->getUserData();
    switch ((int)userData)
    {  
    case 1: // start poker;
        if (_hasBeenSkiped == false) 
        {
            _hasBeenSkiped = true;
            this->startGamePlay();
        }
        break;
    case 2: // start holdem
        break;
    case 3: // quit
        Quit();
        break;
    default: assert(0); break;
    }
}

void SelectLayer::Quit()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
    CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
    CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
#endif
}

void SelectLayer::ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{
	if (_hasBeenSkiped == false) 
	{
		_hasBeenSkiped = true;
		this->startGamePlay();
	}
}

void SelectLayer::startGamePlay()
{
	CCLOG("Intro complete, begin GameScene");
	GameScene* pScene = GameScene::scene();
	CCDirector::sharedDirector()->replaceScene(pScene);
}

/////////////////////////////////////////////////////////
/////////////  SelectScene  //////////////////////////////

CCScene* SelectScene::scene()
{
    // 'scene' is an autorelease object
    CCScene* scene = CCScene::create();
    
    // 'layer' is an autorelease object
    SelectLayer* layer = SelectLayer::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}


void SelectScene::onEnter()
{
    int aa = 0;
    aa++;


}
void SelectScene::onExit()
{
    int aa = 0;
    aa++;

}

bool SelectScene::init()
{
    return true;
}



void SelectScene::menuCloseCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
    CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
#endif
}
