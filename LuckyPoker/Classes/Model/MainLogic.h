#ifndef __MAIN_LOGIC_H__
#define __MAIN_LOGIC_H__

#include "cocos2d.h"

#include "PokerRule.h"
#include "Dealer.h"
#include "PlayerMan.h"
#include "PokerRule.h"

USING_NS_CC;

class MainLogic : public CCObject
{
public:
    static MainLogic* GetInstance();
    static void FreeInstance();

    MainLogic();
    virtual ~MainLogic();
    virtual bool Init();

    virtual void update(float delta);

	void GetPlayerInfo(PokerPlayerInfo playerInfos[]);
	void GetPlayerJokboInfo(JokboResult jokboInfos[]);
    void GetDealerInfo(TableInfo& tableInfo);
    void GetPlayerManInfo(PlayerManInfo& playerManInfo);
	PokerSequence GetSequence();

    void SendPacket(BettingInput* betInput);
    void ReceivePacket(BettingInput* betInput);

    
private:
    static MainLogic* s_pLogic;

	PokerRule m_kRule;
    Dealer m_kDealer;
	PlayerMan m_kPlayerMan;
    PokerRule m_kPokerRule;
};

#endif // __MAIN_LOGIC_H__
