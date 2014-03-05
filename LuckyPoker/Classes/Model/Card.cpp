#include "Card.h"

Card::Card()
{
	Clear();
}

Card::~Card()
{
}


void Card::Clear()
{
	m_eCard = CARD_NONE;
	m_ePicture = CARDPICTURE_MAX;
	m_eNumber = CARDNUMBER_MAX;
	m_nValue = 0;
}

void Card::SetCard(PokerCard eCard)
{
	//assert(eCard > CARD_NONE && eCard < CARD_MAX_COUNT);

	unsigned int uiPicture;
	unsigned int uiNumber;

	uiPicture = (unsigned int)((eCard - 1) / MAX_CARDNUMBER_COUNT);
	uiNumber = (eCard - 1) % MAX_CARDNUMBER_COUNT;

	SetData(eCard, (CardPicture)uiPicture, (CardNumber)uiNumber);
}

void Card::SetCard(CardPicture ePicture, CardNumber eNumber)
{
	if (eNumber == CARDNUMBER_MAX)
		eNumber = CARDNUMBER_A;

	unsigned int uiCard = ePicture * MAX_CARDNUMBER_COUNT + eNumber + 1;

	SetData((PokerCard)uiCard, ePicture, eNumber);
}

Card::PokerCard Card::GetCard() const
{
	return m_eCard;
}
Card::CardPicture Card::GetPicture() const
{
	return m_ePicture;
}
Card::CardNumber Card::GetNumber() const
{
	return m_eNumber;
}
unsigned int Card::GetValue() const
{
	return m_nValue;
}

void Card::SetData(PokerCard eCard, CardPicture ePicture, CardNumber eNumber)
{
	m_eCard = eCard;
	m_ePicture = ePicture;
	m_eNumber = eNumber;

	m_nValue = eNumber;
	if (m_nValue == 0)
		m_nValue = MAX_CARDNUMBER_COUNT;
}

bool Card::SameCard(const Card& rhs)
{
	return (m_eCard == rhs.m_eCard);
}

