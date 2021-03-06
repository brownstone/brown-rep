#include "cocos2d.h"
#include "Dealer.h"
#include "PokerRule.h"
#include "PlayerMan.h"
#include "Player.h"

Dealer::Dealer()
{
}

Dealer::~Dealer()
{
}

bool Dealer::Init(PokerRule* rule, PlayerMan* playerMan)
{
    m_pkPokerRule = rule;
    m_pkPlayerMan = playerMan;
    
    m_kDealerInfo.Init();
    
	m_kTableInfo.Init();
	m_kTableInfo.seedMoney = 10;
    return true;
}

void Dealer::Clear()
{
    m_pkPokerRule = 0;
    m_pkPlayerMan = 0;
}

void Dealer::Update(float delta)
{
    PokerSequence sequence = m_pkPokerRule->GetCurPokerSequence();
    bool start = m_pkPokerRule->IsSequenceStart();
    switch (sequence) 
    {
    case POKERSEQUENCE_START:
        m_kDealerInfo.nGameCount++;
        ResetTitleMoney();
        break;
    case POKERSEQUENCE_SHUFFLE:
        if (start) {
            Shuffle();
        }
		CalcSchoolMoney();
        break;
    case POKERSEQUENCE_DEALFIRSTCARD:
        if (start) {// 처음에 석장씩 나눠어준다.
            DealFirstCard();
        }
        break;
	case POKERSEQUENCE_DEAL1:
        if (start) {
            DoDeal(1);
        }
        break;
    case POKERSEQUENCE_BET1:
        if (start) {
            ResetRaiseCount();
        }
        CalcMoney(1);
        break;
	case POKERSEQUENCE_DEAL2:
        if (start) {
            DoDeal(2);
        }
        break;
    case POKERSEQUENCE_BET2:
        if (start) {
            ResetRaiseCount();
        }
        CalcMoney(2);
        break;
	case POKERSEQUENCE_DEAL3:
        if (start) {
            DoDeal(3);
        }
        break;
    case POKERSEQUENCE_BET3:
        if (start) {
            ResetRaiseCount();
        }
        CalcMoney(3);
        break;
	case POKERSEQUENCE_DEAL4:
        if (start) {
            DoDeal(4);
        }
        break;
    case POKERSEQUENCE_BET4:
        if (start) {
            ResetRaiseCount();
        }
        CalcMoney(4);
        break;
    case POKERSEQUENCE_SETTLE:
        if (start) {
            Settle(); // 승자에게 돈을 준다.
        }
        break;
    default: 
        break;
    }
}

void Dealer::PostUpdate(float delta)
{
    PokerSequence sequence = m_pkPokerRule->GetCurPokerSequence();
    int betIndex = 0;
    switch (sequence) 
    {
    case POKERSEQUENCE_BET1: betIndex = 1; break;
    case POKERSEQUENCE_BET2: betIndex = 2; break;
    case POKERSEQUENCE_BET3: betIndex = 3; break;
    case POKERSEQUENCE_BET4: betIndex = 4; break;
    default: break;
    }

    if (betIndex > 0)
    {
        CalcMoney(betIndex);
        bool notAlone = !m_pkPlayerMan->IsLeaveAlone();
        bool notAllBetting = !m_pkPlayerMan->IsBetDone(betIndex);
        if (notAlone && notAllBetting)
            m_pkPlayerMan->BetTurnOver(betIndex);
    }


    {
        // for debug
        int playersMoney = m_pkPlayerMan->GetPlayersMoney();
        int totalMoney = playersMoney + m_kTableInfo.titleMoney;

        if (totalMoney != 500000)
        {
            int aa = 0;
            aa++;
        }

    }
}


void Dealer::CalcSchoolMoney()
{
	for (unsigned int i = 0; i < MAX_POKERPLAYER_COUNT; i++)
	{
		Player& player = m_pkPlayerMan->GetPlayerByIndex(i);

		if (player.IsDie())
			continue;

		if (player.IsSchoolMoneyDone())
			continue;

		unsigned int tempSchoolMoney = player.GetTempSchoolMoney();
		if (tempSchoolMoney > 0) {
			// transaction...
			player.ExactCalcSchoolMoney();
			AddMoney(tempSchoolMoney);
		}
	}
}

void Dealer::Settle()
{
    int winner = m_pkPlayerMan->GetHighJokboPlayer();
    if (winner == -1) {
        // 모두 die 상태?
        return;
    }
    m_kDealerInfo.nLastWinnerIndex = winner;
    
    Player& player = m_pkPlayerMan->GetPlayerByIndex(winner);

    if (player.IsDie()) {
        // ???
        return;
    }
    
    m_kDealerInfo.nLastWinnerPrice = m_kTableInfo.titleMoney;
    if (m_kDealerInfo.nLastWinnerPrice > m_kDealerInfo.nMostMoney)
        m_kDealerInfo.nMostMoney = m_kDealerInfo.nLastWinnerPrice;
    player.AddMoney(m_kTableInfo.titleMoney);
    ResetTitleMoney();
}

