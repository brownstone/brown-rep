#include "PokerAI.h"
#include "Dealer.h"
#include "PlayerMan.h"
#include "PokerRule.h"

PokerAI::PokerAI()
{
}

PokerAI::~PokerAI()
{
}

bool PokerAI::Init(PokerRule* rule, Dealer* dealer, PlayerMan* playerMan)
{
    m_pkPokerRule = rule;
    m_pkDealer = dealer;
    m_pkPlayerMan = playerMan;
    return true;
}

void PokerAI::Clear()
{
    m_pkPokerRule = 0;
    m_pkDealer = 0;
    m_pkPlayerMan = 0;
}

void PokerAI::Update(float delta)
{
    PokerSequence sequence = m_pkPokerRule->GetCurPokerSequence();
    bool start = m_pkPokerRule->IsSequenceStart();

	switch (sequence)
	{
        case POKERSEQUENCE_BET1:
		{
			if (start)
			{
                ThinkAI();
			}
			break;
		}
  //      case PokerSequence::POKERSEQUENCE_BET2:
		//{
		//	if (start)
		//	{
  //              ThinkAI();
		//	}
		//	break;
		//}
	// case BiPokerSequence::POKERSEQUENCE_SETTLE:
		// {
			// if (pkPokerSequence->IsStart())
			// {
				// CalcJokboResultLast();
				// // 모든 카드를 오픈하여 누가 이겼는지 알아내서
				// // 승자에게 돈을 준다.
				// DoSettle();
			// }

			// break;
		// }
	    default:
		    break;
	}
}

void PokerAI::ThinkAI()
{
    for (unsigned int ui = 0; ui < MAX_POKERPLAYER_COUNT; ui++)
    {
        unsigned int uiIndex = ui;

        Player& player = m_pkPlayerMan->GetPlayerByIndex(uiIndex);

        if (player.IsDie())
            continue;

        player.CalcJokboResult();
    }
}

