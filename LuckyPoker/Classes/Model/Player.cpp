#include "cocos2d.h"
#include "Player.h"
#include "Dealer.h"
#include "PokerAI.h"



Player::Player()
{
}

Player::~Player()
{
}

bool Player::Init(Dealer* dealer)
{
    m_pkDealer = dealer;
    Clear();
	return true;
}

// ----------------------------------------------------------------
void Player::Update()
{
}

void Player::Clear()
{
	ClearBettingInfo();
}

void Player::ClearBettingInfo()
{
    m_kPokerPlayerInfo.ClearBettingInfo();
}

Player::PokerPlayerState Player::GetPlayerState() const
{
	return m_ePlayerState;
}

void Player::SetPlayerInfo(PokerPlayerState state, int playerKey, int money)
{
	m_ePlayerState = state;
	m_kPokerPlayerInfo.nPlayerKey = playerKey;
	m_kPokerPlayerInfo.nTotalMoney = money;
}

void Player::DoChoice()
{
	switch (m_ePlayerState)
	{
	case PLAYERSTATE_NONE:
		break;
	case PLAYERSTATE_LIVE:
		{
			// ����ڴ� ���� �Ѵ�.
			if (m_kPokerPlayerInfo.bChoice == false)
			{
				// �켱 �ӽ÷� �����ϰ� �Ѵ�.
				// ���� �����Ҽ� �ֵ��� �ؾ��Ѵ�.
                m_kPokerPlayerInfo.akOpenCard[0]   = m_kPokerPlayerInfo.akFirstCard[0];
                m_kPokerPlayerInfo.akHiddenCard[0] = m_kPokerPlayerInfo.akFirstCard[1];
                m_kPokerPlayerInfo.akHiddenCard[1] = m_kPokerPlayerInfo.akFirstCard[2];
                m_kPokerPlayerInfo.bChoice = true;
			}
			break;
		}
	case PLAYERSTATE_COMPUTER:
	case PLAYERSTATE_DISCONNECTER:
		{
            m_kPokerPlayerInfo.akOpenCard[0]   = m_kPokerPlayerInfo.akFirstCard[0];
            m_kPokerPlayerInfo.akHiddenCard[0] = m_kPokerPlayerInfo.akFirstCard[1];
            m_kPokerPlayerInfo.akHiddenCard[1] = m_kPokerPlayerInfo.akFirstCard[2];
            m_kPokerPlayerInfo.bChoice = true;
			break;
		}
	default:
		break;
	}
}

Betting Player::GetLastBetting(int betIndex)
{
    Betting bet = BETTING_NONE;
    if (betIndex == 1) {
        bet = m_kPokerPlayerInfo.eBet1;
    } else if (betIndex == 2) {
        bet = m_kPokerPlayerInfo.eBet2;
    } else if (betIndex == 3) {
        bet = m_kPokerPlayerInfo.eBet3;
    } else if (betIndex == 4) {
        bet = m_kPokerPlayerInfo.eBet4;
    }

    return bet;
}

void Player::CalcSchoolMoney(unsigned int seedMoney)
{
	m_kPokerPlayerInfo.nTempSchoolMoney = seedMoney;
}

