#include "PlayerMan.h"
#include "Player.h"
#include "Dealer.h"
#include "PokerRule.h"
#include "PokerAI.h"

PlayerMan::PlayerMan()
{
}

PlayerMan::~PlayerMan()
{
}


bool PlayerMan::Init(PokerRule* rule, Dealer* dealer)
{
    m_pkPokerRule = rule;
    m_pkDealer = dealer;
    
	Clear();

	for (unsigned int i = 0; i < MAX_POKERPLAYER_COUNT; i++)
	{
		m_akPokerPlayer[i].Init();
	}

	// ù��° ���Կ� �������� �ִ´�.
	SetTestPlayer();

	return true;
}


void PlayerMan::OnEnterGame()
{

}
void PlayerMan::OnLeaveGame()
{

}


void PlayerMan::Update(float delta)
{
    PokerSequence sequence = m_pkPokerRule->GetCurPokerSequence();
    bool start = m_pkPokerRule->IsSequenceStart();

	 switch (sequence)
	 {
        case POKERSEQUENCE_START:
		{
			// ���� �����Ѵ�.
			m_kPlayerManInfo.m_nSunPlayerIndex = m_pkDealer->GetLastWinnerIndex();
			m_kPlayerManInfo.m_nTurnIndex = m_kPlayerManInfo.m_nSunPlayerIndex;
			//m_pkOwner->AddMoney(10, 4000);
			break;
		}
		case POKERSEQUENCE_SHUFFLE:
		{
			static float fDelayTime = 0.0f;
			fDelayTime += delta;

			if (fDelayTime < 0.1f)
			{
				break;
			}
			fDelayTime = 0.f;

			DoSchoolMoney();
			break;
		}
		case POKERSEQUENCE_CHOICE:
		{
			DoChoice();
			break;
		}
        case POKERSEQUENCE_CHOICE_DONE:
        {
            CalcJokboResult();
            FindSun();
            m_kPlayerManInfo.m_nTurnIndex = m_kPlayerManInfo.m_nSunPlayerIndex;
            break;
        }
        case POKERSEQUENCE_DEAL1_DONE:
        {
            CalcJokboResult();
            FindSun();
            m_kPlayerManInfo.m_nTurnIndex = m_kPlayerManInfo.m_nSunPlayerIndex;
            break;
        }
        case POKERSEQUENCE_BET1:
		{
			static float fDelayTime = 0.0f;
			fDelayTime += delta;

			if (fDelayTime < 1.5f)
			{
				break;
			}
			fDelayTime -= 1.5f;

			if (m_akPokerPlayer[m_kPlayerManInfo.m_nTurnIndex].DoBet1()) {
                unsigned int seedMoney = m_pkDealer->GetSeedMoney();
                unsigned int callMoney = m_pkDealer->GetCallMoney();
                unsigned int titleMoney = m_pkDealer->GetTitleMoney();
                m_akPokerPlayer[m_kPlayerManInfo.m_nTurnIndex].CalcBetMoney(1, seedMoney, callMoney, titleMoney);

                if (m_akPokerPlayer[m_kPlayerManInfo.m_nTurnIndex].IsRaiseUp(1)) {
                    m_pkDealer->AddRaiseCount();
                }
				SetTurnOver();
            }

			break;
		}
        case POKERSEQUENCE_DEAL2_DONE:
        {
            CalcJokboResult();
            FindSun();
            m_kPlayerManInfo.m_nTurnIndex = m_kPlayerManInfo.m_nSunPlayerIndex;
            break;
        }
        case POKERSEQUENCE_BET2:
		{
			static float fDelayTime = 0.0f;
			fDelayTime += delta;

			if (fDelayTime < 1.5f)
			{
				break;
			}
			fDelayTime -= 1.5f;

			if (m_akPokerPlayer[m_kPlayerManInfo.m_nTurnIndex].DoBet2()) {
				unsigned int seedMoney = m_pkDealer->GetSeedMoney();
				unsigned int callMoney = m_pkDealer->GetCallMoney();
				unsigned int titleMoney = m_pkDealer->GetTitleMoney();
				m_akPokerPlayer[m_kPlayerManInfo.m_nTurnIndex].CalcBetMoney(2, seedMoney, callMoney, titleMoney);

				if (m_akPokerPlayer[m_kPlayerManInfo.m_nTurnIndex].IsRaiseUp(2)) {
					m_pkDealer->AddRaiseCount();
				}
				SetTurnOver();
			}
			break;
		}
        case POKERSEQUENCE_DEAL3_DONE:
        {
            CalcJokboResult();
            FindSun();
            m_kPlayerManInfo.m_nTurnIndex = m_kPlayerManInfo.m_nSunPlayerIndex;
            break;
        }
        case POKERSEQUENCE_BET3:
		{
			static float fDelayTime = 0.0f;
			fDelayTime += delta;

			if (fDelayTime < 1.5f)
			{
				break;
			}
			fDelayTime -= 1.5f;

			if (m_akPokerPlayer[m_kPlayerManInfo.m_nTurnIndex].DoBet3()) {
				unsigned int seedMoney = m_pkDealer->GetSeedMoney();
				unsigned int callMoney = m_pkDealer->GetCallMoney();
				unsigned int titleMoney = m_pkDealer->GetTitleMoney();
				m_akPokerPlayer[m_kPlayerManInfo.m_nTurnIndex].CalcBetMoney(3, seedMoney, callMoney, titleMoney);

				if (m_akPokerPlayer[m_kPlayerManInfo.m_nTurnIndex].IsRaiseUp(3)) {
					m_pkDealer->AddRaiseCount();
				}
				SetTurnOver();
			}

			break;
		}
        case POKERSEQUENCE_DEAL4_DONE:
        {
            // Bet3 �߿� �÷��̾ Die�� ���� ���� �׷��� ���� �ٲ���� ����.
            CalcJokboResult();
            FindSun();
            m_kPlayerManInfo.m_nTurnIndex = m_kPlayerManInfo.m_nSunPlayerIndex;
            break;
        }
        case POKERSEQUENCE_BET4:
		{
			static float fDelayTime = 0.0f;
			fDelayTime += delta;

			if (fDelayTime < 1.5f)
			{
				break;
			}
			fDelayTime -= 1.5f;

			if (m_akPokerPlayer[m_kPlayerManInfo.m_nTurnIndex].DoBet4()) {
				unsigned int seedMoney = m_pkDealer->GetSeedMoney();
				unsigned int callMoney = m_pkDealer->GetCallMoney();
				unsigned int titleMoney = m_pkDealer->GetTitleMoney();
				m_akPokerPlayer[m_kPlayerManInfo.m_nTurnIndex].CalcBetMoney(4, seedMoney, callMoney, titleMoney);

				if (m_akPokerPlayer[m_kPlayerManInfo.m_nTurnIndex].IsRaiseUp(4)) {
					m_pkDealer->AddRaiseCount();
				}
				SetTurnOver();
			}

			break;
		}
        case POKERSEQUENCE_OPEN:
		{
			if (start) {
				CalcJokboResultLast();
			}
			break;
		}
        case POKERSEQUENCE_END:
		{
			if (start)
			{
				ClearPlayerIndex();
				ClearBettingInfo();
				// RemoveDisconnecter();

				// // ��ȭ�� ������ ������ ��� ����.
				// // �ٸ� �÷��̾���� �� ������ ���缭 ����Ѵ�.
				// // ���� �������� �־��ش�.

				// AddPlayer();
			}
			break;
		}

        default:
            break;
	}
}

