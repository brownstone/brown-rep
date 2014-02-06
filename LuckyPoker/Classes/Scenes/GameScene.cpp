#include "GameScene.h"
#include "Assist/InstanceMan.h"
#include "Model/MainLogic.h"

bool GameBGLayer::init()
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
        menu_selector(GameScene::menuCloseCallback));

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

    CCLabelTTF* pLabel = CCLabelTTF::create("Game BG Layer", "Arial", 24);

    // position the label on the center of the screen
    pLabel->setPosition(ccp(origin.x + visibleSize.width/2,
        origin.y + visibleSize.height - pLabel->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(pLabel, 1);

    //// add "IntroScene" splash screen"
    //CCSprite* pSprite = CCSprite::create("IntroScene.png");

    //// position the sprite on the center of the screen
    //pSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    //// add the sprite as a child to this layer
    //this->addChild(pSprite, 0);


    return true;
}

void GameBGLayer::update(float delta)
{
	CCLayer::update(delta);
}



bool PlayerLayer::init()
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
	static int playerBoxWidth = 40;
	//static int playerBoxHeight = 20;
	static int leftXPos = 50;
	static int midXPos = visibleSize.width / 2 - playerBoxWidth / 2;
	static int rightXPos = visibleSize.width - playerBoxWidth - 20;
	static int topYPos    = 3 * visibleSize.height / 3 - 60;
	static int midYPos    = 2 * visibleSize.height / 3 - 60;
	static int bottomYPos = 1 * visibleSize.height / 3 - 60;


	int playerPosX[5];
	int playerPosY[5];
	playerPosX[0] = rightXPos;	playerPosY[0] = topYPos;
	playerPosX[1] = rightXPos;	playerPosY[1] = midYPos;
	playerPosX[2] = midXPos;	playerPosY[2] = bottomYPos;
	playerPosX[3] = leftXPos;	playerPosY[3] = midYPos;
	playerPosX[4] = leftXPos;	playerPosY[4] = topYPos;


	CCLabelTTF* pLabel = CCLabelTTF::create("Player 1", "Arial", 14);
	pLabel->setPosition(ccp(origin.x + playerPosX[0], origin.y + playerPosY[0]));
	this->addChild(pLabel, 1, 0);

	pLabel = CCLabelTTF::create("Player 2", "Arial", 14);
	pLabel->setPosition(ccp(origin.x + playerPosX[1], origin.y + playerPosY[1]));
	this->addChild(pLabel, 1, 1);

	pLabel = CCLabelTTF::create("Player 3", "Arial", 14);
	pLabel->setPosition(ccp(origin.x + playerPosX[2], origin.y + playerPosY[2]));
	this->addChild(pLabel, 1, 2);

	pLabel = CCLabelTTF::create("Player 4", "Arial", 14);
	pLabel->setPosition(ccp(origin.x + playerPosX[3], origin.y + playerPosY[3]));
	this->addChild(pLabel, 1, 3);

	pLabel = CCLabelTTF::create("Player 5", "Arial", 14);
	pLabel->setPosition(ccp(origin.x + playerPosX[4], origin.y + playerPosY[4]));
	this->addChild(pLabel, 1, 4);

	pLabel = CCLabelTTF::create("Dealer", "Arial", 14);
	pLabel->setPosition(ccp(origin.x + midXPos, origin.y + topYPos - 50));
	this->addChild(pLabel, 1, 10);

	pLabel = CCLabelTTF::create("Sequence", "Arial", 14);
	pLabel->setPosition(ccp(origin.x + midXPos, origin.y + midYPos));
	this->addChild(pLabel, 1, 20);

	m_pMainLogic = InstanceMan::mainLogic->GetInstance();

	m_kPokerSequence = POKERSEQUENCE_NONE;

	return true;
}


void PlayerLayer::onEnter()
{
	CCLayer::onEnter();
	scheduleUpdate();
}

void PlayerLayer::update(float delta)
{
	CCLayer::update(delta);

	PokerPlayerInfo playerInfos[MAX_POKERPLAYER_COUNT];
	m_pMainLogic->GetPlayerInfo(playerInfos);

	// player info
	for (int i = 0; i < MAX_POKERPLAYER_COUNT; i++)
	{
		bool changed = m_kPlayerInfos[i].Changed(playerInfos[i]);
		if (changed)
		{
			DisplayPlayer(i, playerInfos[i]);
			m_kPlayerInfos[i] = playerInfos[i];
		}
	}

	{ // dealer info
		TableInfo tableInfo;
		m_pMainLogic->GetDealerInfo(tableInfo);
		bool changed = m_kTableInfo.Changed(tableInfo);
		if (changed)
		{
			DisplayDealer(tableInfo);
			m_kTableInfo = tableInfo;
		}

	}

	{ // sequence
		PokerSequence seq = m_pMainLogic->GetSequence();
		bool changed = (m_kPokerSequence != seq);
		if (changed)
		{
			DisplaySeq(seq);
			m_kPokerSequence = seq;
		}
	}
}


void PlayerLayer::DisplayPlayer(int index, const PokerPlayerInfo& playerInfo)
{
	char pszInfo[256];
	playerInfo.GetStringInfo(pszInfo);

	char pszPlayerInfo[256];
	sprintf(pszPlayerInfo, "player %d \n %s ", index, pszInfo);
	CCLabelTTF *label = (CCLabelTTF *)getChildByTag(index);
	label->setString(pszPlayerInfo);
}


void PlayerLayer::DisplayDealer(const TableInfo& tableInfo)
{
	char pszInfo[256];
	tableInfo.GetStringInfo(pszInfo);

	char pszDealerInfo[256];
	sprintf(pszDealerInfo, "Dealer \n %s ", pszInfo);
	CCLabelTTF *label = (CCLabelTTF *)getChildByTag(10);
	label->setString(pszDealerInfo);

}

void PlayerLayer::DisplaySeq(PokerSequence seq)
{
	char pszInfo[256];
	sprintf(pszInfo, "Seq: %s ", PokerSequenceStr[seq]);
	CCLabelTTF *label = (CCLabelTTF *)getChildByTag(20);
	label->setString(pszInfo);

}

/////////////////////////////////////////////////////////
/////////////  GameScene  //////////////////////////////

GameScene* GameScene::scene()
{
    // 'scene' is an autorelease object
    GameScene* scene = GameScene::create();
    
    GameBGLayer* bgLayer = GameBGLayer::create();
    scene->addChild(bgLayer);

	PlayerLayer* playerLayer = PlayerLayer::create();
	scene->addChild(playerLayer);

    // return the scene
    return scene;
}

void GameScene::onEnter()
{
	scheduleUpdate();
	CCScene::onEnter();
	//m_pMainLogic->OnEnter();
}

void GameScene::onExit()
{
	CCScene::onExit();
	//m_pMainLogic->OnExit();
}

bool GameScene::init()
{
	CCScene::init();
	m_pMainLogic = InstanceMan::mainLogic->GetInstance();
	// m_pMainLogic->Init(); // already init().
    return true;
}

void GameScene::update(float delta)
{
	CCScene::update(delta);

	UpdateLogic(delta);
}

void GameScene::UpdateLogic(float delta)
{
	m_pMainLogic->update(delta);
}

void GameScene::menuCloseCallback(CCObject* pSender)
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
