#include "SevenPoker.h"

SevenPoker::SevenPoker()
{
}

SevenPoker::~SevenPoker()
{
}



void SevenPoker::CalcJokbo(CardBit& kCardBit, BiPlayer::JokboResult& kJokboResult) const
{
	Card kTopCard;
	kTopCard.Clear();

	// ��Ʈ����Ʈ�÷������� �˾ƺ���.
	{
		bool bStraightFlush = false;
		int nStraightCount = 0;
		for (unsigned int uy = 0; uy < MAX_Y; uy++)
		{
			nStraightCount = 0;

			for (unsigned int ux = 0; ux < MAX_X; ux++)
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
							// Ư���� �齺Ʈ����Ʈ�÷����̴�. ��, 1,2,3,4,5 �� ���̴�.
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

	// FourCard���� �˾ƺ���.
	{
		bool bFourBit = false;
		for (unsigned int ux = 0; ux < MAX_X; ux++)
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

	// FullHouse���� �˾ƺ���.
	{
		bool bTriple = false;
		bool bPair = false;

		unsigned int uiPairCount = 0;
		for (unsigned int ux = 0; ux < MAX_X; ux++)
		{
			uiPairCount = 0;
			for (unsigned int uy = 0; uy < MAX_Y; uy++)
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
			for (unsigned int ux = 0; ux < MAX_X; ux++)
			{
				if (bPair)
					break;

				if (ux == (unsigned int)kTopCard.GetNumber())
					continue;

				uiPairCount = 0;

				for (unsigned int uy = 0; uy < MAX_Y; uy++)
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

	// Flush���� �˾ƺ���.
	{
		bool bFlush = false;
		int nFlushCount = 0;
		for (unsigned int uy = 0; uy < MAX_Y; uy++)
		{
			nFlushCount = 0;

			for (unsigned int ux = 1; ux < MAX_X; ux++)
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
			for (unsigned int ux = MAX_X - 1; ux > 0; ux--)
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


	// ��Ʈ����Ʈ���� �˾ƺ���.
	{
		bool bStraight = false;
		bool bBackStraight = false;
		int  nStraightCount = 0;
		bool bBit = false;
		for (unsigned int ux = 0; ux < MAX_X; ux++)
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
						// Ư���� �齺Ʈ����Ʈ�̴�. ��, 1,2,3,4,5 �� ���̴�.

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

	// Triple ���� �˾ƺ���.
	{
		bool bTriple = false;

		unsigned int uiPairCount = 0;
		for (unsigned int ux = 0; ux < MAX_X; ux++)
		{
			uiPairCount = 0;
			for (unsigned int uy = 0; uy < MAX_Y; uy++)
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

	// TwoPair ���� �˾ƺ���.
	{
		bool bOnePair = false;
		bool bTwoPair = false;

		Card kSecondCard;
		unsigned int uiPairCount = 0;
		for (unsigned int ux = MAX_X - 1; ux > 0; ux--)
		{
			if (bTwoPair)
				break;

			uiPairCount = 0;
			for (unsigned int uy = 0; uy < MAX_Y; uy++)
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

	// NoPair�̴�. žī�常 �˾ƺ���.
	{
		bool bFind = false;
		for (int ux = MAX_X - 1; ux > 0; ux--)
		{
			if (bFind)
				break;
			for (int uy = MAX_Y - 1; uy >= 0; uy--)
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


void SevenPoker::GetJokboResultForFindSun(const BiPlayer::PokerPlayerInfo& kPokerPlayerInfo, BiPlayer::JokboResult& kJokboResult) const
{
	kJokboResult.eJokbo = JOKBO_NONE;

	if (kPokerPlayerInfo.bDie)
		return;


	CardBit kCardBit;
	memset(kCardBit.abCardBit, 0, sizeof(kCardBit.abCardBit));

	unsigned int x, y;

	for (unsigned int ui = 0; ui < 4; ui++)
	{
		if (kPokerPlayerInfo.akOpenCard[ui].GetCard() > Card::CARD_NONE)
		{
			y = (unsigned int)kPokerPlayerInfo.akOpenCard[ui].GetPicture();
			x = kPokerPlayerInfo.akOpenCard[ui].GetNumber();
			kCardBit.abCardBit[y][x] = true;
			if (x == 0) // ��Ʈ����Ʈ�� ���� �˱� ���� ���
				kCardBit.abCardBit[y][13] = true;
		}
	}

	CalcJokbo(kCardBit, kJokboResult);
}

void SevenPoker::GetJokboResultForSettle(const Player::PokerPlayerInfo& kPokerPlayerInfo, Player::JokboResult& kJokboResult) const
{
	kJokboResult.eJokbo = JOKBO_NONE;

	if (kPokerPlayerInfo.bDie)
		return;


	CardBit kCardBit;
	memset(kCardBit.abCardBit, 0, sizeof(kCardBit.abCardBit));

	unsigned int x, y;

	for (unsigned int ui = 0; ui < 4; ui++)
	{
		if (kPokerPlayerInfo.akOpenCard[ui].GetCard() > Card::CARD_NONE)
		{
			y = (unsigned int)kPokerPlayerInfo.akOpenCard[ui].GetPicture();
			x = kPokerPlayerInfo.akOpenCard[ui].GetNumber();
			kCardBit.abCardBit[y][x] = true;
			if (x == 0) // ��Ʈ����Ʈ�� ���� �˱� ���� ���
				kCardBit.abCardBit[y][13] = true;
		}
	}
	for (unsigned int ui = 0; ui < 3; ui++)
	{
		if (kPokerPlayerInfo.akHiddenCard[ui].GetCard() > Card::CARD_NONE)
		{
			y = (unsigned int)kPokerPlayerInfo.akHiddenCard[ui].GetPicture();
			x = kPokerPlayerInfo.akHiddenCard[ui].GetNumber();
			kCardBit.abCardBit[y][x] = true;
			if (x == 0) // ��Ʈ����Ʈ�� ���� �˱� ���� ���
				kCardBit.abCardBit[y][13] = true;
		}
	}

	CalcJokbo(kCardBit, kJokboResult);

}


bool SevenPoker::CompareJokbo(const BiPlayer::JokboResult& lhs, const BiPlayer::JokboResult& rhs) const
{
	/*
	1. ����� : žī���� ����, ���� ��
	2. ����� : žī���� ����, ���� �� (���� �ƿ��̾ �����̵����� �̱�)
	3. ����� : žī���� ����, ����ī���� ����, ������ žī���� ���� �� (���� ��ī������̸� �����̵� ���̽� ���� �ִ����� �̱�)
	4. Ʈ���� : žī���� ����
	5. ��Ʈ����Ʈ : ����
	6. �÷��� : ���� ���ڸ� ���ʷ� ��
	7. ��ī�� : ����
	8. ��Ƽ�� : ����

	������ �÷��ø� ���ܻ�Ȳ�̰� �������� ������ �꿡 ������.
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