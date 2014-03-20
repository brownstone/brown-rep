#include "PokerRule.h"
#include "PlayerMan.h"

PokerRule::PokerRule()
{
}

PokerRule::~PokerRule()
{
}

bool PokerRule::Init(PlayerMan* playerMan)
{
    m_pkPlayerMan = playerMan;
    InitSequence();
    return true;
}

void PokerRule::Clear()
{
}

void PokerRule::InitSequence()
{
    m_eCurPokerSequence = POKERSEQUENCE_NONE;
    m_fAccumTime = 0.0f;
    m_bSequenceChanged = false;
}

void PokerRule::Update(float delta)
{
	UpdateSequence(delta);
}

void PokerRule::UpdateSequence(float delta)
{
	static const float START_TIME = 0.0f;
	static const float SHUFFLE_TIME = 2.0f;
	static const float DEALFIRSTCARD_TIME = 2.0f;
	static const float CHOICE_TIME = 2.0f;
	static const float CHOICE_DONE_TIME = 5.0f;
	static const float DEAL1_TIME = 4.0f;
	static const float DEAL1_DONE_TIME = 0.0f;
	static const float BET1_TIME = 60.0f;
	static const float DEAL2_TIME = 2.0f;
	static const float DEAL2_DONE_TIME = 0.0f;
	static const float BET2_TIME = 60.0f;
	static const float DEAL3_TIME = 2.0f;
	static const float DEAL3_DONE_TIME = 0.0f;
	static const float BET3_TIME = 60.0f;
	static const float DEAL4_TIME = 2.0f;
	static const float SHOW_HIDDEN_TIME = 2.0f;
	static const float DEAL4_DONE_TIME = 0.0f;
	static const float BET4_TIME = 60.0f;
	static const float HILOW_TIME = 2.0f;
	static const float OPEN_TIME = 0.0f;
	static const float SETTLE_TIME = 4.0f;
	static const float RESULT_TIME = 5.0f;
	static const float END_TIME = 0.0f;

    float MAX_TIME = 0;
	switch (m_eCurPokerSequence)
	{
	case POKERSEQUENCE_NONE:			MAX_TIME = START_TIME;  break;
	case POKERSEQUENCE_START:			MAX_TIME = START_TIME;  break;
	case POKERSEQUENCE_SHUFFLE:			MAX_TIME = SHUFFLE_TIME;  break;
	case POKERSEQUENCE_DEALFIRSTCARD:	MAX_TIME = DEALFIRSTCARD_TIME;	break;
	case POKERSEQUENCE_CHOICE:			MAX_TIME = CHOICE_TIME;	break;
	case POKERSEQUENCE_CHOICE_DONE:		MAX_TIME = CHOICE_DONE_TIME;	break;
	case POKERSEQUENCE_DEAL1:			MAX_TIME = DEAL1_TIME;	break;
	case POKERSEQUENCE_DEAL1_DONE:		MAX_TIME = DEAL1_DONE_TIME;	break;
	case POKERSEQUENCE_BET1:			MAX_TIME = BET1_TIME;	break;
	case POKERSEQUENCE_DEAL2:			MAX_TIME = DEAL2_TIME;	break;
	case POKERSEQUENCE_DEAL2_DONE:		MAX_TIME = DEAL2_DONE_TIME;	break;
	case POKERSEQUENCE_BET2:			MAX_TIME = BET2_TIME;	break;
	case POKERSEQUENCE_DEAL3:			MAX_TIME = DEAL3_TIME;	break;
    case POKERSEQUENCE_DEAL3_DONE:		MAX_TIME = DEAL3_DONE_TIME;	break;
	case POKERSEQUENCE_BET3:			MAX_TIME = BET3_TIME;	break;
	case POKERSEQUENCE_DEAL4:			MAX_TIME = DEAL4_TIME;	break;
	case POKERSEQUENCE_SHOW_HIDDEN:		MAX_TIME = SHOW_HIDDEN_TIME;	break;
	case POKERSEQUENCE_DEAL4_DONE:	    MAX_TIME = DEAL4_DONE_TIME;	break;
	case POKERSEQUENCE_BET4:			MAX_TIME = BET4_TIME;	break;
	case POKERSEQUENCE_HILOW:			MAX_TIME = HILOW_TIME;	break;
	case POKERSEQUENCE_OPEN:			MAX_TIME = OPEN_TIME;	break;
	case POKERSEQUENCE_SETTLE: 			MAX_TIME = SETTLE_TIME;	break;
	case POKERSEQUENCE_RESULT:			MAX_TIME = RESULT_TIME;	break;
	case POKERSEQUENCE_END:				MAX_TIME = END_TIME;	break;
	}

	switch (m_eCurPokerSequence)
	{
	case POKERSEQUENCE_SHUFFLE:
	case POKERSEQUENCE_DEALFIRSTCARD:
	case POKERSEQUENCE_CHOICE:
	case POKERSEQUENCE_CHOICE_DONE:
	case POKERSEQUENCE_DEAL1:
	case POKERSEQUENCE_DEAL1_DONE:
	case POKERSEQUENCE_BET1:
	case POKERSEQUENCE_DEAL2:
	case POKERSEQUENCE_DEAL2_DONE:
	case POKERSEQUENCE_BET2:
	case POKERSEQUENCE_DEAL3:
	case POKERSEQUENCE_DEAL3_DONE:
	case POKERSEQUENCE_BET3:
	case POKERSEQUENCE_DEAL4:
	case POKERSEQUENCE_SHOW_HIDDEN:
	case POKERSEQUENCE_DEAL4_DONE:
	case POKERSEQUENCE_BET4:
	case POKERSEQUENCE_HILOW:
		bool alone = m_pkPlayerMan->IsLeaveAlone();
		if (alone)
			ChangeToSequence(POKERSEQUENCE_SETTLE);
	}

    
    m_fAccumTime += delta;
    
    m_bSequenceChanged = false;
    bool timeout = false;
    bool jobdone = false;
    if (m_fAccumTime > MAX_TIME) {
        timeout = true;
    }
    
    if (timeout == false) {
        switch (m_eCurPokerSequence)
        {
        case POKERSEQUENCE_CHOICE:		jobdone = m_pkPlayerMan->IsChoiceDone();	break;
        case POKERSEQUENCE_BET1:		jobdone = m_pkPlayerMan->IsBetDone(1);	break;
        case POKERSEQUENCE_BET2:		jobdone = m_pkPlayerMan->IsBetDone(2);	break;
        case POKERSEQUENCE_BET3:		jobdone = m_pkPlayerMan->IsBetDone(3);	break;
        case POKERSEQUENCE_BET4:		jobdone = m_pkPlayerMan->IsBetDone(4);	break;
        }
    }

    if (timeout || jobdone) {
		ChangeToSequence((PokerSequence)(m_eCurPokerSequence + 1));
    }
}

void PokerRule::ChangeToSequence(PokerSequence newSeq)
{
	m_fAccumTime = 0.0f;
	m_bSequenceChanged = true;
	m_eCurPokerSequence = newSeq;
	if (m_eCurPokerSequence >= POKERSEQUENCE_MAX) {
		m_eCurPokerSequence = POKERSEQUENCE_START;
	}

}

PokerSequence PokerRule::GetCurPokerSequence() const
{
	return m_eCurPokerSequence;
}