void Player::CalcBetMoney(int betIndex, unsigned int seedMoney, unsigned int callMoney, unsigned int titleMoney)
{
    Betting bet = BETTING_NONE;
    unsigned int lastBetMoney = 0;
    unsigned int totalMondy = 0;
    
    bet = GetLastBetting(betIndex);
    lastBetMoney = GetLastBetMoney(betIndex);

    if (bet == BETTING_NONE)
        return;
        
    switch (bet)
    {
    case BETTING_DIE:
        {
            totalMondy = 0;
            m_kPokerPlayerInfo.bDie = true;
            break;
        }
    case BETTING_CHECK:
        {
            // �ϴ����� ����.
            break;
        }
    case BETTING_BBING:
        {
            totalMondy = seedMoney;
            break;
        }
    case BETTING_CALL:
        {
            unsigned int requiredCallMoney = callMoney - lastBetMoney;
            totalMondy = requiredCallMoney;
            break;
        }
    case BETTING_QUARTER:
        {
            unsigned int requiredCallMoney  = callMoney - lastBetMoney;
            unsigned int raiseMoney = (titleMoney + callMoney) * 0.25f;
            totalMondy = requiredCallMoney + raiseMoney;
            break;
        }
    case BETTING_HALF:
        {
            unsigned int requiredCallMoney  = callMoney - lastBetMoney;
            unsigned int raiseMoney = (titleMoney + requiredCallMoney) * 0.5f;
            totalMondy = requiredCallMoney + raiseMoney;
            break;
        }
    case BETTING_FULL:
        {
            unsigned int requiredCallMoney  = callMoney - lastBetMoney;
            unsigned int raiseMoney = titleMoney + requiredCallMoney;
            totalMondy = requiredCallMoney + raiseMoney;
            break;
        }
    }

    if (betIndex == 1) {
        m_kPokerPlayerInfo.nTempBet1Money = totalMondy;
    } else if (betIndex == 2) {
        m_kPokerPlayerInfo.nTempBet2Money = totalMondy;
    } else if (betIndex == 3) {
        m_kPokerPlayerInfo.nTempBet3Money = totalMondy;
    } else if (betIndex == 4) {
        m_kPokerPlayerInfo.nTempBet4Money = totalMondy;
    }
}

bool Player::IsRaiseUp(int betIndex)
{
    Betting bet = GetLastBetting(betIndex);

    if (bet == BETTING_BBING || 
        bet == BETTING_QUARTER || 
        bet == BETTING_HALF || 
        bet == BETTING_FULL)  {
            return true;
    }

    return false;
}

void Player::ExactCalc(int betIndex)
{
	if (betIndex == 1) {
		m_kPokerPlayerInfo.nTotalMoney -= m_kPokerPlayerInfo.nTempBet1Money;
		m_kPokerPlayerInfo.nLastBet1Money += m_kPokerPlayerInfo.nTempBet1Money;
		m_kPokerPlayerInfo.nTempBet1Money = 0;
	} else if (betIndex == 2) {
		m_kPokerPlayerInfo.nTotalMoney -= m_kPokerPlayerInfo.nTempBet2Money;
		m_kPokerPlayerInfo.nLastBet2Money += m_kPokerPlayerInfo.nTempBet1Money;
		m_kPokerPlayerInfo.nTempBet2Money = 0;
	} else if (betIndex == 3) {
		m_kPokerPlayerInfo.nTotalMoney -= m_kPokerPlayerInfo.nTempBet3Money;
		m_kPokerPlayerInfo.nLastBet3Money += m_kPokerPlayerInfo.nTempBet3Money;
		m_kPokerPlayerInfo.nTempBet3Money = 0;
	} else if (betIndex == 4) {
		m_kPokerPlayerInfo.nTotalMoney -= m_kPokerPlayerInfo.nTempBet4Money;
		m_kPokerPlayerInfo.nLastBet4Money += m_kPokerPlayerInfo.nTempBet4Money;
		m_kPokerPlayerInfo.nTempBet4Money = 0;
	}
}

void Player::ExactCalcSchoolMoney()
{
	m_kPokerPlayerInfo.nTotalMoney -= m_kPokerPlayerInfo.nTempSchoolMoney;
	m_kPokerPlayerInfo.nTempSchoolMoney = 0;
	m_kPokerPlayerInfo.bSchoolMoney = true;
}

unsigned int Player::GetTempSchoolMoney()
{
	return m_kPokerPlayerInfo.nTempSchoolMoney;
}

void Player::OnEnterTurn(bool myTurn)
{
    float thinkTime = 1.0f;
    if (myTurn)
    {
        thinkTime = 10.0f;
    }
    m_kPokerPlayerInfo.eBetAction = BET_ACTION_THINK_PREPARE;
    m_kPokerPlayerInfo.fThinkTime = thinkTime;
    m_kPokerPlayerInfo.fThrowTime = 0.6f;
    m_kPokerPlayerInfo.onMyTurn = myTurn;
}

void Player::OnLeaveTurn()
{
    m_kPokerPlayerInfo.onMyTurn = false;
}

