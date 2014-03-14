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
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    CCSize playerBoxSize(100,100);
    // visible size 320.0, 480.0

    static int LEFT_MARGIN  = 10;
    // x
    static int playerBoxWidth = 100;
    static int leftXPos = playerBoxWidth / 2 + LEFT_MARGIN;
    static int midXPos = visibleSize.width / 2 - LEFT_MARGIN;
    static int rightXPos = visibleSize.width - playerBoxWidth / 2 - LEFT_MARGIN;

    static int TABLEHEIGHT = visibleSize.height - 40;
    static int TOP_MARGIN  = 30;
    // y
    static int playerBoxHeight = 100;
    static int topYPos    = 3 * TABLEHEIGHT / 3 - playerBoxHeight / 2 - 20;
    static int midYPos    = 2 * TABLEHEIGHT / 3 - playerBoxHeight / 2 - 20;
    static int bottomYPos = 1 * TABLEHEIGHT / 3 - playerBoxHeight / 2 - 20;


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

    static int midXPos = visibleSize.width / 2;
    static int rightXPos = visibleSize.width - 100 - 20;
    static int topYPos    = 3 * visibleSize.height / 3 - 60;
    static int midYPos    = 2 * visibleSize.height / 3 - 60;
    static int bottomYPos = 1 * visibleSize.height / 3 - 40;


    for (int i = 0; i < MAX_POKERPLAYER_COUNT; i++)
    {
        CCSprite* pbox = CCSprite::create(s_pPathPBoxDefault);
        pbox->setPosition(GetPlayerPos(i));
        addChild(pbox, 1);
    }


    CCPoint playerBoxPos[MAX_POKERPLAYER_COUNT];
    for (int i = 0; i < MAX_POKERPLAYER_COUNT; i++)
    {
        playerBoxPos[i] = GetPlayerPos(i);
    }


	CCLabelTTF* pLabel = CCLabelTTF::create("Player 1", "Arial", 20);
	pLabel->setPosition(ccp(playerBoxPos[0].x,  playerBoxPos[0].y + 20));
	this->addChild(pLabel, 1, 0);

	pLabel = CCLabelTTF::create("Player 2", "Arial", 20);
	pLabel->setPosition(ccp(playerBoxPos[1].x,  playerBoxPos[1].y + 20));
	this->addChild(pLabel, 1, 1);

	pLabel = CCLabelTTF::create("Player 3", "Arial", 20);
	pLabel->setPosition(ccp(playerBoxPos[2].x,  playerBoxPos[2].y + 20));
	this->addChild(pLabel, 1, 2);

	pLabel = CCLabelTTF::create("Player 4", "Arial", 20);
	pLabel->setPosition(ccp(playerBoxPos[3].x,  playerBoxPos[3].y + 20));
	this->addChild(pLabel, 1, 3);

	pLabel = CCLabelTTF::create("Player 5", "Arial", 20);
	pLabel->setPosition(ccp(playerBoxPos[4].x,  playerBoxPos[4].y + 20));
	this->addChild(pLabel, 1, 4);

	pLabel = CCLabelTTF::create("Dealer", "Arial", 20);
	pLabel->setPosition(ccp(origin.x + midXPos, origin.y + topYPos - 50));
	this->addChild(pLabel, 1, 10);

	pLabel = CCLabelTTF::create("Sequence", "Arial", 20);
	pLabel->setPosition(ccp(origin.x + midXPos, origin.y + topYPos + 30));
	this->addChild(pLabel, 1, 20);


    pLabel = CCLabelTTF::create(" ", "Arial", 18);
    pLabel->setPosition(ccp(playerBoxPos[0].x,  playerBoxPos[0].y + 60));
    pLabel->setColor(ccBLUE);
    this->addChild(pLabel, 1, 500);

    pLabel = CCLabelTTF::create(" ", "Arial", 18);
    pLabel->setPosition(ccp(playerBoxPos[1].x,  playerBoxPos[1].y + 60));
    pLabel->setColor(ccBLUE);
    this->addChild(pLabel, 1, 501);

    pLabel = CCLabelTTF::create(" ", "Arial", 18);
    pLabel->setPosition(ccp(playerBoxPos[2].x,  playerBoxPos[2].y + 60));
    pLabel->setColor(ccBLUE);
    this->addChild(pLabel, 1, 502);

    pLabel = CCLabelTTF::create(" ", "Arial", 18);
    pLabel->setPosition(ccp(playerBoxPos[3].x,  playerBoxPos[3].y + 60));
    pLabel->setColor(ccBLUE);
    this->addChild(pLabel, 1, 503);

    pLabel = CCLabelTTF::create(" ", "Arial", 18);
    pLabel->setPosition(ccp(playerBoxPos[4].x,  playerBoxPos[4].y + 60));
    pLabel->setColor(ccBLUE);
    this->addChild(pLabel, 1, 504);


	{ // players hand card
		static const int SMALL_CARD_WIDTH = 14;
		for (int i = 0; i < MAX_POKERPLAYER_COUNT; i++)
		{
			for (int j = 0; j < MAX_HANDCARD_COUNT; j++)
			{
				CCSprite* cardImg = CCSprite::create();
				cardImg->setPosition(ccp(playerBoxPos[i].x + j * SMALL_CARD_WIDTH - 40, playerBoxPos[i].y - 20));
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
				pLabel->setPosition(ccp(playerBoxPos[i].x, playerBoxPos[i].y - 40 - (j * JOKBO_DISPALY_HEIGHT)));
				pLabel->setColor(ccYELLOW);
				this->addChild(pLabel, 2, GetJokboLabelTag(i, j));
			}
		}
	}
	{ // turn, sun
        CCSprite* turnImg = CCSprite::create(s_pPathPBoxTurn);
        turnImg->setPosition(playerBoxPos[0]);
        turnImg->setVisible(false);
        addChild(turnImg, 1, 301);

        CCSprite* sunImg = CCSprite::create(s_pPathSun);
		sunImg->setPosition(playerBoxPos[0]);
		sunImg->setVisible(false);
		addChild(sunImg, 1, 300);

	}

    { // betting buttons

        // 하프  쿼터
        //  콜    삥
        // 체크  다이
        // 스킵
        CCMenuItem* btn1 = CCMenuItemImage::create(s_pPathHalfOn,   s_pPathHalfOn,   s_pPathHalfOff,   this, menu_selector(PlayerLayer::menuCallbackBetBtns));
        btn1->setUserData((void*)1);
        btn1->setTag(401);
        CCMenuItem* btn2 = CCMenuItemImage::create(s_pPathQuaterOn, s_pPathQuaterOn, s_pPathQuaterOff, this, menu_selector(PlayerLayer::menuCallbackBetBtns));
        btn2->setUserData((void*)2);
        btn2->setTag(402);
        CCMenuItem* btn3 = CCMenuItemImage::create(s_pPathCallOn,   s_pPathCallOn,   s_pPathCallOff,   this, menu_selector(PlayerLayer::menuCallbackBetBtns));
        btn3->setUserData((void*)3);
        btn3->setTag(403);
        CCMenuItem* btn4 = CCMenuItemImage::create(s_pPathBbingOn,  s_pPathBbingOn,  s_pPathBbingOff,  this, menu_selector(PlayerLayer::menuCallbackBetBtns));
        btn4->setUserData((void*)4);
        btn4->setTag(404);
        CCMenuItem* btn5 = CCMenuItemImage::create(s_pPathCheckOn,  s_pPathCheckOn,  s_pPathCheckOff,  this, menu_selector(PlayerLayer::menuCallbackBetBtns));
        btn5->setUserData((void*)5);
        btn5->setTag(405);
        CCMenuItem* btn6 = CCMenuItemImage::create(s_pPathDieOn,    s_pPathDieOn,    s_pPathDieOff,    this, menu_selector(PlayerLayer::menuCallbackBetBtns));
        btn6->setUserData((void*)6);
        btn6->setTag(406);
        CCMenu* menu = CCMenu::create(btn1, btn2, btn3, btn4, btn5, btn6, NULL);
        menu->setVisible(false);

        static const int BTN_WIDTH = 64 + 2;
        static const int BTN_HEIGHT = 32 + 2;
        btn1->setPosition(ccp(BTN_WIDTH * 0, BTN_HEIGHT * 2)); btn1->setAnchorPoint(ccp(0, 0));
        btn2->setPosition(ccp(BTN_WIDTH * 1, BTN_HEIGHT * 2)); btn2->setAnchorPoint(ccp(0, 0));
        btn3->setPosition(ccp(BTN_WIDTH * 0, BTN_HEIGHT * 1)); btn3->setAnchorPoint(ccp(0, 0));
        btn4->setPosition(ccp(BTN_WIDTH * 1, BTN_HEIGHT * 1)); btn4->setAnchorPoint(ccp(0, 0));
        btn5->setPosition(ccp(BTN_WIDTH * 0, BTN_HEIGHT * 0)); btn5->setAnchorPoint(ccp(0, 0));
        btn6->setPosition(ccp(BTN_WIDTH * 1, BTN_HEIGHT * 0)); btn6->setAnchorPoint(ccp(0, 0));

        addChild(menu, 3, 400);

        CCPoint menuPos;
        menuPos.x = playerBoxPos[0].x - 50;
        menuPos.y = playerBoxPos[2].y - 50;
        menu->setPosition(menuPos);

    }

	m_pMainLogic = InstanceMan::mainLogic->GetInstance();

	m_kPokerSequence = POKERSEQUENCE_NONE;
    m_bMyBettingTurn = false;

	return true;
}