void PlayerMan::DoSchoolMoney()
{
	if (m_akPokerPlayer[m_kPlayerManInfo.m_nTurnIndex].GetTempSchoolMoney() > 0)
		return;

	unsigned int seedMoney = m_pkDealer->GetSeedMoney();
	m_akPokerPlayer[m_kPlayerManInfo.m_nTurnIndex].CalcSchoolMoney(seedMoney);
	SetTurnOver();
}

bool PlayerMan::IsSchoolMoneyDone()
{
	unsigned int uiAlivePlayerCount = GetAlivePlayerCount();

	unsigned int uiSchoolMoneyDoneCount = 0;
	for (unsigned int ui = 0; ui < MAX_POKERPLAYER_COUNT; ui++)
	{
		if (m_akPokerPlayer[ui].GetPlayerState() == Player::PLAYERSTATE_NONE)
			continue;

		if (m_akPokerPlayer[ui].IsDie())
			continue;

		if (m_akPokerPlayer[ui].IsSchoolMoneyDone())
			uiSchoolMoneyDoneCount++;
	}

	return (uiAlivePlayerCount == uiSchoolMoneyDoneCount);
}

bool PlayerMan::IsChoiceDone() const
{
	unsigned int uiAlivePlayerCount = GetAlivePlayerCount();

	unsigned int uiChoiceDoneCount = 0;
	for (unsigned int ui = 0; ui < MAX_POKERPLAYER_COUNT; ui++)
	{
		if (m_akPokerPlayer[ui].GetPlayerState() == Player::PLAYERSTATE_NONE)
			continue;

		if (m_akPokerPlayer[ui].IsDie())
			continue;

		if (m_akPokerPlayer[ui].IsChoiceDone())
			uiChoiceDoneCount++;
	}

	return (uiAlivePlayerCount == uiChoiceDoneCount);
}