int Player::GetPrepareBetting(int betIndex)
{
    int result = BETTING_DIE;
    unsigned int raiseCount = m_pkDealer->GetRaiseCount();
    unsigned int callMoney = m_pkDealer->GetCallMoney();
    unsigned int titleMoney = m_pkDealer->GetTitleMoney();
    Betting ePriviousBetting = BETTING_NONE;
    bool canQuater = ((unsigned int)(titleMoney * 0.25f) < m_kPokerPlayerInfo.nTotalMoney);
    bool canHalf = ((unsigned int)(titleMoney * 0.5f) < m_kPokerPlayerInfo.nTotalMoney);

    if (betIndex == 1) 
        ePriviousBetting = m_kPokerPlayerInfo.eBet1;
    else if (betIndex == 2)
        ePriviousBetting = m_kPokerPlayerInfo.eBet2;
    else if (betIndex == 3)
        ePriviousBetting = m_kPokerPlayerInfo.eBet3;
    else if (betIndex == 4)
        ePriviousBetting = m_kPokerPlayerInfo.eBet4;

    if (raiseCount == 0)
    {   // ý, ��, ����, ����, Ǯ�� �Ҽ� �ִ� // ��, ���̽��� �Ҽ� ����.
        result = BETTING_BBING | BETTING_CHECK | BETTING_QUARTER | BETTING_HALF | BETTING_DIE;
    }
    else
    {
        if (ePriviousBetting == BETTING_CALL || ePriviousBetting == BETTING_CHECK)
        {   // ���̳� ���̳�?
            result = BETTING_CALL | BETTING_DIE;
        }
        else //  if (ePriviousBetting == BETTING_QUARTER || ePriviousBetting == BETTING_HALF || ePriviousBetting == BETTING_FULL)
        {
            // ���� ���̽����� ������ �� ���̽��Ҽ� �ִ�
            // ó���Ҷ�, ��, ����, ����, Ǯ (üũ�� ������)
            // ������ ��, ���̽�, ����...

            if (raiseCount < 2)
            {
                result = BETTING_CALL | BETTING_QUARTER | BETTING_HALF | BETTING_DIE;
            }
            else
            {
                result = BETTING_CALL | BETTING_DIE;
            }
        }
    }

    if (!canHalf) 
    {
        result &= ~BETTING_HALF;
    }
    if (!canQuater) 
    {
        result &= ~BETTING_QUARTER;
    }

    return result;
}

BetAction Player::Thinking(int betIndex, float delta)
{
    switch (m_kPokerPlayerInfo.eBetAction)
    {
    case BET_ACTION_THINK_PREPARE:
        m_kPokerPlayerInfo.ePrepareBetting = (Betting)GetPrepareBetting(betIndex);
        m_kPokerPlayerInfo.eBetAction = BET_ACTION_THINK;
        break;
    case BET_ACTION_THINK: 
        m_kPokerPlayerInfo.fThinkTime -= delta;
        if (m_kPokerPlayerInfo.onMyTurn) 
        {
            if (m_kPokerPlayerInfo.fThinkTime < 0.5f)
            {
                m_kPokerPlayerInfo.onMyTurn = false;
            }

        }
        if (m_kPokerPlayerInfo.fThinkTime < 0.0f) 
        {
            m_kPokerPlayerInfo.eBetAction = BET_ACTION_BETTING;
        }
        break;
    case BET_ACTION_BETTING:
        m_kPokerPlayerInfo.eBetAction = BET_ACTION_THROW;
        break;
    case BET_ACTION_THROW:
        m_kPokerPlayerInfo.fThrowTime -= delta;
        if (m_kPokerPlayerInfo.fThrowTime < 0.0f)
        {
            m_kPokerPlayerInfo.eBetAction = BET_ACTION_DONE;
        }
        break;
    default: assert(0); break;
    }

    return m_kPokerPlayerInfo.eBetAction;
}

bool Player::IsThinking()
{
    return (m_kPokerPlayerInfo.eBetAction == BET_ACTION_THINK);
}

void Player::StopThinking()
{
    m_kPokerPlayerInfo.eBetAction = BET_ACTION_THROW;
}

