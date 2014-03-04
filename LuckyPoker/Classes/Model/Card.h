#ifndef __CARD_H__
#define __CARD_H__


class Card
{
public:
	enum CardPicture
	{
		CARDPICTURE_CLOVER,
		CARDPICTURE_DIAMOND,
		CARDPICTURE_HEART,
		CARDPICTURE_SPADE,
		CARDPICTURE_MAX,
	};
	enum CardNumber
	{
		CARDNUMBER_A,
		CARDNUMBER_2,
		CARDNUMBER_3,
		CARDNUMBER_4,
		CARDNUMBER_5,
		CARDNUMBER_6,
		CARDNUMBER_7,
		CARDNUMBER_8,
		CARDNUMBER_9,
		CARDNUMBER_10,
		CARDNUMBER_J,
		CARDNUMBER_Q,
		CARDNUMBER_K,
		CARDNUMBER_MAX, //12
	};

	enum PokerCard
	{
		CARD_NONE,
		//Clover
		CARD_C1, CARD_C2, CARD_C3, CARD_C4, CARD_C5, CARD_C6, CARD_C7, CARD_C8, CARD_C9, CARD_C10, CARD_C11, CARD_C12, CARD_C13,
		//Diamond
		CARD_D1, CARD_D2, CARD_D3, CARD_D4, CARD_D5, CARD_D6, CARD_D7, CARD_D8, CARD_D9, CARD_D10, CARD_D11, CARD_D12, CARD_D13,
		//Heart
		CARD_H1, CARD_H2, CARD_H3, CARD_H4, CARD_H5, CARD_H6, CARD_H7, CARD_H8, CARD_H9, CARD_H10, CARD_H11, CARD_H12, CARD_H13,
		//Spade
		CARD_S1, CARD_S2, CARD_S3, CARD_S4, CARD_S5, CARD_S6, CARD_S7, CARD_S8, CARD_S9, CARD_S10, CARD_S11, CARD_S12, CARD_S13,

		CARD_MAX_COUNT,
	};

	static const unsigned int MAX_CARD_COUNT = (CARD_MAX_COUNT - 1);
	static const unsigned int MAX_CARDNUMBER_COUNT = CARDNUMBER_MAX;


public:
	Card();
	virtual ~Card();

	void Clear();

	void SetCard(PokerCard eCard);
	void SetCard(CardPicture ePicture, CardNumber eNumber);

	PokerCard		GetCard() const;
	CardPicture		GetPicture() const;
	CardNumber		GetNumber() const;
	unsigned int	GetValue() const;

	bool SameCard(const Card& rhs);

	const char* GetString() const;


protected:
	void			SetData(PokerCard eCard, CardPicture ePicture, CardNumber uiNumber);
	PokerCard		m_eCard;
	CardPicture		m_ePicture;
	CardNumber		m_eNumber;
	unsigned int 	m_nValue;

};

#endif // __CARD_H__
