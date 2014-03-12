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
		m_akPokerPlayer[i].Init(dealer);
	}

	// 첫번째 슬롯에 내정보를 넣는다.
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
			// 선을 정리한다.
			m_kPlayerManInfo.sunPlayerIndex = m_pkDealer->GetLastWinnerIndex();
			m_kPlayerManInfo.turnIndex = m_kPlayerManInfo.sunPlayerIndex;
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
            m_kPlayerManInfo.turnIndex = m_kPlayerManInfo.sunPlayerIndex;
            break;
        }
        case POKERSEQUENCE_DEAL1_DONE:
        {
            CalcJokboResult();
            FindSun();
            m_kPlayerManInfo.turnCount = 0;
            m_kPlayerManInfo.turnIndex = m_kPlayerManInfo.sunPlayerIndex;
            bool myTurn = (m_kPlayerManInfo.turnIndex == m_kPlayerManInfo.curPlayerIndex);
            m_akPokerPlayer[m_kPlayerManInfo.turnIndex].OnEnterTurn(myTurn);
            break;
        }
        case POKERSEQUENCE_BET1:
		{
			EachPlayerBetting(1, delta);
			break;
		}
        case POKERSEQUENCE_DEAL2_DONE:
        {
            CalcJokboResult();
            FindSun();
            m_kPlayerManInfo.turnCount = 0;
            m_kPlayerManInfo.turnIndex = m_kPlayerManInfo.sunPlayerIndex;
            bool myTurn = (m_kPlayerManInfo.turnIndex == m_kPlayerManInfo.curPlayerIndex);
            m_akPokerPlayer[m_kPlayerManInfo.turnIndex].OnEnterTurn(myTurn);
            break;
        }
        case POKERSEQUENCE_BET2:
		{
			EachPlayerBetting(2, delta);
			break;
		}
        case POKERSEQUENCE_DEAL3_DONE:
        {
            CalcJokboResult();
            FindSun();
            m_kPlayerManInfo.turnCount = 0;
            m_kPlayerManInfo.turnIndex = m_kPlayerManInfo.sunPlayerIndex;
            bool myTurn = (m_kPlayerManInfo.turnIndex == m_kPlayerManInfo.curPlayerIndex);
            m_akPokerPlayer[m_kPlayerManInfo.turnIndex].OnEnterTurn(myTurn);
            break;
        }
        case POKERSEQUENCE_BET3:
		{
			EachPlayerBetting(3, delta);
			break;
		}
        case POKERSEQUENCE_DEAL4_DONE:
        {
            // Bet3 중에 플레이어가 Die할 수도 있음 그래서 선이 바뀔수도 있음.
            CalcJokboResult();
            FindSun();
            m_kPlayerManInfo.turnCount = 0;
            m_kPlayerManInfo.turnIndex = m_kPlayerManInfo.sunPlayerIndex;
            bool myTurn = (m_kPlayerManInfo.turnIndex == m_kPlayerManInfo.curPlayerIndex);
            m_akPokerPlayer[m_kPlayerManInfo.turnIndex].OnEnterTurn(myTurn);
            break;
        }
        case POKERSEQUENCE_BET4:
		{
			EachPlayerBetting(4, delta);
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
                m_kPlayerManInfo.turnCount = 0;
				ClearPlayerIndex();
				ClearBettingInfo();
				// RemoveDisconnecter();

				// // 변화의 요인이 없으면 계속 간다.
				// // 다른 플레이어들이 다 나가면 멈춰서 대기한다.
				// // 새로 들어왔으면 넣어준다.

				// AddPlayer();
			}
			break;
		}

        default:
            break;
	}
}

void PlayerMan::EachPlayerBetting(int betIndex, float delta)
{
    if (m_kPlayerManInfo.turnIndex == 2){
        int aa = 0;
        aa++;
    }
    Player& player = m_akPokerPlayer[m_kPlayerManInfo.turnIndex];
    BetAction betAction = player.Thinking(betIndex, delta);

    if (betAction == BET_ACTION_BETTING) 
    {
        bool result = player.DoBetting(betIndex, BETTING_NONE);

        if (result) {
            unsigned int seedMoney = m_pkDealer->GetSeedMoney();
            unsigned int callMoney = m_pkDealer->GetCallMoney();
            unsigned int titleMoney = m_pkDealer->GetTitleMoney();
            player.CalcBetMoney(betIndex, seedMoney, callMoney, titleMoney);

            if (player.IsRaiseUp(betIndex)) {
                m_pkDealer->AddRaiseCount();
            }
        }
    }
    else if (betAction == BET_ACTION_DONE) 
    {
        m_kPlayerManInfo.turnCount++;
        SetTurnOver();
    }
}