bool PlayerMan::IsBet1Done() const
{
	unsigned int uiAlivePlayerCount = GetAlivePlayerCount();

	unsigned int uiDoneCount = 0;
	for (unsigned int ui = 0; ui < MAX_POKERPLAYER_COUNT; ui++)
	{
		if (m_akPokerPlayer[ui].GetPlayerState() == Player::PLAYERSTATE_NONE)
			continue;

		if (m_akPokerPlayer[ui].IsDie())
			continue;

		if (m_akPokerPlayer[ui].IsBet1CheckOrCall())
			uiDoneCount++;
	}

	return (uiAlivePlayerCount == uiDoneCount);
}

bool PlayerMan::IsBet2Done() const
{
	unsigned int uiAlivePlayerCount = GetAlivePlayerCount();

	unsigned int uiDoneCount = 0;
	for (unsigned int ui = 0; ui < MAX_POKERPLAYER_COUNT; ui++)
	{
		if (m_akPokerPlayer[ui].GetPlayerState() == Player::PLAYERSTATE_NONE)
			continue;

		if (m_akPokerPlayer[ui].IsDie())
			continue;

		if (m_akPokerPlayer[ui].IsBet2CheckOrCall())
			uiDoneCount++;
	}

	return (uiAlivePlayerCount == uiDoneCount);
}

bool PlayerMan::IsBet3Done() const
{
	unsigned int uiAlivePlayerCount = GetAlivePlayerCount();

	unsigned int uiDoneCount = 0;
	for (unsigned int ui = 0; ui < MAX_POKERPLAYER_COUNT; ui++)
	{
		if (m_akPokerPlayer[ui].GetPlayerState() == Player::PLAYERSTATE_NONE)
			continue;

		if (m_akPokerPlayer[ui].IsDie())
			continue;

		if (m_akPokerPlayer[ui].IsBet3CheckOrCall())
			uiDoneCount++;
	}

	return (uiAlivePlayerCount == uiDoneCount);
}

bool PlayerMan::IsBet4Done() const
{
	unsigned int uiAlivePlayerCount = GetAlivePlayerCount();

	unsigned int uiDoneCount = 0;
	for (unsigned int ui = 0; ui < MAX_POKERPLAYER_COUNT; ui++)
	{
		if (m_akPokerPlayer[ui].GetPlayerState() == Player::PLAYERSTATE_NONE)
			continue;

		if (m_akPokerPlayer[ui].IsDie())
			continue;

		if (m_akPokerPlayer[ui].IsBet4CheckOrCall())
			uiDoneCount++;
	}

	return (uiAlivePlayerCount == uiDoneCount);
}

void PlayerMan::Clear()
{
	ClearPlayerIndex();
	ClearBettingInfo();
}

void PlayerMan::ClearPlayerIndex()
{
	m_kPlayerManInfo.Clear();
}

void PlayerMan::ClearBettingInfo()
{
	for (int i = 0; i < MAX_POKERPLAYER_COUNT; i++)
	{
		m_akPokerPlayer[i].ClearBettingInfo();
	}
}

void PlayerMan::AddPlayer()
{
	// ������ ����Ʈ���� ������ �� �÷��̾���� PokerPlayer�� �ִ´�.
}

void PlayerMan::AddAIPlayer()
{
	for (unsigned int ui = 0; ui < MAX_POKERPLAYER_COUNT; ui++)
	{
		if (m_akPokerPlayer[ui].GetPlayerState() == Player::PLAYERSTATE_NONE)
		{
			m_akPokerPlayer[ui].SetComputer();
		}
	}
}
void PlayerMan::RemoveDisconnecter()
{
	for (unsigned int ui = 0; ui < MAX_POKERPLAYER_COUNT; ui++)
	{
		if (m_akPokerPlayer[ui].GetPlayerState() == Player::PLAYERSTATE_DISCONNECTER)
		{
			m_akPokerPlayer[ui].Remove();
		}
	}
}

void PlayerMan::SetTestPlayer()
{
	// ù��° ���Կ� �ӽ÷� �� ������ �ִ´�.

	static const unsigned int nPlayerKey = 100;
	static const unsigned int nPlayerIndex = 0;

	m_kPlayerManInfo.m_nCurPlayerKey = nPlayerKey;
	m_kPlayerManInfo.m_nCurPlayerIndex = nPlayerIndex;
    
    for (int i = 0; i < MAX_POKERPLAYER_COUNT; i++) {
        if (i == m_kPlayerManInfo.m_nCurPlayerIndex) {
            m_akPokerPlayer[i].SetPlayerInfo(Player::PLAYERSTATE_LIVE, 100, 100000);
        } 
        else {
            m_akPokerPlayer[i].SetPlayerInfo(Player::PLAYERSTATE_COMPUTER, INVALID_PLAYER_INDEX, 100000);
        }
    }
}

