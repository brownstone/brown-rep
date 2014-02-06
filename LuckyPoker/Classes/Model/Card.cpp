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
	// ¢¿ ¡ß  ¢½  ¢»   ¢» ¢¼ ¢½ ¢¾ ¢¿ ¢À ¢Á ¢Â ¢Ã ¢Ä ¢Å ¡Þ ¡ß
	//return " ¢¿ ¡ß  ¢½  ¢»";
	//switch (m_eCard)
	//{
	//case CARD_C1: return "¢ÀA ";
	//case CARD_C2: return "¢À2 ";
	//case CARD_C3: return "¢À3 ";
	//case CARD_C4: return "¢À4 ";
	//case CARD_C5: return "¢À5 ";
	//case CARD_C6: return "¢À6 ";
	//case CARD_C7: return "¢À7 ";
	//case CARD_C8: return "¢À8 ";
	//case CARD_C9: return "¢À9 ";
	//case CARD_C10: return "¢ÀJ ";
	//case CARD_C11: return "¢ÀQ ";
	//case CARD_C12: return "¢ÀK ";
	//case CARD_C13: return "¢ÀA ";
	//case CARD_D1: return "¡ÞA ";
	//case CARD_D2: return "¡Þ2 ";
	//case CARD_D3: return "¡Þ3 ";
	//case CARD_D4: return "¡Þ4 ";
	//case CARD_D5: return "¡Þ5 ";
	//case CARD_D6: return "¡Þ6 ";
	//case CARD_D7: return "¡Þ7 ";
	//case CARD_D8: return "¡Þ8 ";
	//case CARD_D9: return "¡Þ9 ";
	//case CARD_D10: return "¡ÞJ ";
	//case CARD_D11: return "¡ÞQ ";
	//case CARD_D12: return "¡ÞK ";
	//case CARD_D13: return "¡ÞA ";
	//case CARD_H1: return "¢¾A ";
	//case CARD_H2: return "¢¾2 ";
	//case CARD_H3: return "¢¾3 ";
	//case CARD_H4: return "¢¾4 ";
	//case CARD_H5: return "¢¾5 ";
	//case CARD_H6: return "¢¾6 ";
	//case CARD_H7: return "¢¾7 ";
	//case CARD_H8: return "¢¾8 ";
	//case CARD_H9: return "¢¾9 ";
	//case CARD_H10: return "¢¾J ";
	//case CARD_H11: return "¢¾Q ";
	//case CARD_H12: return "¢¾K ";
	//case CARD_H13: return "¢¾A ";
	//case CARD_S1: return "¢¼A ";
	//case CARD_S2: return "¢¼2 ";
	//case CARD_S3: return "¢¼3 ";
	//case CARD_S4: return "¢¼4 ";
	//case CARD_S5: return "¢¼5 ";
	//case CARD_S6: return "¢¼6 ";
	//case CARD_S7: return "¢¼7 ";
	//case CARD_S8: return "¢¼8 ";
	//case CARD_S9: return "¢¼9 ";
	//case CARD_S10: return "¢¼J ";
	//case CARD_S11: return "¢¼Q ";
	//case CARD_S12: return "¢¼K ";
	//case CARD_S13: return "¢¼A ";
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
	case CARD_C10: return "CJ ";
	case CARD_C11: return "CQ ";
	case CARD_C12: return "CK ";
	case CARD_C13: return "CA ";
	case CARD_D1: return "DA ";
	case CARD_D2: return "D2 ";
	case CARD_D3: return "D3 ";
	case CARD_D4: return "D4 ";
	case CARD_D5: return "D5 ";
	case CARD_D6: return "D6 ";
	case CARD_D7: return "D7 ";
	case CARD_D8: return "D8 ";
	case CARD_D9: return "D9 ";
	case CARD_D10: return "DJ ";
	case CARD_D11: return "DQ ";
	case CARD_D12: return "DK ";
	case CARD_D13: return "DA ";
	case CARD_H1: return "HA ";
	case CARD_H2: return "H2 ";
	case CARD_H3: return "H3 ";
	case CARD_H4: return "H4 ";
	case CARD_H5: return "H5 ";
	case CARD_H6: return "H6 ";
	case CARD_H7: return "H7 ";
	case CARD_H8: return "H8 ";
	case CARD_H9: return "H9 ";
	case CARD_H10: return "HJ ";
	case CARD_H11: return "HQ ";
	case CARD_H12: return "HK ";
	case CARD_H13: return "HA ";
	case CARD_S1: return "SA ";
	case CARD_S2: return "S2 ";
	case CARD_S3: return "S3 ";
	case CARD_S4: return "S4 ";
	case CARD_S5: return "S5 ";
	case CARD_S6: return "S6 ";
	case CARD_S7: return "S7 ";
	case CARD_S8: return "S8 ";
	case CARD_S9: return "S9 ";
	case CARD_S10: return "SJ ";
	case CARD_S11: return "SQ ";
	case CARD_S12: return "SK ";
	case CARD_S13: return "SA ";
	default: return " "; break;
	}

}