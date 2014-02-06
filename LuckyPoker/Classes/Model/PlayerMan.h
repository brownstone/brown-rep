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

    void DoChoice();
	bool IsChoiceDone() const;
	bool IsBet1Done() const;
	bool IsBet2Done() const;
	bool IsBet3Done() const;
	bool IsBet4Done() const;
	void Choice();
	void Settle();
	unsigned int GetMasterPlayerKey() const;
	unsigned int GetCurPlayerKey() const;
	unsigned int GetAlivePlayerCount() const;
	Player& GetPlayerByIndex(unsigned int index);
	const Player& GetPlayerByIndex(unsigned int index) const;
	unsigned int GetSunIndex() const;
	bool IsMaster() const;
	void FindSun();
	void CalcJokboResult();
	void CalcJokboResultLast();
    int GetHighJokboPlayer();

	void GetPlayerInfo(PokerPlayerInfo playerInfos[]);



protected:
	void AddPlayer();
	void AddAIPlayer();
	void RemoveDisconnecter();
	void SetTestPlayer();
	void ClearPlayerIndex();
	void ClearBettingInfo();
	void IsAllCall() const;
	void SetTurnOver();


protected:
	Player          m_akPokerPlayer[MAX_POKERPLAYER_COUNT];
	PlayerManInfo   m_kPlayerManInfo;

    Dealer*         m_pkDealer;
    PokerRule*      m_pkPokerRule;

};

#endif // __PLAYER_MAN_H__
