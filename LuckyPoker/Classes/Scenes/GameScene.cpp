#include "GameScene.h"
#include "Assist/InstanceMan.h"
#include "Model/MainLogic.h"
#include "../ResourceString.h"
#include "scenes/SelectScene.h"

bool GameBGLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }

    //CCLayerColor* background = CCLayerColor::create(ccc4(155, 155, 155, 255));
    //addChild(background);



    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    CCSprite* pSprite = CCSprite::create("Images/bg.png");
    pSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(pSprite, 0);


    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    CCMenuItemFont *item_1 = CCMenuItemFont::create("Menu", this, menu_selector(GameBGLayer::menuBackCallback));
    item_1->setPosition(ccp(origin.x + visibleSize.width - item_1->getContentSize().width/2 - 100 ,
        origin.y + item_1->getContentSize().height/2));

    // add a "close" icon to exit the progress. it's an autorelease object
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
        "CloseNormal.png", "CloseSelected.png", this, menu_selector(GameScene::menuCloseCallback));
    pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
        origin.y + pCloseItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(item_1, pCloseItem, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);


    return true;
}

void GameBGLayer::update(float delta)
{
	CCLayer::update(delta);
}

void GameBGLayer::menuBackCallback(CCObject* pSender)
{
    CCLOG("Intro complete, begin SelectScene");
    //MainLogic* mainLogic = InstanceMan::mainLogic->GetInstance();
    //if (mainLogic)
    //{
    //    mainLogic->Init()
    //}

    CCScene* pScene = SelectScene::scene();
    CCDirector::sharedDirector()->replaceScene(pScene);
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


CCPoint PlayerLayer::GetPlayerNamePos(int playerIndex) const
{
    if (playerIndex >= MAX_POKERPLAYER_COUNT) {
        return CCPoint(0,0);
    }

    int playerPosX[5];
    int playerPosY[5];
    playerPosX[0] = 1160;	playerPosY[0] = 480;
    playerPosX[1] = 1160;	playerPosY[1] = 312;
    playerPosX[2] = 360;	playerPosY[2] = 59;
    playerPosX[3] = 150;	playerPosY[3] = 312;
    playerPosX[4] = 150;	playerPosY[4] = 480;

    return CCPoint(playerPosX[playerIndex], playerPosY[playerIndex]);

}

CCPoint PlayerLayer::GetPlayerMoneyPos(int playerIndex) const
{
    if (playerIndex >= MAX_POKERPLAYER_COUNT) {
        return CCPoint(0,0);
    }

    int playerPosX[5];
    int playerPosY[5];
    playerPosX[0] = 980;	playerPosY[0] = 480;
    playerPosX[1] = 980;	playerPosY[1] = 312;
    playerPosX[2] = 620;	playerPosY[2] = 59;
    playerPosX[3] = 340;	playerPosY[3] = 312;
    playerPosX[4] = 340;	playerPosY[4] = 480;

    return CCPoint(playerPosX[playerIndex], playerPosY[playerIndex]);
}

CCPoint PlayerLayer::GetSequencePos() const
{
    return CCPoint(640, 680);
}

CCPoint PlayerLayer::GetTableMoneyPos() const
{
    return CCPoint(700, 456);
}

CCPoint PlayerLayer::GetCallMoneyPos() const
{
    return CCPoint(700, 420);
}

CCPoint PlayerLayer::GetMyTableMoneyPos() const
{
    return CCPoint(700, 388);
}

CCPoint PlayerLayer::GetBettingInfoPos(int playerIndex) const
{
    if (playerIndex >= MAX_POKERPLAYER_COUNT) {
        return CCPoint(0,0);
    }

    int playerPosX[5];
    int playerPosY[5];
    playerPosX[0] = 800;	playerPosY[0] = 550;
    playerPosX[1] = 800;	playerPosY[1] = 350;
    playerPosX[2] = 550;	playerPosY[2] = 280;
    playerPosX[3] = 500;	playerPosY[3] = 350;
    playerPosX[4] = 500;	playerPosY[4] = 550;

    return CCPoint(playerPosX[playerIndex], playerPosY[playerIndex]);
}

CCPoint PlayerLayer::GetCardSpritePos(int playerIndex, int cardIndex) const
{
    if (playerIndex >= MAX_POKERPLAYER_COUNT) {
        return CCPoint(0,0);
    }
    if (cardIndex >= MAX_HANDCARD_COUNT) {
        return CCPoint(0,0);
    }

    int xoffset = cardIndex * 20;

    int playerPosX[5];
    int playerPosY[5];
    playerPosX[0] = 860 + xoffset;	playerPosY[0] = 560;
    playerPosX[1] = 860 + xoffset;	playerPosY[1] = 390;
    playerPosX[2] = 520 + xoffset;	playerPosY[2] = 150;
    playerPosX[3] = 260 + xoffset;	playerPosY[3] = 390;
    playerPosX[4] = 260 + xoffset;	playerPosY[4] = 560;

    return CCPoint(playerPosX[playerIndex], playerPosY[playerIndex]);
}


CCPoint PlayerLayer::GetJokboLabelPos(int playerIndex) const
{
    CCPoint pos = GetCardSpritePos(playerIndex, 3);
    pos.y -= 40;

    return pos;
}

CCPoint PlayerLayer::GetTurnBoxPos(int playerIndex) const
{
    if (playerIndex >= MAX_POKERPLAYER_COUNT) {
        return CCPoint(0,0);
    }

    CCPoint pos = GetPlayerNamePos(playerIndex);
    pos.y += 60;

    return pos;
}

CCPoint PlayerLayer::GetSunPos(int playerIndex) const
{
    if (playerIndex >= MAX_POKERPLAYER_COUNT) {
        return CCPoint(0,0);
    }

    CCPoint pos = GetCardSpritePos(playerIndex, 0);
    pos.y += 60;

    return pos;
}

int PlayerLayer::GetPlayerNameTag(int playerIndex) const
{
    return playerIndex + 0;
}

int PlayerLayer::GetPlayerMoneyTag(int playerIndex) const
{
    return playerIndex + 10;
}

int PlayerLayer::GetSequenceTag() const
{
    return 20;
}

int PlayerLayer::GetTableMoneyTag() const
{
    return 30;
}

int PlayerLayer::GetCallMoneyTag() const
{
    return 40;
}

int PlayerLayer::GetMyTableMoneyTag() const
{
    return 50;
}

int PlayerLayer::GetBettingInfoTag(int playerIndex) const
{
    return playerIndex + 70;
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

int PlayerLayer::GetTurnBoxTag() const
{
    return 300;

}
int PlayerLayer::GetSunTag() const
{
    return 310;

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


    CCLabelTTF* pLabel;
    // names
    for (int i = 0; i < MAX_POKERPLAYER_COUNT; i++)
    {
	    pLabel = CCLabelTTF::create("Player name", "Arial", 20);
	    pLabel->setPosition(GetPlayerNamePos(i));
	    this->addChild(pLabel, 1, GetPlayerNameTag(i));
    }

    // moneys     right align
    for (int i = 0; i < MAX_POKERPLAYER_COUNT; i++)
    {
        pLabel = CCLabelTTF::create("", "Arial", 20);
        pLabel->setPosition(GetPlayerMoneyPos(i));
        this->addChild(pLabel, 1, GetPlayerMoneyTag(i));
    }


    // seq
    pLabel = CCLabelTTF::create("cequence", "Arial", 20);
    pLabel->setPosition(GetSequencePos());
    this->addChild(pLabel, 1, GetSequenceTag());

    // Table money
    pLabel = CCLabelTTF::create("", "Arial", 20);
    pLabel->setPosition(GetTableMoneyPos());
    this->addChild(pLabel, 1, GetTableMoneyTag());
    // call money
    pLabel = CCLabelTTF::create("", "Arial", 20);
    pLabel->setPosition(GetCallMoneyPos());
    this->addChild(pLabel, 1, GetCallMoneyTag());
    // My table money
    pLabel = CCLabelTTF::create("", "Arial", 20);
    pLabel->setPosition(GetMyTableMoneyPos());
    this->addChild(pLabel, 1, GetMyTableMoneyTag());


    // Betting info
    for (int i = 0; i < MAX_POKERPLAYER_COUNT; i++)
    {
        pLabel = CCLabelTTF::create(" ", "Arial", 18);
        pLabel->setPosition(GetBettingInfoPos(i));
        pLabel->setColor(ccBLUE);
        this->addChild(pLabel, 1, GetBettingInfoTag(i));
    }



	{ // players hand card
		static const int SMALL_CARD_WIDTH = 14;
		for (int i = 0; i < MAX_POKERPLAYER_COUNT; i++)
		{
			for (int j = 0; j < MAX_HANDCARD_COUNT; j++)
			{
				CCSprite* cardImg = CCSprite::create();
				cardImg->setPosition(GetCardSpritePos(i, j));
				cardImg->setVisible(false);
				addChild(cardImg, 1, GetCardSpriteTag(i, j));
			}
		}
	}

	{ // jokbo
		for (int i = 0; i < MAX_POKERPLAYER_COUNT; i++)
		{
			pLabel = CCLabelTTF::create(" ", "Arial", 18);
			pLabel->setPosition(GetJokboLabelPos(i));
			pLabel->setColor(ccYELLOW);
			this->addChild(pLabel, 2, GetJokboLabelTag(i, 0));
		}
	}
	{ // turn, sun
        CCSprite* turnImg = CCSprite::create(s_pPathPBoxTurn);
        turnImg->setPosition(GetTurnBoxPos(0));
        turnImg->setVisible(false);
        addChild(turnImg, 1, GetTurnBoxTag());

        CCSprite* sunImg = CCSprite::create(s_pPathSun);
		sunImg->setPosition(GetSunPos(0));
		sunImg->setVisible(false);
		addChild(sunImg, 1, GetSunTag());

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
        menuPos.x = 900;
        menuPos.y = 150;
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
    CCSprite* trunImg = (CCSprite*)getChildByTag(GetTurnBoxTag());
    if (trunImg)
        trunImg->setVisible(show);

    CCSprite* sunImg = (CCSprite*)getChildByTag(GetSunTag());
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


	char pszPlayerInfo[256];
	sprintf(pszPlayerInfo, "player %d", index);
    CCLabelTTF* label;
    label = (CCLabelTTF*)getChildByTag(GetPlayerNameTag(index));
	label->setString(pszPlayerInfo);

    label = (CCLabelTTF*)getChildByTag(GetPlayerMoneyTag(index));
    sprintf(pszPlayerInfo, "%d", playerInfo.nTotalMoney);
    label->setString(pszPlayerInfo);

	DisplayPlayerHandCards(index, playerInfo);
}

void PlayerLayer::DisplayBetting(int index, int betIndex, const PokerPlayerInfo& playerInfo)
{
    char pszInfo[256];
    playerInfo.GetBetString(pszInfo, betIndex);

    CCLabelTTF* betLabel = (CCLabelTTF*)getChildByTag(GetBettingInfoTag(index));
    betLabel->setString(pszInfo);
}

void PlayerLayer::ClearBetString()
{
    for (int i = 0; i < MAX_POKERPLAYER_COUNT; i++)
    {
        CCLabelTTF* betLabel = (CCLabelTTF*)getChildByTag(GetBettingInfoTag(i));
        betLabel->setString("");
    }
}

static const char* GetCardImgName(int num)
{
    static const char* cardImgName[] = {
        "Images/cards/b1fv.png",
        "Images/cards/c1.png", "Images/cards/c2.png", "Images/cards/c3.png", "Images/cards/c4.png", "Images/cards/c5.png", "Images/cards/c6.png", "Images/cards/c7.png", "Images/cards/c8.png", "Images/cards/c9.png", "Images/cards/c10.png", "Images/cards/cj.png", "Images/cards/cq.png", "Images/cards/ck.png",
        "Images/cards/d1.png", "Images/cards/d2.png", "Images/cards/d3.png", "Images/cards/d4.png", "Images/cards/d5.png", "Images/cards/d6.png", "Images/cards/d7.png", "Images/cards/d8.png", "Images/cards/d9.png", "Images/cards/d10.png", "Images/cards/dj.png", "Images/cards/dq.png", "Images/cards/dk.png",
        "Images/cards/h1.png", "Images/cards/h2.png", "Images/cards/h3.png", "Images/cards/h4.png", "Images/cards/h5.png", "Images/cards/h6.png", "Images/cards/h7.png", "Images/cards/h8.png", "Images/cards/h9.png", "Images/cards/h10.png", "Images/cards/hj.png", "Images/cards/hq.png", "Images/cards/hk.png",
        "Images/cards/s1.png", "Images/cards/s2.png", "Images/cards/s3.png", "Images/cards/s4.png", "Images/cards/s5.png", "Images/cards/s6.png", "Images/cards/s7.png", "Images/cards/s8.png", "Images/cards/s9.png", "Images/cards/s10.png", "Images/cards/sj.png", "Images/cards/sq.png", "Images/cards/sk.png"
    };

    return cardImgName[num];
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
                const char* cardImgName = GetCardImgName((int)card.GetCard());
                cardSprite->setVisible(true);
                cardSprite->initWithFile(cardImgName);

				//static const int CARD_WIDTH = 20;
				//static const int CARD_HEIGHT = 40;

				//int cardY = card.GetPicture() * CARD_HEIGHT;
				//int cardX = card.GetNumber() * CARD_WIDTH;

				//cardSprite->setVisible(true);
				//cardSprite->initWithFile("Images/smallcards.png", CCRect(cardX, cardY, CARD_WIDTH, CARD_HEIGHT));
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

	CCLabelTTF* label;
    label = (CCLabelTTF *)getChildByTag(GetTableMoneyTag());
    sprintf(pszInfo, "%d", tableInfo.titleMoney);
    label->setString(pszInfo);
    label = (CCLabelTTF *)getChildByTag(GetCallMoneyTag());
    sprintf(pszInfo, "%d", tableInfo.callMoney);
    label->setString(pszInfo);
    label = (CCLabelTTF *)getChildByTag(GetMyTableMoneyTag());
    label->setString("0");
}

void PlayerLayer::DisplaySeq(PokerSequence seq)
{
	char pszInfo[256];
	sprintf(pszInfo, "ceq: %s ", PokerSequenceStr[seq]);
	CCLabelTTF *label = (CCLabelTTF *)getChildByTag(GetSequenceTag());
	label->setString(pszInfo);

}

void PlayerLayer::DisplayPlayerMan(const PlayerManInfo& playerManInfo)
{
    CCPoint sunPlayerPos(GetSunPos(playerManInfo.sunPlayerIndex));
    CCSprite* sunImg = (CCSprite*)getChildByTag(GetSunTag());
    sunImg->setVisible(true);
    sunImg->setPosition(sunPlayerPos);

    CCPoint turnPlayerPos(GetTurnBoxPos(playerManInfo.turnIndex));
    CCSprite* turnImg = (CCSprite*)getChildByTag(GetTurnBoxTag());
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
