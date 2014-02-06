#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "PokerDefines.h"
#include "Card.h"

class PokerRule;
class Dealer;

class Player
{
public:
    Player();
    virtual ~Player();
    
    bool Init();
    void Clear();

    void ClearBettingInfo();
    
    void Update();
    
	enum PokerPlayerState
	{
		PLAYERSTATE_NONE,
		PLAYERSTATE_LIVE,
		PLAYERSTATE_DISCONNECTER,
		PLAYERSTATE_COMPUTER,
	};


    void SetPlayerInfo(PokerPlayerState state, int playerKey, int money);

    PokerPlayerState GetPlayerState() const;
    
    void DoChoice();
    bool DoBet1();
    bool DoBet2();
    bool DoBet3();
    bool DoBet4();
    
    bool IsDie() const;
    bool IsChoiceDone() const;
    bool IsBet1CheckOrCall() const;
    bool IsBet2CheckOrCall() const;
    bool IsBet3CheckOrCall() const;
    bool IsBet4CheckOrCall() const;
    void SetDeal3Card(const Deal3CardInfo& kCardInfo);
    void SetDealCard(const DealCardInfo& kCardInfo, int nIndex);
    void SetHiddenCard(const DealCardInfo& kCardInfo, int nIndex);
    const JokboResult& GetJokboResult() const;
    void CalcJokboResult();
    void CalcJokboResultLast();
    void AddMoney(unsigned int money);

    bool IsRaiseUp(int betIndex);
    void CalcBetMoney(int betIndex, unsigned int seedMoney, unsigned int callMoney, unsigned int titleMoney);
    Betting GetLastBetting(int betIndex);
    unsigned int GetTempBetMoney(int betIndex);
    unsigned int GetLastBetMoney(int betIndex);
    void ExactCalc(int betIndex);
    Betting GetBetting(Betting ePriviousBetting) const;

    void GetStringInfo(char szInformation[]) const;
    //char* GetJokboStringInfo(Jokbo eJokbo, char szCard[]) const
    //char* GetCardStringInfo(const Card& kCard, char szCard[]) const

	void GetPlayerInfo(PokerPlayerInfo& playerInfo);

    void SetComputer();
    void Remove();

    
protected:
	PokerPlayerState	m_ePlayerState;
	PokerPlayerInfo		m_kPokerPlayerInfo;

	JokboResult			m_kJokboResult;


};

#endif // __PLAYER_H__