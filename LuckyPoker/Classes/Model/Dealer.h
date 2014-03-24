#ifndef __DEALER_H__
#define __DEALER_H__

#include "PokerDefines.h"

class PokerRule;
class PlayerMan;

class Dealer
{
public:
    Dealer();
    virtual ~Dealer();
    
    bool Init(PokerRule* rule, PlayerMan* playerMan);
    void Clear();
    
    void Update(float delta);
    void PostUpdate(float delta);
    void AddMoney(unsigned int money);
    
    int GetLastWinnerIndex();
    unsigned int GetSeedMoney();
    unsigned int GetCallMoney();
    unsigned int GetTitleMoney();
    void AddRaiseCount();
    unsigned int GetRaiseCount();

    void GetDealerInfo(DealerInfo& dealerInfo);
    void GetTableInfo(TableInfo& tableInfo);

    
protected:
    Card::PokerCard GetCardFromDeck();
    void ResetRaiseCount();
    void ResetTitleMoney();
    void Shuffle();
	void CalcSchoolMoney();
    void DealFirstCard();
    void CalcMoney(int betIndex);
    void Settle();
    void SetCallMoney(unsigned int money);
    void DoDeal(int betIndex);
    
    
private:
    DealerInfo          m_kDealerInfo;
    //unsigned int        m_nMasterPlayerKey;
    //unsigned int        m_nGameCount;
    //unsigned int        m_nMostMoney;
    //unsigned int        m_nLastWinnerIndex; // 다음판에 패를 나눠줄때 이넘 다음부터
    //unsigned int        m_nLastWinnerPrice;
    Card::PokerCard	    m_kCardDeck[Card::MAX_CARD_COUNT];
    unsigned int        m_nCardDeckIndex;

	// table data
	TableInfo           m_kTableInfo;
    
    PokerRule*          m_pkPokerRule;
    PlayerMan*          m_pkPlayerMan;
    
};

#endif // __DEALER_H__