void Dealer::AddMoney(unsigned int money)
{
    m_kTableInfo.titleMoney += money;
}

unsigned int Dealer::GetSeedMoney()
{
    return m_kTableInfo.seedMoney;
}

int Dealer::GetLastWinnerIndex()
{
    return m_kDealerInfo.nLastWinnerIndex;
}

void Dealer::ResetRaiseCount()
{
    m_kTableInfo.raiseCount = 0;
    m_kTableInfo.callMoney = 0;
}

void Dealer::CalcMoney(int betIndex)
{
	for (unsigned int i = 0; i < MAX_POKERPLAYER_COUNT; i++)
	{
		Player& player = m_pkPlayerMan->GetPlayerByIndex(i);

		if (player.IsDie())
			continue;
            
        unsigned int tempBetMoney = player.GetTempBetMoney(betIndex);
        if (tempBetMoney > 0) {
            // transaction...
            player.ExactCalc(betIndex);
            AddMoney(tempBetMoney);
            
            unsigned int lastBetMoney = player.GetLastBetMoney(betIndex);
            SetCallMoney(lastBetMoney);
        }
	}
}

void Dealer::SetCallMoney(unsigned int money)
{
    m_kTableInfo.callMoney = money;

}
void Dealer::ResetTitleMoney()
{
	m_kTableInfo.Clear();
}

void Dealer::Shuffle()
{
	m_nCardDeckIndex = Card::MAX_CARD_COUNT - 1;

    for (unsigned int i = 0; i < Card::MAX_CARD_COUNT; i++)
    {
        m_kCardDeck[i] = (Card::PokerCard)(i + 1);
    }

    unsigned int srcIndex;
    unsigned int desIndex;
    Card::PokerCard eTemp;
    for (unsigned int i = 0; i < 200; i++)
    {
        srcIndex = rand() % Card::MAX_CARD_COUNT;
        desIndex = rand() % Card::MAX_CARD_COUNT;

        eTemp = m_kCardDeck[srcIndex];
        m_kCardDeck[srcIndex] = m_kCardDeck[desIndex];
        m_kCardDeck[desIndex] = eTemp;
    }
}

Card::PokerCard Dealer::GetCardFromDeck()
{
    Card::PokerCard eCard = m_kCardDeck[m_nCardDeckIndex];
    m_nCardDeckIndex--;

    return eCard;
}

void Dealer::DealFirstCard()
{
	Deal3CardInfo kCardInfo;

	unsigned int sunIndex = m_pkPlayerMan->GetSunIndex();

	for (unsigned int i = 0; i < MAX_POKERPLAYER_COUNT; i++)
	{
		unsigned int index = (i + sunIndex) % MAX_POKERPLAYER_COUNT;

		Player& player = m_pkPlayerMan->GetPlayerByIndex(index);

		if (player.IsDie())
			continue;
		
		kCardInfo.ucPlayerIndex = (unsigned char)index;
		kCardInfo.aucCard[0] = (unsigned char)GetCardFromDeck();
		kCardInfo.aucCard[1] = (unsigned char)GetCardFromDeck();
		kCardInfo.aucCard[2] = (unsigned char)GetCardFromDeck();

		player.SetDeal3Card(kCardInfo);
	}
}

void Dealer::DoDeal(int betIndex)
{
    //if (IsMaster())
    {
        DealCardInfo kCardInfo;
        unsigned int uiSunIndex = m_pkPlayerMan->GetSunIndex();

        for (unsigned int ui = uiSunIndex; ui < uiSunIndex + MAX_POKERPLAYER_COUNT; ui++)
        {
            unsigned int uiIndex = ui;
            if (uiIndex >= MAX_POKERPLAYER_COUNT)
                uiIndex -= MAX_POKERPLAYER_COUNT;

            Player& player = m_pkPlayerMan->GetPlayerByIndex(uiIndex);

            if (player.IsDie())
                continue;

            kCardInfo.ucPlayerIndex = (unsigned char)uiIndex;
            kCardInfo.ucCard = (unsigned char)GetCardFromDeck();

            if (betIndex == 4)
            {
                player.SetLastCard(kCardInfo);
            }
            else
            {
                player.SetDealCard(kCardInfo, betIndex);
            }
        }
    }
}

unsigned int Dealer::GetCallMoney()
{
    return m_kTableInfo.callMoney;
}

unsigned int Dealer::GetTitleMoney()
{
    return m_kTableInfo.titleMoney;
}

void Dealer::AddRaiseCount()
{
    m_kTableInfo.raiseCount++;
}

unsigned int Dealer::GetRaiseCount()
{
    return m_kTableInfo.raiseCount;
}

void Dealer::GetDealerInfo(DealerInfo& dealerInfo)
{
    dealerInfo = m_kDealerInfo;
}

void Dealer::GetTableInfo(TableInfo& tableInfo)
{
	tableInfo = m_kTableInfo;
}