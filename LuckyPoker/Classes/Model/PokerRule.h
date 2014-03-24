#ifndef __POKER_RULE_H__
#define __POKER_RULE_H__

#include "PokerDefines.h"

class PlayerMan;

class PokerRule
{
public:
    PokerRule();
    virtual ~PokerRule();
    
    bool Init(PlayerMan* playerMan);
    void Clear();
    
    void UpdateSequence(float delta);
    void Update(float delta);
    
	PokerSequence GetCurPokerSequence() const;
    bool IsSequenceStart() const { return m_bSequenceChanged; }
    
protected:
	PokerSequence m_eCurPokerSequence;
    bool m_bSequenceChanged;
    float m_fAccumTime;

    float m_fFirstDealTime;
    float m_fDeal1Time;
    float m_fDeal2Time;
    float m_fDeal3Time;
    float m_fDeal4Time;

	void ChangeToSequence(PokerSequence seq);
    
private:
    void InitSequence();
    
    PlayerMan*  m_pkPlayerMan;
    
};

#endif // __POKER_RULE_H__