Betting Player::GetBetting(Betting ePriviousBetting) const
{
	// ���� ���� �ִ� �ݾװ� ī��� ���� ī�带 ���� ���� �����ϴ� �ڵ尡 �־���Ѵ�.

    const Betting BET_LIMIT = BETTING_QUARTER;
	Betting eResult = BETTING_NONE;
    unsigned int uiRaiseCount = m_pkDealer->GetRaiseCount();

	if (uiRaiseCount == 0)
	{
		// ó���̶�� ����
		// ý, ��, ����, ����, Ǯ�� �Ҽ� �ִ�
		// ��, ���̽��� �Ҽ� ����.
		int nRnd = rand() % 4;
		if (nRnd == 0)
		{
			eResult = BETTING_BBING;
		}
		else if (nRnd == 1)
		{
			eResult = BETTING_CHECK;
		}
		else if (nRnd == 2)
		{
			eResult = BETTING_BBING;
		}
		else if (nRnd == 3)
		{
            eResult = BET_LIMIT;
		}
	}
	else
	{
		if (ePriviousBetting == BETTING_CALL || ePriviousBetting == BETTING_CHECK)
		{
			// ���̳� ���̳�?
			int nRnd = rand() % 2;
			if (nRnd == 0)
			{
				eResult = BETTING_DIE;
			}
			else if (nRnd == 1)
			{
				eResult = BETTING_CALL;
			}
		}
		else //  if (ePriviousBetting == BETTING_QUARTER || ePriviousBetting == BETTING_HALF || ePriviousBetting == BETTING_FULL)
		{
			// ���� ���̽����� ������ �� ���̽��Ҽ� �ִ�
			// ó���Ҷ�, ��, ����, ����, Ǯ (üũ�� ������)
			// ������ ��, ���̽�, ����...

			if (uiRaiseCount < 2)
			{
				int nRnd = rand() % 3;
				if (nRnd == 0)
				{
					eResult = BETTING_CALL;
				}
				else if (nRnd == 1)
				{
					eResult = BETTING_DIE;
				}
				else if (nRnd == 2)
				{
					eResult = BET_LIMIT;
				}
			}
			else
			{
				eResult = BETTING_CALL;
			}
		}
	}

	return eResult;
}

bool Player::DoBetting(int betIndex, Betting betting)
{
    bool bTurnOver = false;
    // 1. ���̸� ui�� ȣ���ϰ� ��ٸ���.
    // 2. ��ǻ�ʹ� ������̸� �����Ͱ� ��� ���ش�.
    // 3. �����̸� �Ѿ��� ��ٸ���.
    Betting* bettingRef = 0;
    if (betIndex == 1) 
        bettingRef = &m_kPokerPlayerInfo.eBet1;
    else if (betIndex == 2)
        bettingRef = &m_kPokerPlayerInfo.eBet2;
    else if (betIndex == 3)
        bettingRef = &m_kPokerPlayerInfo.eBet3;
    else if (betIndex == 4)
        bettingRef = &m_kPokerPlayerInfo.eBet4;


    switch (m_ePlayerState)
    {
    case PLAYERSTATE_NONE:
        break;
    case PLAYERSTATE_LIVE:
        {
            // ui���� �����Ҽ� �ֵ��� �Ѵ�.
            // �Ͽ����� ��ٸ���.
            // �ٸ�������̸� �ڿ������� ��ٸ���.
            //BiUiManager::GetInst()->

            if (betting == BETTING_NONE)
                *bettingRef = GetBetting(*bettingRef);
            else 
                *bettingRef = betting;

            //if (betIndex == 1) 
            //{
            //    if (betting == BETTING_NONE)
            //        m_kPokerPlayerInfo.eBet1 = GetBetting(m_kPokerPlayerInfo.eBet1);
            //    else 
            //        m_kPokerPlayerInfo.eBet1 = betting;

            //}
            //else if (betIndex == 2)
            //{
            //    if (betting == BETTING_NONE)
            //        m_kPokerPlayerInfo.eBet2 = GetBetting(m_kPokerPlayerInfo.eBet2);
            //    else 
            //        m_kPokerPlayerInfo.eBet2 = betting;
            //}
            //else if (betIndex == 3)
            //{
            //    if (betting == BETTING_NONE)
            //        m_kPokerPlayerInfo.eBet3 = GetBetting(m_kPokerPlayerInfo.eBet3);
            //    else 
            //        m_kPokerPlayerInfo.eBet3 = betting;
            //}
            //else if (betIndex == 4)
            //{
            //    if (betting == BETTING_NONE)
            //        m_kPokerPlayerInfo.eBet4 = GetBetting(m_kPokerPlayerInfo.eBet4);
            //    else 
            //        m_kPokerPlayerInfo.eBet4 = betting;
            //}

            bTurnOver = true;
            break;
        }
    case PLAYERSTATE_COMPUTER:
    case PLAYERSTATE_DISCONNECTER:
        {
            *bettingRef = GetBetting(*bettingRef);
            //if (betIndex == 1) 
            //    m_kPokerPlayerInfo.eBet1 = GetBetting(m_kPokerPlayerInfo.eBet1);
            //else if (betIndex == 2)
            //    m_kPokerPlayerInfo.eBet2 = GetBetting(m_kPokerPlayerInfo.eBet2);
            //else if (betIndex == 3)
            //    m_kPokerPlayerInfo.eBet3 = GetBetting(m_kPokerPlayerInfo.eBet3);
            //else if (betIndex == 4)
            //    m_kPokerPlayerInfo.eBet4 = GetBetting(m_kPokerPlayerInfo.eBet4);
            bTurnOver = true;
            break;
        }
    default:
        break;
    }

    return bTurnOver;
}


