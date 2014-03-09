#include "GameScene.h"
#include "Assist/InstanceMan.h"
#include "Model/MainLogic.h"
#include "../ResourceString.h"

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


CCPoint PlayerLayer::GetPlayerPos(int playerIndex) const
{
    if (playerIndex >= MAX_POKERPLAYER_COUNT) {
        return CCPoint(0,0);
    }

    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();

    static int playerBoxWidth = 40;
    //static int playerBoxHeight = 20;
    static int leftXPos = 50;
    static int midXPos = visibleSize.width / 2 - playerBoxWidth / 2;
    static int rightXPos = visibleSize.width - playerBoxWidth - 20;
    static int topYPos    = 3 * visibleSize.height / 3 - 60;
    static int midYPos    = 2 * visibleSize.height / 3 - 60;
    static int bottomYPos = 1 * visibleSize.height / 3 - 40;


    int playerPosX[5];
    int playerPosY[5];
    playerPosX[0] = rightXPos;	playerPosY[0] = topYPos;
    playerPosX[1] = rightXPos;	playerPosY[1] = midYPos;
    playerPosX[2] = midXPos;	playerPosY[2] = bottomYPos;
    playerPosX[3] = leftXPos;	playerPosY[3] = midYPos;
    playerPosX[4] = leftXPos;	playerPosY[4] = topYPos;

    return CCPoint(playerPosX[playerIndex], playerPosY[playerIndex]);
}