void PokerAI::CalcJokbo(CardBit& kCardBit, JokboResult& kJokboResult)
{
	Card kTopCard;
	kTopCard.Clear();

	// 스트레이트플러시인지 알아본다.
	{
		bool bStraightFlush = false;
		int nStraightCount = 0;
		for (unsigned int uy = 0; uy < MAX_CARD_Y; uy++)
		{
			nStraightCount = 0;

			for (unsigned int ux = 0; ux < MAX_CARD_X; ux++)
			{
				if (kCardBit.abCardBit[uy][ux])
				{
					nStraightCount++;
					if (nStraightCount >= 5)
					{
						bStraightFlush = true;
						kTopCard.SetCard((Card::CardPicture)uy, (Card::CardNumber)ux);

						if (ux == 4)
						{
							// 특별히 백스트레이트플래쉬이다. 즉, 1,2,3,4,5 란 뜻이다.
							break;
						}
					}
				}
				else
					nStraightCount = 0;
			}
		}

		if (bStraightFlush)
		{
			if (kTopCard.GetNumber() == Card::CARDNUMBER_A)
			{
				kJokboResult.eJokbo = JOKBO_ROYALSTRAIGHTFLUSH;
				kJokboResult.kTopCard = kTopCard;
			}
			else if (kTopCard.GetNumber() == Card::CARDNUMBER_5)
			{
				kJokboResult.eJokbo = JOKBO_BACKSTRAIGHTFLUSH;
				kJokboResult.kTopCard = kTopCard;
			}
			else
			{
				kJokboResult.eJokbo = JOKBO_STRAIGHTFLUSH;
				kJokboResult.kTopCard = kTopCard;
			}
			return;
		}
	}

	// FourCard인지 알아본다.
	{
		bool bFourBit = false;
		for (unsigned int ux = 0; ux < MAX_CARD_X; ux++)
		{
			bFourBit = kCardBit.abCardBit[0][ux] && kCardBit.abCardBit[1][ux] && kCardBit.abCardBit[2][ux] && kCardBit.abCardBit[3][ux];
			if (bFourBit)
			{
				kTopCard.SetCard(Card::CARDPICTURE_SPADE, (Card::CardNumber)ux);

				kJokboResult.eJokbo = JOKBO_FOURCARD;
				kJokboResult.kTopCard = kTopCard;

				return;
			}
		}
	}

	// FullHouse인지 알아본다.
	{
		bool bTriple = false;
		bool bPair = false;

		unsigned int uiPairCount = 0;
		for (unsigned int ux = 0; ux < MAX_CARD_X; ux++)
		{
			uiPairCount = 0;
			for (unsigned int uy = 0; uy < MAX_CARD_Y; uy++)
			{
				if (kCardBit.abCardBit[uy][ux])
				{
					uiPairCount++;

					if (uiPairCount >= 3)
					{
						bTriple = true;
						kTopCard.SetCard((Card::CardPicture)uy, (Card::CardNumber)ux);
						break;
					}
				}
			}
		}

		if (bTriple)
		{
			for (unsigned int ux = 0; ux < MAX_CARD_X; ux++)
			{
				if (bPair)
					break;

				if (ux == (unsigned int)kTopCard.GetNumber())
					continue;

				uiPairCount = 0;

				for (unsigned int uy = 0; uy < MAX_CARD_Y; uy++)
				{
					if (kCardBit.abCardBit[uy][ux])
					{
						uiPairCount++;

						if (uiPairCount >= 2)
						{
							bPair = true;
							break;
						}
					}
				}
			}
		}

		if (bTriple && bPair)
		{
			kJokboResult.eJokbo = JOKBO_FULLHOUSE;
			kJokboResult.kTopCard = kTopCard;
			return;
		}
	}

	// Flush인지 알아본다.
	{
		bool bFlush = false;
		int nFlushCount = 0;
		for (unsigned int uy = 0; uy < MAX_CARD_Y; uy++)
		{
			nFlushCount = 0;

			for (unsigned int ux = 1; ux < MAX_CARD_X; ux++)
			{
				if (kCardBit.abCardBit[uy][ux])
				{
					nFlushCount++;
					if (nFlushCount >= 5)
					{
						bFlush = true;

						kTopCard.SetCard((Card::CardPicture)uy, (Card::CardNumber)ux);
					}
				}
			}
		}

		if (bFlush)
		{
			nFlushCount = 0;
			for (unsigned int ux = MAX_CARD_X - 1; ux > 0; ux--)
			{
				if (kCardBit.abCardBit[kJokboResult.kTopCard.GetPicture()][ux])
				{
					nFlushCount++;
					if (nFlushCount > 1)
					{
						kJokboResult.akFlush[nFlushCount - 2].SetCard(kJokboResult.kTopCard.GetPicture(), (Card::CardNumber)ux);
					}

					if (nFlushCount >= 5)
						break;
				}
			}
			kJokboResult.eJokbo = JOKBO_FLUSH;
			kJokboResult.kTopCard = kTopCard;
			return;
		}
	}


	// 스트레이트인지 알아본다.
	{
		bool bStraight = false;
		bool bBackStraight = false;
		int  nStraightCount = 0;
		bool bBit = false;
		for (unsigned int ux = 0; ux < MAX_CARD_X; ux++)
		{
			bBit = kCardBit.abCardBit[0][ux] || kCardBit.abCardBit[1][ux] || kCardBit.abCardBit[2][ux] || kCardBit.abCardBit[3][ux];
			if (bBit)
			{
				nStraightCount++;
				if (nStraightCount >= 5)
				{
					bStraight = true;

					int nPicture = 0;

					if (kCardBit.abCardBit[3][ux])
						nPicture = 3;
					else if (kCardBit.abCardBit[2][ux])
						nPicture = 2;
					else if (kCardBit.abCardBit[1][ux])
						nPicture = 1;
					else if (kCardBit.abCardBit[0][ux])
						nPicture = 0;

					kTopCard.SetCard((Card::CardPicture)nPicture, (Card::CardNumber)ux);

					if (ux == 4)
					{
						// 특별히 백스트레이트이다. 즉, 1,2,3,4,5 란 뜻이다.

						bBackStraight = true;

						if (kCardBit.abCardBit[3][0])
							nPicture = 3;
						else if (kCardBit.abCardBit[2][0])
							nPicture = 2;
						else if (kCardBit.abCardBit[1][0])
							nPicture = 1;
						else if (kCardBit.abCardBit[0][0])
							nPicture = 0;

						kTopCard.SetCard((Card::CardPicture)nPicture, Card::CARDNUMBER_A);

						break;
					}
				}
			}
			else
				nStraightCount = 0;
		}

		if (bStraight)
		{
			kJokboResult.kTopCard = kTopCard;

			if (kTopCard.GetNumber() == Card::CARDNUMBER_A)
			{
				if (bBackStraight)
				{
					kJokboResult.eJokbo = JOKBO_BACKSTRAIGHT;
				}
				else
				{
					kJokboResult.eJokbo = JOKBO_ROYALSTRAIGHT;
				}
			}
			else
			{
				kJokboResult.eJokbo = JOKBO_STRAIGHT;
			}
			return;
		}
	}

	// Triple 인지 알아본다.
	{
		bool bTriple = false;

		unsigned int uiPairCount = 0;
		for (unsigned int ux = 0; ux < MAX_CARD_X; ux++)
		{
			uiPairCount = 0;
			for (unsigned int uy = 0; uy < MAX_CARD_Y; uy++)
			{
				if (kCardBit.abCardBit[uy][ux])
				{
					uiPairCount++;

					if (uiPairCount >= 3)
					{
						bTriple = true;
						kTopCard.SetCard((Card::CardPicture)uy, (Card::CardNumber)ux);
						break;
					}
				}
			}
		}
		if (bTriple)
		{
			kJokboResult.eJokbo = JOKBO_TRIFLE;
			kJokboResult.kTopCard = kTopCard;
			return;
		}
	}

	// TwoPair 인지 알아본다.
	{
		bool bOnePair = false;
		bool bTwoPair = false;

		Card kSecondCard;
		unsigned int uiPairCount = 0;
		for (unsigned int ux = MAX_CARD_X - 1; ux > 0; ux--)
		{
			if (bTwoPair)
				break;

			uiPairCount = 0;
			for (unsigned int uy = 0; uy < MAX_CARD_Y; uy++)
			{
				if (kCardBit.abCardBit[uy][ux])
				{
					uiPairCount++;

					if (uiPairCount >= 2)
					{
						if (bOnePair)
						{
							bTwoPair = true;
							kSecondCard.SetCard((Card::CardPicture)uy, (Card::CardNumber)ux);
							break;
						}
						else
						{
							bOnePair = true;
							kTopCard.SetCard((Card::CardPicture)uy, (Card::CardNumber)ux);
							break;
						}
					}
				}
			}
		}

		if (bTwoPair)
		{
			kJokboResult.eJokbo = JOKBO_TWOPAIR;
			kJokboResult.kTopCard = kTopCard;
			kJokboResult.kSecondCard = kSecondCard;
			return;
		}

		if (bOnePair)
		{
			kJokboResult.eJokbo = JOKBO_ONEPAIR;
			kJokboResult.kTopCard = kTopCard;
			return;
		}
	}

	// NoPair이다. 탑카드만 알아본다.
	{
		bool bFind = false;
		for (int ux = MAX_CARD_X - 1; ux > 0; ux--)
		{
			if (bFind)
				break;
			for (int uy = MAX_CARD_Y - 1; uy >= 0; uy--)
			{
				if (kCardBit.abCardBit[uy][ux])
				{
					bFind = true;
					kTopCard.SetCard((Card::CardPicture)uy, (Card::CardNumber)ux);
					break;
				}
			}
		}
		kJokboResult.eJokbo = JOKBO_NOPAIR;
		kJokboResult.kTopCard = kTopCard;
		return;
	}
}