unsigned int Player::GetTempBetMoney(int betIndex)
{
    unsigned int tempBetMoney = 0;
    if (betIndex == 1) {
        tempBetMoney = m_kPokerPlayerInfo.nTempBet1Money;
    } else if (betIndex == 2) {
        tempBetMoney = m_kPokerPlayerInfo.nTempBet2Money;
    } else if (betIndex == 3) {
        tempBetMoney = m_kPokerPlayerInfo.nTempBet3Money;
    } else if (betIndex == 4) {
        tempBetMoney = m_kPokerPlayerInfo.nTempBet4Money;
    }
    
    return tempBetMoney;
}

unsigned int Player::GetLastBetMoney(int betIndex)
{
    unsigned int lastBetMoney = 0;
    if (betIndex == 1) {
        lastBetMoney = m_kPokerPlayerInfo.nLastBet1Money;
    } else if (betIndex == 2) {
        lastBetMoney = m_kPokerPlayerInfo.nLastBet2Money;
    } else if (betIndex == 3) {
        lastBetMoney = m_kPokerPlayerInfo.nLastBet3Money;
    } else if (betIndex == 4) {
        lastBetMoney = m_kPokerPlayerInfo.nLastBet4Money;
    }
    
    return lastBetMoney;
}

bool Player::IsDie() const
{
	return m_kPokerPlayerInfo.bDie;
}

bool Player::IsSchoolMoneyDone() const
{
	return m_kPokerPlayerInfo.bSchoolMoney;
}

bool Player::IsChoiceDone() const
{
	return m_kPokerPlayerInfo.bChoice;
}

bool Player::IsBet1CheckOrCall() const
{
	return (m_kPokerPlayerInfo.eBet1 == BETTING_CHECK || m_kPokerPlayerInfo.eBet1 == BETTING_CALL);
}
bool Player::IsBet2CheckOrCall() const
{
	return (m_kPokerPlayerInfo.eBet2 == BETTING_CHECK || m_kPokerPlayerInfo.eBet2 == BETTING_CALL);
}
bool Player::IsBet3CheckOrCall() const
{
	return (m_kPokerPlayerInfo.eBet3 == BETTING_CHECK || m_kPokerPlayerInfo.eBet3 == BETTING_CALL);
}
bool Player::IsBet4CheckOrCall() const
{
	return (m_kPokerPlayerInfo.eBet4 == BETTING_CHECK || m_kPokerPlayerInfo.eBet4 == BETTING_CALL);
}

void Player::SetDeal3Card(const Deal3CardInfo& kCardInfo)
{
	m_kPokerPlayerInfo.akFirstCard[0].SetCard((Card::PokerCard)kCardInfo.aucCard[0]);
	m_kPokerPlayerInfo.akFirstCard[1].SetCard((Card::PokerCard)kCardInfo.aucCard[1]);
	m_kPokerPlayerInfo.akFirstCard[2].SetCard((Card::PokerCard)kCardInfo.aucCard[2]);
}