bool PlayerLayer::init()
{
	//////////////////////////////
	// 1. super init first
	if ( !CCLayer::init() )
	{
		return false;
	}
	CCLayerColor* background = CCLayerColor::create(ccc4(155, 155, 155, 255));
	addChild(background);

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
	static int bottomYPos = 1 * visibleSize.height / 3 - 40;


	int playerPosX[5];
	int playerPosY[5];
	playerPosX[0] = rightXPos;	playerPosY[0] = topYPos;
	playerPosX[1] = rightXPos;	playerPosY[1] = midYPos;
	playerPosX[2] = midXPos;	playerPosY[2] = bottomYPos;
	playerPosX[3] = leftXPos;	playerPosY[3] = midYPos;
	playerPosX[4] = leftXPos;	playerPosY[4] = topYPos;


	CCLabelTTF* pLabel = CCLabelTTF::create("Player 1", "Arial", 20);
	pLabel->setPosition(ccp(origin.x + playerPosX[0], origin.y + playerPosY[0]));
	this->addChild(pLabel, 1, 0);

	pLabel = CCLabelTTF::create("Player 2", "Arial", 20);
	pLabel->setPosition(ccp(origin.x + playerPosX[1], origin.y + playerPosY[1] - 10));
	this->addChild(pLabel, 1, 1);

	pLabel = CCLabelTTF::create("Player 3", "Arial", 20);
	pLabel->setPosition(ccp(origin.x + playerPosX[2], origin.y + playerPosY[2]));
	this->addChild(pLabel, 1, 2);

	pLabel = CCLabelTTF::create("Player 4", "Arial", 20);
	pLabel->setPosition(ccp(origin.x + playerPosX[3], origin.y + playerPosY[3] - 10));
	this->addChild(pLabel, 1, 3);

	pLabel = CCLabelTTF::create("Player 5", "Arial", 20);
	pLabel->setPosition(ccp(origin.x + playerPosX[4], origin.y + playerPosY[4]));
	this->addChild(pLabel, 1, 4);

	pLabel = CCLabelTTF::create("Dealer", "Arial", 20);
	pLabel->setPosition(ccp(origin.x + midXPos, origin.y + topYPos - 50));
	this->addChild(pLabel, 1, 10);

	pLabel = CCLabelTTF::create("Sequence", "Arial", 20);
	pLabel->setPosition(ccp(origin.x + midXPos, origin.y + topYPos + 30));
	this->addChild(pLabel, 1, 20);

	{ // players hand card
		static const int SMALL_CARD_WIDTH = 14;
		for (int i = 0; i < MAX_POKERPLAYER_COUNT; i++)
		{
			for (int j = 0; j < MAX_HANDCARD_COUNT; j++)
			{
				CCSprite* cardImg = CCSprite::create();
				cardImg->setPosition(ccp(playerPosX[i] + j * SMALL_CARD_WIDTH - 40, playerPosY[i] - 20));
				cardImg->setVisible(false);
				addChild(cardImg, 1, GetCardSpriteTag(i, j));
			}
		}
	}

	{ // jokbo
		static const int JOKBO_DISPALY_HEIGHT = 16;
		for (int i = 0; i < MAX_POKERPLAYER_COUNT; i++)
		{
			for (int j = 0; j < 2; j++) 
			{
				pLabel = CCLabelTTF::create(" ", "Arial", 18);
				pLabel->setPosition(ccp(playerPosX[i], playerPosY[i] - 40 - (j * JOKBO_DISPALY_HEIGHT)));
				pLabel->setColor(ccYELLOW);
				this->addChild(pLabel, 2, GetJokboLabelTag(i, j));
			}
		}
	}
	{ // sun, turn
		CCSprite* sunImg = CCSprite::create("Images/sun.png");
		sunImg->setPosition(ccp(playerPosX[0], playerPosY[0]));
		sunImg->setVisible(false);
		addChild(sunImg, 1, 300);

		CCSprite* turnImg = CCSprite::create("Images/turn.png");
		turnImg->setPosition(ccp(playerPosX[0], playerPosY[0]));
		turnImg->setVisible(false);
		addChild(turnImg, 1, 301);
	}

    { // betting buttons

        // ÇÏÇÁ  ÄõÅÍ
        //  ÄÝ    »æ
        // Ã¼Å©  ´ÙÀÌ
        // ½ºÅµ
        CCMenuItem* btn1 = CCMenuItemImage::create(s_pPathHalfOn,   s_pPathHalfOn,   s_pPathHalfOff,   this, menu_selector(PlayerLayer::menuCallbackBetBtns));
        btn1->setUserData((void*)0x1);
        CCMenuItem* btn2 = CCMenuItemImage::create(s_pPathQuaterOn, s_pPathQuaterOn, s_pPathQuaterOff, this, menu_selector(PlayerLayer::menuCallbackBetBtns));
        btn2->setUserData((void*)0x2);
        CCMenuItem* btn3 = CCMenuItemImage::create(s_pPathCallOn,   s_pPathCallOn,   s_pPathCallOff,   this, menu_selector(PlayerLayer::menuCallbackBetBtns));
        btn3->setUserData((void*)0x3);
        CCMenuItem* btn4 = CCMenuItemImage::create(s_pPathBbingOn,  s_pPathBbingOn,  s_pPathBbingOff,  this, menu_selector(PlayerLayer::menuCallbackBetBtns));
        btn4->setUserData((void*)0x4);
        CCMenuItem* btn5 = CCMenuItemImage::create(s_pPathCheckOn,  s_pPathCheckOn,  s_pPathCheckOff,  this, menu_selector(PlayerLayer::menuCallbackBetBtns));
        btn5->setUserData((void*)0x5);
        CCMenuItem* btn6 = CCMenuItemImage::create(s_pPathDieOn,    s_pPathDieOn,    s_pPathDieOff,    this, menu_selector(PlayerLayer::menuCallbackBetBtns));
        btn6->setUserData((void*)0x6);
        CCMenu* menu = CCMenu::create( btn1, btn2, btn3, btn4, btn5, btn6, NULL);
        menu->alignItemsInColumns(2, 2, 2, NULL);


        addChild(menu);
        menu->setPosition(ccp(midXPos + 100, bottomYPos));

    }



	m_pMainLogic = InstanceMan::mainLogic->GetInstance();

	m_kPokerSequence = POKERSEQUENCE_NONE;

	return true;
}

void PlayerLayer::menuCallbackBetBtns(CCObject* sender)
{
    void* userData = ((CCNode*)sender)->getUserData();
    int aa = 0;
    aa++;
}



void PlayerLayer::onEnter()
{
	CCLayer::onEnter();
	scheduleUpdate();
}