void PlayerLayer::menuCallbackBetBtns(CCObject* sender)
{
    ReadyBtns(0);

    void* userData = ((CCNode*)sender)->getUserData();
    Betting bet = BETTING_DIE;
    switch ((int)userData)
    {  
    case 1: bet = BETTING_HALF; break;
    case 2: bet = BETTING_QUARTER; break;
    case 3: bet = BETTING_CALL; break;
    case 4: bet = BETTING_BBING; break;
    case 5: bet = BETTING_CHECK; break;
    case 6: bet = BETTING_DIE; break;
    default: assert(0); break;
    }

    BettingInput betInput;
    betInput.ucPlayerIndex = 2;
    betInput.ucBetting = (unsigned char)bet;

    if (m_kPokerSequence == POKERSEQUENCE_BET1)
        betInput.ucBetIndex = 1;
    else if (m_kPokerSequence == POKERSEQUENCE_BET2)
        betInput.ucBetIndex = 2;
    else if (m_kPokerSequence == POKERSEQUENCE_BET3)
        betInput.ucBetIndex = 3;
    else if (m_kPokerSequence == POKERSEQUENCE_BET4)
        betInput.ucBetIndex = 4;
    betInput.ucTurnCount = m_kPlayerManInfo.turnCount;

    m_pMainLogic->SendPacket(&betInput);
}



