#ifndef __POKER_AI_H__
#define __POKER_AI_H__

#include "PokerDefines.h"

class PokerRule;
class Dealer;
class PlayerMan;


class PokerAI
{
public:
    PokerAI();
    virtual ~PokerAI();
    
    bool Init(PokerRule* rule, Dealer* dealer, PlayerMan* playerMan);
    void Clear();
    
    void Update(float delta);
    
	//void GetJokboResultForFindSun(const Player::PokerPlayerInfo& kPokerPlayerInfo, JokboResult& kJokboResult) const;
	//void GetJokboResultForSettle(const Player::PokerPlayerInfo& kPokerPlayerInfo, JokboResult& kJokboResult) const;

    static void CalcJokbo(CardBit& kCardBit, JokboResult& kJokboResult);
    static bool CompareJokbo(const JokboResult& lhs, const JokboResult& rhs);


protected:
    void ThinkAI();
    
private:
    AiWeight            m_kBetWeights[MAX_POKERPLAYER_COUNT];
    
    PokerRule*          m_pkPokerRule;
    Dealer*             m_pkDealer;
    PlayerMan*          m_pkPlayerMan;

};

#endif // __POKER_AI_H__
