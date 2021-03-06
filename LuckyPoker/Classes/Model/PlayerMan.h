#ifndef __PLAYER_MAN_H__
#define __PLAYER_MAN_H__

//#include "PokerDefines.h"
#include "Player.h"

class PokerRule;
class Dealer;

class PlayerMan
{
public:
    PlayerMan();
    virtual ~PlayerMan();
    
    bool Init(PokerRule* rule, Dealer* dealer);
	void Clear();

	void OnEnterGame();
	void OnLeaveGame();

	void Update(float delta);

	void DoSchoolMoney();
	bool IsSchoolMoneyDone();
    void DoChoice();
	bool IsChoiceDone() const;
	void EachPlayerBetting(int betIndex, float delta);
	bool IsBetDone(int betIndex);
	void Choice();
	void Settle();
	unsigned int GetMasterPlayerKey() const;
	unsigned int GetCurPlayerKey() const;
	unsigned int GetAlivePlayerCount() const;
	bool IsLeaveAlone() const;
	Player& GetPlayerByIndex(unsigned int index);
	const Player& GetPlayerByIndex(unsigned int index) const;
	unsigned int GetSunIndex() const;
	bool IsMaster() const;
	void FindSun();
	void CalcJokboResult();
	void CalcJokboResultLast();
    int GetHighJokboPlayer();

	void GetPlayerInfo(PokerPlayerInfo playerInfos[]);
	void GetPlayerJokbo(JokboResult jokboInfos[]);
    void GetPlayerManInfo(PlayerManInfo& playerManInfo);

    void ReceivePacket(BettingInput* betInput);

    void BetTurnOver(int betIndex);

    int GetPlayersMoney();


protected:
	void AddPlayer();
	void AddAIPlayer();
	void RemoveDisconnecter();
	void SetTestPlayer();
	void ClearPlayerIndex();
	void ClearBettingInfo();
	void IsAllCall() const;
	void SetTurnOver();
    void AlivePlayer();


protected:
	Player          m_akPokerPlayer[MAX_POKERPLAYER_COUNT];
	PlayerManInfo   m_kPlayerManInfo;

    Dealer*         m_pkDealer;
    PokerRule*      m_pkPokerRule;

};

#endif // __PLAYER_MAN_H__