void PlayerLayer::update(float delta)
{
	CCLayer::update(delta);


	{ // player info
		PokerPlayerInfo playerInfos[MAX_POKERPLAYER_COUNT];
		m_pMainLogic->GetPlayerInfo(playerInfos);

		for (int i = 0; i < MAX_POKERPLAYER_COUNT; i++)
		{
			bool changed = m_kPlayerInfos[i].Changed(playerInfos[i]);
			if (changed)
			{
				DisplayPlayer(i, playerInfos[i]);
				m_kPlayerInfos[i] = playerInfos[i];
			}
		}
	}

	{ // jokbo info
		JokboResult jokboInfos[MAX_POKERPLAYER_COUNT];
		m_pMainLogic->GetPlayerJokboInfo(jokboInfos);

		for (int i = 0; i < MAX_POKERPLAYER_COUNT; i++)
		{
			bool changed = m_kPlayerJokbo[i].Changed(jokboInfos[i]);
			if (changed)
			{
				DisplayPlayerJokbo(i, jokboInfos[i]);
				m_kPlayerJokbo[i] = jokboInfos[i];
			}
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

			if (seq == POKERSEQUENCE_START || seq == POKERSEQUENCE_RESULT)
			{
				HideHandCards();
			}
			m_kPokerSequence = seq;
		}
	}

    { // player manager infos. sun/turn
        PlayerManInfo playerManInfo;
        m_pMainLogic->GetPlayerManInfo(playerManInfo);

        bool changed = m_kPlayerManInfo.Changed(playerManInfo);
        if (changed) 
        {
            DisplayPlayerMan(playerManInfo);
            m_kPlayerManInfo = playerManInfo;
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

	DisplayPlayerHandCards(index, playerInfo);
}

int PlayerLayer::GetCardSpriteTag(int playerIndex, int cardIndex) const
{
	int index = 100 + playerIndex * 10 + cardIndex;
	return index;
}

int PlayerLayer::GetJokboLabelTag(int playerIndex, int labelIndex) const
{
	int index = 200 + playerIndex * 10 + labelIndex;
	return index;
}

void PlayerLayer::DisplayPlayerHandCards(int index, const PokerPlayerInfo& playerInfo)
{
	for (int i = 0; i < MAX_HANDCARD_COUNT; i++)
	{
		Card card;
		if (i < MAX_HIDDENCARD_COUNT) {
			card = playerInfo.akHiddenCard[i];
		} 
		else if (i < MAX_HIDDENCARD_COUNT + MAX_OPENCARD_COUNT) 
		{
			card = playerInfo.akOpenCard[i - MAX_HIDDENCARD_COUNT];
		} else 
		{
			card = playerInfo.kLastCard;
		}
		if (card.GetCard() != Card::CARD_NONE)
		{
			int cardTag = GetCardSpriteTag(index, i);
			CCSprite* cardSprite = (CCSprite*)getChildByTag(cardTag);
			if (cardSprite && cardSprite->isVisible() == false)
			{
				static const int CARD_WIDTH = 20;
				static const int CARD_HEIGHT = 40;

				int cardY = card.GetPicture() * CARD_HEIGHT;
				int cardX = card.GetNumber() * CARD_WIDTH;

				cardSprite->setVisible(true);
				cardSprite->initWithFile("Images/smallcards.png", CCRect(cardX, cardY, CARD_WIDTH, CARD_HEIGHT));
			}
		}
	}
}

void PlayerLayer::DisplayPlayerJokbo(int index, const JokboResult& playerJokbo)
{
	char pszInfo[256];
	playerJokbo.GetStringInfo(pszInfo);

	CCLabelTTF* label = (CCLabelTTF*)getChildByTag(GetJokboLabelTag(index, 0));
	if (label)
	{
		label->setString(pszInfo);
	}
}


void PlayerLayer::HideHandCards()
{
	static const int SMALL_CARD_WIDTH = 20;
	for (int i = 0; i < MAX_POKERPLAYER_COUNT; i++)
	{
		for (int j = 0; j < MAX_HANDCARD_COUNT; j++)
		{
			CCSprite* cardSprite = (CCSprite*)getChildByTag(GetCardSpriteTag(i, j));
			cardSprite->setVisible(false);
		}
	}
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

void PlayerLayer::DisplayPlayerMan(const PlayerManInfo& playerManInfo)
{
    CCPoint sunPlayerPos(GetPlayerPos(playerManInfo.sunPlayerIndex));
    CCSprite* sunImg = (CCSprite*)getChildByTag(300);
    sunImg->setVisible(true);
    sunImg->setPosition(sunPlayerPos);

    CCPoint turnPlayerPos(GetPlayerPos(playerManInfo.turnIndex));
    turnPlayerPos.x += 20;
    CCSprite* turnImg = (CCSprite*)getChildByTag(301);
    turnImg->setVisible(true);
    turnImg->setPosition(turnPlayerPos);

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