void Player::SetDealCard(const DealCardInfo& kCardInfo, int nIndex)
{
	m_kPokerPlayerInfo.akOpenCard[nIndex].SetCard((Card::PokerCard)kCardInfo.ucCard);
}

void Player::SetHiddenCard(const DealCardInfo& kCardInfo, int nIndex)
{
	m_kPokerPlayerInfo.akHiddenCard[nIndex].SetCard((Card::PokerCard)kCardInfo.ucCard);
}

void Player::SetLastCard(const DealCardInfo& kCardInfo)
{
	m_kPokerPlayerInfo.kLastCard.SetCard((Card::PokerCard)kCardInfo.ucCard);
}

const JokboResult& Player::GetJokboResult() const
{
	return m_kJokboResult;
}

void Player::CalcJokboResult()
{
    m_kJokboResult.eJokbo = JOKBO_NONE;

    if (m_kPokerPlayerInfo.bDie)
        return;

    CardBit kCardBit;
    memset(kCardBit.abCardBit, 0, sizeof(kCardBit.abCardBit));

    unsigned int x, y;

    for (unsigned int ui = 0; ui < MAX_OPENCARD_COUNT; ui++)
    {
        if (m_kPokerPlayerInfo.akOpenCard[ui].GetCard() > Card::CARD_NONE)
        {
            y = (unsigned int)m_kPokerPlayerInfo.akOpenCard[ui].GetPicture();
            x = m_kPokerPlayerInfo.akOpenCard[ui].GetNumber();
            kCardBit.abCardBit[y][x] = true;
            if (x == 0) // ��Ʈ����Ʈ�� ���� �˱� ���� ���
                kCardBit.abCardBit[y][13] = true;
        }
    }

    PokerAI::CalcJokbo(kCardBit, m_kJokboResult);
}

void Player::CalcJokboResultLast()
{
    m_kJokboResult.eJokbo = JOKBO_NONE;

    if (m_kPokerPlayerInfo.bDie)
        return;


    CardBit kCardBit;
    memset(kCardBit.abCardBit, 0, sizeof(kCardBit.abCardBit));

    unsigned int x, y;

    for (unsigned int ui = 0; ui < MAX_OPENCARD_COUNT; ui++)
    {
        if (m_kPokerPlayerInfo.akOpenCard[ui].GetCard() > Card::CARD_NONE)
        {
            y = (unsigned int)m_kPokerPlayerInfo.akOpenCard[ui].GetPicture();
            x = m_kPokerPlayerInfo.akOpenCard[ui].GetNumber();
            kCardBit.abCardBit[y][x] = true;
            if (x == 0) // ��Ʈ����Ʈ�� ���� �˱� ���� ���
                kCardBit.abCardBit[y][13] = true;
        }
    }
    for (unsigned int ui = 0; ui < MAX_HIDDENCARD_COUNT; ui++)
    {
        if (m_kPokerPlayerInfo.akHiddenCard[ui].GetCard() > Card::CARD_NONE)
        {
            y = (unsigned int)m_kPokerPlayerInfo.akHiddenCard[ui].GetPicture();
            x = m_kPokerPlayerInfo.akHiddenCard[ui].GetNumber();
            kCardBit.abCardBit[y][x] = true;
            if (x == 0) // ��Ʈ����Ʈ�� ���� �˱� ���� ���
                kCardBit.abCardBit[y][13] = true;
        }
    }
    if (m_kPokerPlayerInfo.kLastCard.GetCard() > Card::CARD_NONE)
    {
        y = (unsigned int)m_kPokerPlayerInfo.kLastCard.GetPicture();
        x = m_kPokerPlayerInfo.kLastCard.GetNumber();
        kCardBit.abCardBit[y][x] = true;
        if (x == 0) // ��Ʈ����Ʈ�� ���� �˱� ���� ���
            kCardBit.abCardBit[y][13] = true;
    }


    PokerAI::CalcJokbo(kCardBit, m_kJokboResult);
}