void PlayerLayer::onEnter()
{
	CCLayer::onEnter();
	scheduleUpdate();
}

void PlayerLayer::update(float delta)
{
	CCLayer::update(delta);

    bool playerChanged = false;
    bool jokboChanged = false;
    bool dealChanged = false;
    bool seqChanged = false;
    bool playerManChanged = false;


	// player info
	PokerPlayerInfo playerInfos[MAX_POKERPLAYER_COUNT];
	m_pMainLogic->GetPlayerInfo(playerInfos);

	for (int i = 0; i < MAX_POKERPLAYER_COUNT; i++)
	{
		bool changed = m_kPlayerInfos[i].Changed(playerInfos[i]);
        playerChanged |= changed;
		if (changed)
		{
            DisplayPlayer(i, playerInfos[i]);
		}
	}

	// jokbo info
	JokboResult jokboInfos[MAX_POKERPLAYER_COUNT];
	m_pMainLogic->GetPlayerJokboInfo(jokboInfos);

	for (int i = 0; i < MAX_POKERPLAYER_COUNT; i++)
	{
		bool changed = m_kPlayerJokbo[i].Changed(jokboInfos[i]);
        jokboChanged |= changed;
		if (changed)
		{
			DisplayPlayerJokbo(i, jokboInfos[i]);
		}
	}


	// dealer info
	TableInfo tableInfo;
	m_pMainLogic->GetDealerInfo(tableInfo);
	bool dealerChanged = m_kTableInfo.Changed(tableInfo);
	if (dealerChanged)
	{
		DisplayDealer(tableInfo);
	}

	// sequence
	PokerSequence seq = m_pMainLogic->GetSequence();
	seqChanged = (m_kPokerSequence != seq);
	if (seqChanged)
	{
		DisplaySeq(seq);

		if (seq == POKERSEQUENCE_START || seq == POKERSEQUENCE_RESULT)
		{
            btnsTurnCount = 0;
            btnsBetIndex = 0;
			HideHandCards();
            ShowBetBtns(false);
            ShowTurnSun(false);
		}

        if (seq == POKERSEQUENCE_BET1 || seq == POKERSEQUENCE_BET2 ||
            seq == POKERSEQUENCE_BET3 || seq == POKERSEQUENCE_BET4)
        {
            ShowBetBtns(true);
            ReadyBtns(0);
            ShowTurnSun(true);
        }

        if (m_kPokerSequence == POKERSEQUENCE_BET1 || m_kPokerSequence == POKERSEQUENCE_BET2 ||
            m_kPokerSequence == POKERSEQUENCE_BET3 || m_kPokerSequence == POKERSEQUENCE_BET4)
        {
            ShowBetBtns(false);
            ShowTurnSun(false);
            ClearBetString();
        }
	}

    // player manager infos. sun/turn
    PlayerManInfo playerManInfo;
    m_pMainLogic->GetPlayerManInfo(playerManInfo);

    playerManChanged = m_kPlayerManInfo.Changed(playerManInfo);
    if (playerManChanged) 
    {
        DisplayPlayerMan(playerManInfo);
    }

    {// on enter turn 을 어떻게 알아낼 것인가?
        if (m_kPokerSequence == POKERSEQUENCE_BET1 || m_kPokerSequence == POKERSEQUENCE_BET2 ||
            m_kPokerSequence == POKERSEQUENCE_BET3 || m_kPokerSequence == POKERSEQUENCE_BET4)
        {
            enum BtnState
            {
                BS_NONE,
                BS_READY,
                BS_WAIT,
                BS_DISABLE,
            };
            BtnState bsState = BS_NONE;
            bool readyBtns = false;
            PokerPlayerInfo& turnPlayerInfo = playerInfos[m_kPlayerManInfo.turnIndex];
            if (turnPlayerInfo.onMyTurn)
            {
                bsState = BS_WAIT;
                if (btnsBetIndex != m_kPokerSequence || btnsTurnCount != m_kPlayerManInfo.turnCount)
                {
                    bsState = BS_READY;
                }
            }
            else 
            {
                bsState = BS_DISABLE;
            }

            if (bsState == BS_READY)
            {
                btnsBetIndex = m_kPokerSequence;
                btnsTurnCount = m_kPlayerManInfo.turnCount;
                ReadyBtns(turnPlayerInfo.ePrepareBetting);
            }
            else if (bsState == BS_DISABLE)
            {
                ReadyBtns(0);
            }
        }
    }

    {// on enter turn 을 어떻게 알아낼 것인가?
        if (m_kPokerSequence == POKERSEQUENCE_BET1 || m_kPokerSequence == POKERSEQUENCE_BET2 ||
            m_kPokerSequence == POKERSEQUENCE_BET3 || m_kPokerSequence == POKERSEQUENCE_BET4)
        {
            int betIndex = 0;
            if (m_kPokerSequence == POKERSEQUENCE_BET1)
                betIndex = 1;
            if (m_kPokerSequence == POKERSEQUENCE_BET2)
                betIndex = 2;
            if (m_kPokerSequence == POKERSEQUENCE_BET3)
                betIndex = 3;
            if (m_kPokerSequence == POKERSEQUENCE_BET4)
                betIndex = 4;

            for (int i = 0; i < MAX_POKERPLAYER_COUNT; i++)
            {
                bool changed = m_kPlayerInfos[i].Changed(playerInfos[i]);
                playerChanged |= changed;
                if (changed)
                {
                    DisplayBetting(i, betIndex, playerInfos[i]);
                }
            }
        }
    }


    if (playerChanged)
    {
        for (int i = 0; i < MAX_POKERPLAYER_COUNT; i++)
        {
            m_kPlayerInfos[i] = playerInfos[i];
        }
    }

    if (jokboChanged)
    {
        for (int i = 0; i < MAX_POKERPLAYER_COUNT; i++)
        {
            m_kPlayerJokbo[i] = jokboInfos[i];
        }
    }
    if (dealerChanged)
    {
        m_kTableInfo = tableInfo;
    }
    if (seqChanged)
    {
        m_kPokerSequence = seq;
    }
    if (playerManChanged) 
    {
        m_kPlayerManInfo = playerManInfo;
    }
}