//void PokerAI::GetJokboResultForFindSun(const Player::PokerPlayerInfo& kPokerPlayerInfo, JokboResult& kJokboResult) const
//{
//	kJokboResult.eJokbo = JOKBO_NONE;
//
//	if (kPokerPlayerInfo.bDie)
//		return;
//
//
//	CardBit kCardBit;
//	memset(kCardBit.abCardBit, 0, sizeof(kCardBit.abCardBit));
//
//	unsigned int x, y;
//
//	for (unsigned int ui = 0; ui < 4; ui++)
//	{
//		if (kPokerPlayerInfo.akOpenCard[ui].GetCard() > Card::CARD_NONE)
//		{
//			y = (unsigned int)kPokerPlayerInfo.akOpenCard[ui].GetPicture();
//			x = kPokerPlayerInfo.akOpenCard[ui].GetNumber();
//			kCardBit.abCardBit[y][x] = true;
//			if (x == 0) // 스트레이트를 쉽게 알기 위한 편법
//				kCardBit.abCardBit[y][13] = true;
//		}
//	}
//
//	CalcJokbo(kCardBit, kJokboResult);
//}
//
//void PokerAI::GetJokboResultForSettle(const Player::PokerPlayerInfo& kPokerPlayerInfo, JokboResult& kJokboResult) const
//{
//	kJokboResult.eJokbo = JOKBO_NONE;
//
//	if (kPokerPlayerInfo.bDie)
//		return;
//
//
//	CardBit kCardBit;
//	memset(kCardBit.abCardBit, 0, sizeof(kCardBit.abCardBit));
//
//	unsigned int x, y;
//
//	for (unsigned int ui = 0; ui < 4; ui++)
//	{
//		if (kPokerPlayerInfo.akOpenCard[ui].GetCard() > Card::CARD_NONE)
//		{
//			y = (unsigned int)kPokerPlayerInfo.akOpenCard[ui].GetPicture();
//			x = kPokerPlayerInfo.akOpenCard[ui].GetNumber();
//			kCardBit.abCardBit[y][x] = true;
//			if (x == 0) // 스트레이트를 쉽게 알기 위한 편법
//				kCardBit.abCardBit[y][13] = true;
//		}
//	}
//	for (unsigned int ui = 0; ui < 3; ui++)
//	{
//		if (kPokerPlayerInfo.akHiddenCard[ui].GetCard() > Card::CARD_NONE)
//		{
//			y = (unsigned int)kPokerPlayerInfo.akHiddenCard[ui].GetPicture();
//			x = kPokerPlayerInfo.akHiddenCard[ui].GetNumber();
//			kCardBit.abCardBit[y][x] = true;
//			if (x == 0) // 스트레이트를 쉽게 알기 위한 편법
//				kCardBit.abCardBit[y][13] = true;
//		}
//	}
//
//	CalcJokbo(kCardBit, kJokboResult);
//}