void Player::SetComputer()
{
    assert(m_ePlayerState == PLAYERSTATE_NONE);

    m_ePlayerState = PLAYERSTATE_COMPUTER;
    m_kPokerPlayerInfo.nPlayerKey = INVALID_PLAYER_INDEX;
    m_kPokerPlayerInfo.nTotalMoney = 100000000;

}

void Player::Remove()
{
    m_ePlayerState = PLAYERSTATE_NONE;
    m_kPokerPlayerInfo.Init();
}

void Player::GetStringInfo(char szInformation[]) const
{
	szInformation[0] = 0;

	//sprintf_s(szInformation, 256, "%d", m_kPokerPlayerInfo.uiTotalMoney);
	//strcat_s(szInformation, 256, "\n");

	//char szCard[128];
	//strcat_s(szInformation, 256, GetJokboStringInfo(m_kJokboResult.eJokbo, szCard));
	//strcat_s(szInformation, 256, " : ");
	//strcat_s(szInformation, 256, GetCardStringInfo(m_kJokboResult.kTopCard, szCard));


	//strcat_s(szInformation, 256, "\n");

	//for (unsigned int ui = 0; ui < MAX_OPENCARD_COUNT; ui++)
	//{
	//	strcat_s(szInformation, 256, GetCardStringInfo(m_kPokerPlayerInfo.akOpenCard[ui], szCard));
	//}
	//strcat_s(szInformation, 256, "\n");

	//for (unsigned int ui = 0; ui < MAX_HIDDENCARD_COUNT; ui++)
	//{
	//	strcat_s(szInformation, 256, GetCardStringInfo(m_kPokerPlayerInfo.akHiddenCard[ui], szCard));
	//}
	//strcat_s(szInformation, 256, "\n");

	//switch (m_kPokerPlayerInfo.eBet1)
	//{
	//case BETTING_NONE:	strcat_s(szInformation, 256, "B1_NO");	break;
	//case BETTING_CHECK:	strcat_s(szInformation, 256, "B1_CH");	break;
	//case BETTING_BBING:	strcat_s(szInformation, 256, "B1_BB");	break;
	//case BETTING_CALL:	strcat_s(szInformation, 256, "B1_CA");	break;
	//case BETTING_QUARTER:	strcat_s(szInformation, 256, "B1_QU");	break;
	//case BETTING_HALF:	strcat_s(szInformation, 256, "B1_HA");	break;
	//case BETTING_FULL:	strcat_s(szInformation, 256, "B1_FU");	break;
	//case BETTING_DOUBLE:	strcat_s(szInformation, 256, "B1_DO");	break;
	//case BETTING_ALLIN:	strcat_s(szInformation, 256, "B1_AL");	break;
	//case BETTING_DIE:	strcat_s(szInformation, 256, "B1_DI");	break;
	//}
	//sprintf_s(szCard, 128, "  %d", m_kPokerPlayerInfo.uiBet1Money);
	//strcat_s(szInformation, 256, szCard);
	//strcat_s(szInformation, 256, "\n");

	//switch (m_kPokerPlayerInfo.eBet2)
	//{
	//case BETTING_NONE:	strcat_s(szInformation, 256, "B2_NO");	break;
	//case BETTING_CHECK:	strcat_s(szInformation, 256, "B2_CH");	break;
	//case BETTING_BBING:	strcat_s(szInformation, 256, "B2_BB");	break;
	//case BETTING_CALL:	strcat_s(szInformation, 256, "B2_CA");	break;
	//case BETTING_QUARTER:	strcat_s(szInformation, 256, "B2_QU");	break;
	//case BETTING_HALF:	strcat_s(szInformation, 256, "B2_HA");	break;
	//case BETTING_FULL:	strcat_s(szInformation, 256, "B2_FU");	break;
	//case BETTING_DOUBLE:	strcat_s(szInformation, 256, "B2_DO");	break;
	//case BETTING_ALLIN:	strcat_s(szInformation, 256, "B2_AL");	break;
	//case BETTING_DIE:	strcat_s(szInformation, 256, "B2_DI");	break;
	//}
	//sprintf_s(szCard, 128, "  %d", m_kPokerPlayerInfo.uiBet2Money);
	//strcat_s(szInformation, 256, szCard);
	//strcat_s(szInformation, 256, "\n");

	//switch (m_kPokerPlayerInfo.eBet3)
	//{
	//case BETTING_NONE:	strcat_s(szInformation, 256, "B3_NO");	break;
	//case BETTING_CHECK:	strcat_s(szInformation, 256, "B3_CH");	break;
	//case BETTING_BBING:	strcat_s(szInformation, 256, "B3_BB");	break;
	//case BETTING_CALL:	strcat_s(szInformation, 256, "B3_CA");	break;
	//case BETTING_QUARTER:	strcat_s(szInformation, 256, "B3_QU");	break;
	//case BETTING_HALF:	strcat_s(szInformation, 256, "B3_HA");	break;
	//case BETTING_FULL:	strcat_s(szInformation, 256, "B3_FU");	break;
	//case BETTING_DOUBLE:	strcat_s(szInformation, 256, "B3_DO");	break;
	//case BETTING_ALLIN:	strcat_s(szInformation, 256, "B3_AL");	break;
	//case BETTING_DIE:	strcat_s(szInformation, 256, "B3_DI");	break;
	//}
	//sprintf_s(szCard, 128, "  %d", m_kPokerPlayerInfo.uiBet3Money);
	//strcat_s(szInformation, 256, szCard);
	//strcat_s(szInformation, 256, "\n");

	//switch (m_kPokerPlayerInfo.eBet4)
	//{
	//case BETTING_NONE:	strcat_s(szInformation, 256, "B4_NO");	break;
	//case BETTING_CHECK:	strcat_s(szInformation, 256, "B4_CH");	break;
	//case BETTING_BBING:	strcat_s(szInformation, 256, "B4_BB");	break;
	//case BETTING_CALL:	strcat_s(szInformation, 256, "B4_CA");	break;
	//case BETTING_QUARTER:	strcat_s(szInformation, 256, "B4_QU");	break;
	//case BETTING_HALF:	strcat_s(szInformation, 256, "B4_HA");	break;
	//case BETTING_FULL:	strcat_s(szInformation, 256, "B4_FU");	break;
	//case BETTING_DOUBLE:	strcat_s(szInformation, 256, "B4_DO");	break;
	//case BETTING_ALLIN:	strcat_s(szInformation, 256, "B4_AL");	break;
	//case BETTING_DIE:	strcat_s(szInformation, 256, "B4_DI");	break;
	//}
	//sprintf_s(szCard, 128, "  %d", m_kPokerPlayerInfo.uiBet4Money);
	//strcat_s(szInformation, 256, szCard);
	//strcat_s(szInformation, 256, "\n");

}