const char* Card::GetString() const
{
	// ♧ ◆  ♡  ♤   ♤ ♠ ♡ ♥ ♧ ♣ ⊙ ◈ ▣ ◐ ◑ ◇ ◆
	//return " ♧ ◆  ♡  ♤";	 // ♠ ♥ ♦ ♣
	//switch (m_eCard)
	//{
	//case CARD_C1: return "♣A ";
	//case CARD_C2: return "♣2 ";
	//case CARD_C3: return "♣3 ";
	//case CARD_C4: return "♣4 ";
	//case CARD_C5: return "♣5 ";
	//case CARD_C6: return "♣6 ";
	//case CARD_C7: return "♣7 ";
	//case CARD_C8: return "♣8 ";
	//case CARD_C9: return "♣9 ";
	//case CARD_C10: return "♣10 ";
	//case CARD_C11: return "♣J ";
	//case CARD_C12: return "♣Q ";
	//case CARD_C13: return "♣K ";
	//case CARD_D1: return "♦A ";
	//case CARD_D2: return "♦2 ";
	//case CARD_D3: return "♦3 ";
	//case CARD_D4: return "♦4 ";
	//case CARD_D5: return "♦5 ";
	//case CARD_D6: return "♦6 ";
	//case CARD_D7: return "♦7 ";
	//case CARD_D8: return "♦8 ";
	//case CARD_D9: return "♦9 ";
	//case CARD_D10: return "♦10 ";
	//case CARD_D11: return "♦J ";
	//case CARD_D12: return "♦Q ";
	//case CARD_D13: return "♦K ";
	//case CARD_H1: return "♥A ";
	//case CARD_H2: return "♥2 ";
	//case CARD_H3: return "♥3 ";
	//case CARD_H4: return "♥4 ";
	//case CARD_H5: return "♥5 ";
	//case CARD_H6: return "♥6 ";
	//case CARD_H7: return "♥7 ";
	//case CARD_H8: return "♥8 ";
	//case CARD_H9: return "♥9 ";
	//case CARD_H10: return "♥10 ";
	//case CARD_H11: return "♥J ";
	//case CARD_H12: return "♥Q ";
	//case CARD_H13: return "♥K ";
	//case CARD_S1: return "♠A ";
	//case CARD_S2: return "♠2 ";
	//case CARD_S3: return "♠3 ";
	//case CARD_S4: return "♠4 ";
	//case CARD_S5: return "♠5 ";
	//case CARD_S6: return "♠6 ";
	//case CARD_S7: return "♠7 ";
	//case CARD_S8: return "♠8 ";
	//case CARD_S9: return "♠9 ";
	//case CARD_S10: return "♠10 ";
	//case CARD_S11: return "♠J ";
	//case CARD_S12: return "♠Q ";
	//case CARD_S13: return "♠K ";
	//default: return " "; break;
	//}

	switch (m_eCard)
	{
	case CARD_C1: return "CA ";
	case CARD_C2: return "C2 ";
	case CARD_C3: return "C3 ";
	case CARD_C4: return "C4 ";
	case CARD_C5: return "C5 ";
	case CARD_C6: return "C6 ";
	case CARD_C7: return "C7 ";
	case CARD_C8: return "C8 ";
	case CARD_C9: return "C9 ";
	case CARD_C10: return "C10 ";
	case CARD_C11: return "CJ ";
	case CARD_C12: return "CQ ";
	case CARD_C13: return "CK ";
	case CARD_D1: return "DA ";
	case CARD_D2: return "D2 ";
	case CARD_D3: return "D3 ";
	case CARD_D4: return "D4 ";
	case CARD_D5: return "D5 ";
	case CARD_D6: return "D6 ";
	case CARD_D7: return "D7 ";
	case CARD_D8: return "D8 ";
	case CARD_D9: return "D9 ";
	case CARD_D10: return "D10 ";
	case CARD_D11: return "DJ ";
	case CARD_D12: return "DQ ";
	case CARD_D13: return "DK ";
	case CARD_H1: return "HA ";
	case CARD_H2: return "H2 ";
	case CARD_H3: return "H3 ";
	case CARD_H4: return "H4 ";
	case CARD_H5: return "H5 ";
	case CARD_H6: return "H6 ";
	case CARD_H7: return "H7 ";
	case CARD_H8: return "H8 ";
	case CARD_H9: return "H9 ";
	case CARD_H10: return "H10 ";
	case CARD_H11: return "HJ ";
	case CARD_H12: return "HQ ";
	case CARD_H13: return "HK ";
	case CARD_S1: return "SA ";
	case CARD_S2: return "S2 ";
	case CARD_S3: return "S3 ";
	case CARD_S4: return "S4 ";
	case CARD_S5: return "S5 ";
	case CARD_S6: return "S6 ";
	case CARD_S7: return "S7 ";
	case CARD_S8: return "S8 ";
	case CARD_S9: return "S9 ";
	case CARD_S10: return "S10 ";
	case CARD_S11: return "SJ ";
	case CARD_S12: return "SQ ";
	case CARD_S13: return "SK ";
	default: return " "; break;
	}
}

const char* Card::GetNumberToString() const
{
	switch(GetNumber())
	{
	case CARDNUMBER_A: return "A";
	case CARDNUMBER_2: return "2";
	case CARDNUMBER_3: return "3";
	case CARDNUMBER_4: return "4";
	case CARDNUMBER_5: return "5";
	case CARDNUMBER_6: return "6";
	case CARDNUMBER_7: return "7";
	case CARDNUMBER_8: return "8";
	case CARDNUMBER_9: return "9";
	case CARDNUMBER_10: return "10";
	case CARDNUMBER_J: return "J";
	case CARDNUMBER_Q: return "Q";
	case CARDNUMBER_K: return "K";
	default: return " ";
	}

	return " ";
}