bool PokerAI::CompareJokbo(const JokboResult& lhs, const JokboResult& rhs)
{
	/*
	1. 노페어 : 탑카드의 숫자, 무늬 비교
	2. 원페어 : 탑카드의 숫자, 무늬 비교 (같은 아원이어도 스페이드쪽이 이김)
	3. 투페어 : 탑카드의 숫자, 세컨카드의 숫자, 같으면 탑카드의 무늬 비교 (같은 아카투페어이면 스페이드 에이스 갖고 있는쪽이 이김)
	4. 트리플 : 탑카드의 숫자
	5. 스트레이트 : 동일
	6. 플러시 : 높은 숫자를 차례로 비교
	7. 포카드 : 동일
	8. 스티플 : 동일

	투페어와 플러시만 예외상황이고 나머지는 동일한 룰에 따른다.
	*/

	bool bResult = false;
	if (lhs.eJokbo < rhs.eJokbo)
	{
		bResult = true;
	}
	else if (lhs.eJokbo == rhs.eJokbo)
	{
		if (lhs.eJokbo == JOKBO_TWOPAIR)
		{
			if (lhs.kTopCard.GetValue() < rhs.kTopCard.GetValue())
			{
				bResult = true;
			}
			else if (lhs.kTopCard.GetValue() == rhs.kTopCard.GetValue())
			{
				if (lhs.kSecondCard.GetValue() < rhs.kSecondCard.GetValue())
				{
					bResult = true;
				}
				else if (lhs.kSecondCard.GetValue() == rhs.kSecondCard.GetValue())
				{
					if (lhs.kTopCard.GetPicture() < rhs.kTopCard.GetPicture())
					{
						bResult = true;
					}
				}
			}
		}
		else if (lhs.eJokbo == JOKBO_FLUSH)
		{
			if (lhs.kTopCard.GetValue() < rhs.kTopCard.GetValue())
			{
				bResult = true;
			}
			else if (lhs.kTopCard.GetValue() == rhs.kTopCard.GetValue())
			{
				if (lhs.akFlush[0].GetValue() < rhs.akFlush[0].GetValue())
				{
					bResult = true;
				}
				else if (lhs.akFlush[0].GetValue() == rhs.akFlush[0].GetValue())
				{
					if (lhs.akFlush[1].GetValue() < rhs.akFlush[1].GetValue())
					{
						bResult = true;
					}
					else if (lhs.akFlush[1].GetValue() == rhs.akFlush[1].GetValue())
					{
						if (lhs.akFlush[2].GetValue() < rhs.akFlush[2].GetValue())
						{
							bResult = true;
						}
						else if (lhs.akFlush[2].GetValue() == rhs.akFlush[2].GetValue())
						{
							if (lhs.akFlush[3].GetValue() < rhs.akFlush[3].GetValue())
							{
								bResult = true;
							}
							else if (lhs.akFlush[3].GetValue() == rhs.akFlush[3].GetValue())
							{
								if (lhs.kTopCard.GetPicture() < rhs.kTopCard.GetPicture())
								{
									bResult = true;
								}
							}
						}
					}
				}
			}
		}
		else
		{
			if (lhs.kTopCard.GetValue() < rhs.kTopCard.GetValue())
			{
				bResult = true;
			}
			else if (lhs.kTopCard.GetValue() == rhs.kTopCard.GetValue())
			{
				if (lhs.kTopCard.GetPicture() < rhs.kTopCard.GetPicture())
				{
					bResult = true;
				}
			}
		}
	}

	return bResult;
}