void PlayerMan::DoChoice()
{
	// ������ ��ǻ�Ͱ� �� ���� �����Ѵ�.
	// �������� �˾ƾ� �Ѵ�.  �������� ��������ϴ°�?
	// �������� �˷��� �������� ���� masterplayerkey�� �־�� �ϰ� ���� �������� �Ź� ��������Ѵ�.
	for (unsigned int i = 0; i < MAX_POKERPLAYER_COUNT; i++)
	{
		m_akPokerPlayer[i].DoChoice();
	}
}

unsigned int PlayerMan::GetMasterPlayerKey() const
{
	return 0;
}

unsigned int PlayerMan::GetCurPlayerKey() const
{
	return m_kPlayerManInfo.m_nCurPlayerKey;
}

unsigned int PlayerMan::GetAlivePlayerCount() const
{
	unsigned int nAlivePlayerCount = 0;
	for (unsigned int i = 0; i < MAX_POKERPLAYER_COUNT; i++)
	{
		if (m_akPokerPlayer[i].GetPlayerState() == Player::PLAYERSTATE_NONE)
			continue;

		if (m_akPokerPlayer[i].IsDie())
			continue;
		nAlivePlayerCount++;
	}

	return nAlivePlayerCount;
}

bool PlayerMan::IsLeaveAlone() const
{
	return (GetAlivePlayerCount() == 1);
}

unsigned int PlayerMan::GetSunIndex() const
{
	return m_kPlayerManInfo.m_nSunPlayerIndex;
}

bool PlayerMan::IsMaster() const
{
	return (0 == m_kPlayerManInfo.m_nCurPlayerKey);
}

Player& PlayerMan::GetPlayerByIndex(unsigned int index)
{
	return m_akPokerPlayer[index];
}

const Player& PlayerMan::GetPlayerByIndex(unsigned int index) const
{
	return m_akPokerPlayer[index];
}

int PlayerMan::GetHighJokboPlayer()
{
	int highJokboPlayerIndex = -1;
	for (int i = 0; i < MAX_POKERPLAYER_COUNT; i++)
	{
		const JokboResult kJokboResult = m_akPokerPlayer[i].GetJokboResult();
		if (kJokboResult.eJokbo == JOKBO_NONE)
			continue;

		highJokboPlayerIndex = i;
		break;
	}


	for (int i = 0; i < MAX_POKERPLAYER_COUNT; i++)
	{
		if (m_akPokerPlayer[i].GetJokboResult().eJokbo == JOKBO_NONE)
			continue;

		if (highJokboPlayerIndex == i)
			continue;

        JokboResult lhs = m_akPokerPlayer[highJokboPlayerIndex].GetJokboResult();
        JokboResult rhs = m_akPokerPlayer[i].GetJokboResult();
		if (PokerAI::CompareJokbo(lhs, rhs)) {
			highJokboPlayerIndex = i;
		}
	}
    
    return highJokboPlayerIndex;
}

void PlayerMan::FindSun()
{
    int highJokboPlayerIndex = GetHighJokboPlayer();
    if (highJokboPlayerIndex == -1) {
        // ��� die ����?
        highJokboPlayerIndex = 0;
    }
    m_kPlayerManInfo.m_nSunPlayerIndex = highJokboPlayerIndex;
}

void PlayerMan::CalcJokboResult()
{
	for (unsigned int i = 0; i < MAX_POKERPLAYER_COUNT; i++)
	{
		m_akPokerPlayer[i].CalcJokboResult();
	}
}

void PlayerMan::CalcJokboResultLast()
{
	for (unsigned int i = 0; i < MAX_POKERPLAYER_COUNT; i++)
	{
		m_akPokerPlayer[i].CalcJokboResultLast();
	}
}


void PlayerMan::IsAllCall() const
{


}

void PlayerMan::SetTurnOver()
{
	unsigned int uiNextTurnIndex = 0;
	for (unsigned int ui = m_kPlayerManInfo.m_nTurnIndex + 1; ui < m_kPlayerManInfo.m_nTurnIndex + 1 + MAX_POKERPLAYER_COUNT; ui++)
	{
		uiNextTurnIndex = ui;
		if (uiNextTurnIndex >= MAX_POKERPLAYER_COUNT)
			uiNextTurnIndex -= MAX_POKERPLAYER_COUNT;

		if (m_akPokerPlayer[uiNextTurnIndex].GetPlayerState() == Player::PLAYERSTATE_NONE)
			continue;
		if (m_akPokerPlayer[uiNextTurnIndex].IsDie())
			continue;

		break;
	}

	m_kPlayerManInfo.m_nTurnIndex = uiNextTurnIndex;
}

void PlayerMan::GetPlayerInfo(PokerPlayerInfo playerInfos[])
{
	for (int i = 0; i < MAX_POKERPLAYER_COUNT; i++) 
	{
		m_akPokerPlayer[i].GetPlayerInfo(playerInfos[i]);
	}

}