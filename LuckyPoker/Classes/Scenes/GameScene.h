#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "Model/PokerDefines.h"

class MainLogic;

USING_NS_CC;

class GameBGLayer : public CCLayer
{
public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();
	virtual void update(float delta);

	// implement the "static node()" method manually
	CREATE_FUNC(GameBGLayer);

    // a selector callback
    void menuBackCallback(CCObject* pSender);
};

class PlayerLayer : public CCLayer
{
public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();  
	virtual void onEnter();
	virtual void update(float delta);

    void menuCallbackBetBtns(CCObject* pSender);


	// implement the "static node()" method manually
	CREATE_FUNC(PlayerLayer);

private:
    void DisplayPlayer(int index, const PokerPlayerInfo& playerInfo);
    void DisplayBetting(int index, int betIndex, const PokerPlayerInfo& playerInfo);
	void DisplayPlayerHandCards(int index, const PokerPlayerInfo& playerInfo);
	void DisplayPlayerJokbo(int index, const JokboResult& playerInfo);
	void DisplayDealer(const TableInfo& tableInfo);
    void DisplaySeq(PokerSequence seq);
    void DisplayPlayerMan(const PlayerManInfo& playerManInfo);
	void HideHandCards();
    void ShowBetBtns(bool show);
    void ShowTurnSun(bool show);
    void ReadyBtns(int betting);
    void ClearBetString();


    CCPoint GetPlayerPos(int playerIndex) const;
    CCPoint GetPlayerNamePos(int playerIndex) const;
    CCPoint GetPlayerMoneyPos(int playerIndex) const;
    CCPoint GetSequencePos() const;
    CCPoint GetTableMoneyPos() const;
    CCPoint GetCallMoneyPos() const;
    CCPoint GetMyTableMoneyPos() const;
    CCPoint GetBettingInfoPos(int playerIndex) const;
    CCPoint GetCardSpritePos(int playerIndex, int cardIndex) const;
    CCPoint GetJokboLabelPos(int playerIndex) const;
    CCPoint GetTurnBoxPos(int playerIndex) const;
    CCPoint GetSunPos(int playerIndex) const;

    int GetPlayerNameTag(int playerIndex) const;
    int GetPlayerMoneyTag(int playerIndex) const;
    int GetSequenceTag() const;
    int GetTableMoneyTag() const;
    int GetCallMoneyTag() const;
    int GetMyTableMoneyTag() const;
    int GetBettingInfoTag(int playerIndex) const;

    int GetCardSpriteTag(int playerIndex, int cardIndex) const;
    int GetJokboLabelTag(int playerIndex, int labelIndex) const;

    int GetTurnBoxTag() const;
    int GetSunTag() const;

private:
	MainLogic* m_pMainLogic;

	PlayerManInfo   m_kPlayerManInfo;
	PokerPlayerInfo m_kPlayerInfos[MAX_POKERPLAYER_COUNT];
	JokboResult		m_kPlayerJokbo[MAX_POKERPLAYER_COUNT];
	TableInfo       m_kTableInfo;
	PokerSequence   m_kPokerSequence;
    bool            m_bMyBettingTurn;

    int btnsTurnCount;
    int btnsBetIndex;

};


class GameScene : public CCScene
{
public:
    virtual bool init();  

    virtual void onEnter();
    virtual void onExit();
	virtual void update(float delta);
	void UpdateLogic(float delta);


	//static GameScene* create();
    static GameScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    
    // implement the "static node()" method manually
    CREATE_FUNC(GameScene);

private:
	MainLogic* m_pMainLogic;
};

#endif // __GAME_SCENE_H__