void PlayerLayer::ShowBetBtns(bool show)
{
    int menuTag = 400;
    CCMenu* menu = (CCMenu*)getChildByTag(menuTag);
    if (menu)
    {
        menu->setVisible(show);
    }
}

void PlayerLayer::ShowTurnSun(bool show)
{
    CCSprite* trunImg = (CCSprite*)getChildByTag(300);
    if (trunImg)
        trunImg->setVisible(show);

    CCSprite* sunImg = (CCSprite*)getChildByTag(301);
    if (sunImg)
        sunImg->setVisible(show);
}

void PlayerLayer::ReadyBtns(int betting)
{
    int menuTag = 400;
    CCMenu* menu = (CCMenu*)getChildByTag(menuTag);
    if (menu)
    {
        CCMenuItem* btn1 = (CCMenuItem*)menu->getChildByTag(401);
        CCMenuItem* btn2 = (CCMenuItem*)menu->getChildByTag(402);
        CCMenuItem* btn3 = (CCMenuItem*)menu->getChildByTag(403);
        CCMenuItem* btn4 = (CCMenuItem*)menu->getChildByTag(404);
        CCMenuItem* btn5 = (CCMenuItem*)menu->getChildByTag(405);
        CCMenuItem* btn6 = (CCMenuItem*)menu->getChildByTag(406);

        // 하프  쿼터
        //  콜    삥
        // 체크  다이

        btn1->setEnabled(false);
        btn2->setEnabled(false);
        btn3->setEnabled(false);
        btn4->setEnabled(false);
        btn5->setEnabled(false);
        btn6->setEnabled(false);

        if (betting & BETTING_HALF)
            btn1->setEnabled(true);

        if (betting & BETTING_QUARTER)
            btn2->setEnabled(true);

        if (betting & BETTING_CALL)
            btn3->setEnabled(true);

        if (betting & BETTING_BBING)
            btn4->setEnabled(true);

        if (betting & BETTING_CHECK)
            btn5->setEnabled(true);

        if (betting & BETTING_DIE)
            btn6->setEnabled(true);
    }
}