void PlayerMan::DoSchoolMoney()
{
	if (m_akPokerPlayer[m_kPlayerManInfo.turnIndex].GetTempSchoolMoney() > 0)
		return;

	unsigned int seedMoney = m_pkDealer->GetSeedMoney();
	m_akPokerPlayer[m_kPlayerManInfo.turnIndex].CalcSchoolMoney(seedMoney);
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
	// 웨이터 리스트에서 게임을 할 플레이어들을 PokerPlayer에 넣는다.
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
	static const unsigned int nPlayerKey = 100;
	static const unsigned int nPlayerIndex = 2;

	m_kPlayerManInfo.curPlayerKey = nPlayerKey;
	m_kPlayerManInfo.curPlayerIndex = nPlayerIndex;
    
    for (int i = 0; i < MAX_POKERPLAYER_COUNT; i++) {
        if (i == m_kPlayerManInfo.curPlayerIndex) {
            m_akPokerPlayer[i].SetPlayerInfo(Player::PLAYERSTATE_LIVE, 100, 100000);
        } 
        else {
            m_akPokerPlayer[i].SetPlayerInfo(Player::PLAYERSTATE_COMPUTER, INVALID_PLAYER_INDEX, 100000);
        }
    }
}

void PlayerMan::DoChoice()
{
	// 방장이 컴퓨터가 할 일을 결정한다.
	// 방장인지 알아야 한다.  누구한테 물어봐야하는가?
	// 방장인지 알려면 룸정보에 방장 masterplayerkey가 있어야 하고 내가 방장인지 매번 물어봐야한다.
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
	return m_kPlayerManInfo.curPlayerKey;
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
	return m_kPlayerManInfo.sunPlayerIndex;
}

bool PlayerMan::IsMaster() const
{
	return (0 == m_kPlayerManInfo.curPlayerKey);
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
        // 모두 die 상태?
        highJokboPlayerIndex = 0;
    }
    m_kPlayerManInfo.sunPlayerIndex = highJokboPlayerIndex;
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
	for (unsigned int ui = m_kPlayerManInfo.turnIndex + 1; ui < m_kPlayerManInfo.turnIndex + 1 + MAX_POKERPLAYER_COUNT; ui++)
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


    m_akPokerPlayer[m_kPlayerManInfo.turnIndex].OnLeaveTurn();
	m_kPlayerManInfo.turnIndex = uiNextTurnIndex;
    bool myTurn = (m_kPlayerManInfo.turnIndex == m_kPlayerManInfo.curPlayerIndex);
    m_akPokerPlayer[m_kPlayerManInfo.turnIndex].OnEnterTurn(myTurn);
}

void PlayerMan::GetPlayerInfo(PokerPlayerInfo playerInfos[])
{
	for (int i = 0; i < MAX_POKERPLAYER_COUNT; i++) 
	{
		m_akPokerPlayer[i].GetPlayerInfo(playerInfos[i]);
	}
}

void PlayerMan::GetPlayerJokbo(JokboResult jokboInfos[])
{
	for (int i = 0; i < MAX_POKERPLAYER_COUNT; i++) 
	{
		m_akPokerPlayer[i].GetPlayerJokbo(jokboInfos[i]);
	}
}

void PlayerMan::GetPlayerManInfo(PlayerManInfo& playerManInfo)
{
    playerManInfo = m_kPlayerManInfo;
}


void PlayerMan::ReceivePacket(BettingInput* betInput)
{
    unsigned int playerIndex = betInput->ucPlayerIndex;
    unsigned int turnCount = betInput->ucTurnCount;
    int betIndex = betInput->ucBetIndex;
    Betting betting = (Betting)betInput->ucBetting;

    if (m_kPlayerManInfo.curPlayerIndex != playerIndex)
    {
        assert(0);
        return;
    }
    if (m_kPlayerManInfo.turnCount != turnCount)
    {
        assert(0);
        return;
    }

    Player& myTurnPlayer = m_akPokerPlayer[betInput->ucPlayerIndex];

    if (myTurnPlayer.IsThinking()) {
        myTurnPlayer.StopThinking();
        bool result = myTurnPlayer.DoBetting(betIndex, betting);

        if (result) {
            unsigned int seedMoney = m_pkDealer->GetSeedMoney();
            unsigned int callMoney = m_pkDealer->GetCallMoney();
            unsigned int titleMoney = m_pkDealer->GetTitleMoney();
            myTurnPlayer.CalcBetMoney(betIndex, seedMoney, callMoney, titleMoney);

            if (myTurnPlayer.IsRaiseUp(betIndex)) {
                m_pkDealer->AddRaiseCount();
            }
        }
    }
    else 
    {
        // 패킷이 너무 늦게 왔거나 패킷 내용이 이상하다.
        assert(0);
        return;
    }
}