//char* Player::GetCardStringInfo(const Card& kCard, char szCard[]) const
//{
//	if (kCard.GetCard() == 0)
//		strcpy_s(szCard, 128, "    ");
//	else
//	{
//		char szC[64];
//		switch (kCard.GetNumber())
//		{
//		case 0: strcpy_s(szC, 64, "A  "); break;
//		case 1: 
//		case 2: 
//		case 3: 
//		case 4: 
//		case 5: 
//		case 6: 
//		case 7: 
//		case 8: 
//			sprintf_s(szC, 64, "%d  ", kCard.GetNumber() + 1); break;
//		case 9: 
//			sprintf_s(szC, 64, "%d ", kCard.GetNumber() + 1); break;
//		case 10: strcpy_s(szC, 64, "J  "); break;
//		case 11: strcpy_s(szC, 64, "Q  "); break;
//		case 12: strcpy_s(szC, 64, "K  "); break;
//		}
//		sprintf_s(szCard, 128, "%d%s", kCard.GetPicture(), szC);
//	}
//
//	return szCard;
//}

void Player::AddMoney(unsigned int money)
{
	m_kPokerPlayerInfo.nTotalMoney += money;
}

void Player::GetPlayerInfo(PokerPlayerInfo& playerInfo)
{
	playerInfo = m_kPokerPlayerInfo;
}

void Player::GetPlayerJokbo(JokboResult& jokboInfo)
{
	jokboInfo = m_kJokboResult;
}