void PlayerLayer::DisplayPlayer(int index, const PokerPlayerInfo& playerInfo)
{
	char pszInfo[256];
	playerInfo.GetStringInfo(pszInfo);

	char pszPlayerInfo[256];
	sprintf(pszPlayerInfo, "player %d \n %s ", index, pszInfo);
	CCLabelTTF* label = (CCLabelTTF*)getChildByTag(index);
	label->setString(pszPlayerInfo);

	DisplayPlayerHandCards(index, playerInfo);
}

void PlayerLayer::DisplayBetting(int index, int betIndex, const PokerPlayerInfo& playerInfo)
{
    char pszInfo[256];
    playerInfo.GetBetString(pszInfo, betIndex);

    CCLabelTTF* betLabel = (CCLabelTTF*)getChildByTag(500 + index);
    betLabel->setString(pszInfo);
}

void PlayerLayer::ClearBetString()
{
    for (int i = 0; i < MAX_POKERPLAYER_COUNT; i++)
    {
        CCLabelTTF* betLabel = (CCLabelTTF*)getChildByTag(500 + i);
        betLabel->setString("");
    }
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
    sunPlayerPos.y += 46;
    CCSprite* sunImg = (CCSprite*)getChildByTag(300);
    sunImg->setVisible(true);
    sunImg->setPosition(sunPlayerPos);

    CCPoint turnPlayerPos(GetPlayerPos(playerManInfo.turnIndex));
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
