#ifndef __POKER_DEFINES_H__
#define __POKER_DEFINES_H__

#include "cocos2d.h"
#include "Card.h"


enum PokerSequence 
{
	POKERSEQUENCE_NONE = 0,
	POKERSEQUENCE_START, //무조건 스타트가 된다. 한타임이다. 이때 Poker Player를 정리한다.
	POKERSEQUENCE_SHUFFLE,
	POKERSEQUENCE_DEALFIRSTCARD,
	POKERSEQUENCE_CHOICE,
	POKERSEQUENCE_CHOICE_DONE,
	POKERSEQUENCE_DEAL1,
	POKERSEQUENCE_DEAL1_DONE,
	POKERSEQUENCE_BET1,
	POKERSEQUENCE_DEAL2,
	POKERSEQUENCE_DEAL2_DONE,
	POKERSEQUENCE_BET2,
	POKERSEQUENCE_DEAL3,
	POKERSEQUENCE_DEAL3_DONE,
	POKERSEQUENCE_BET3,
	POKERSEQUENCE_DEAL4, // Hidden
	POKERSEQUENCE_SHOW_HIDDEN,
	POKERSEQUENCE_DEAL4_DONE,
	POKERSEQUENCE_BET4,
	POKERSEQUENCE_HILOW,
	POKERSEQUENCE_OPEN,
	POKERSEQUENCE_SETTLE, //정산
	POKERSEQUENCE_RESULT,
	POKERSEQUENCE_END,

	POKERSEQUENCE_MAX,
};

const static char* PokerSequenceStr [] = {
	"NONE",
	"START", //무조건 스타트가 된다. 한타임이다. 이때 Poker Player를 정리한다.
	"SHUFFLE",
	"DEALFIRSTCARD",
	"CHOICE",
	"CHOICE_DONE",
	"DEAL1",
	"DEAL1_DONE",
	"BET1",
	"DEAL2",
	"DEAL2_DONE",
	"BET2",
	"DEAL3",
	"DEAL3_DONE",
	"BET3",
	"DEAL4", // Hidden
	"SHOW_HIDDEN",
	"DEAL4_DONE",
	"BET4",
	"HILOW",
	"OPEN",
	"SETTLE", //정산
	"RESULT",
	"END",

	"MAX",
};


enum Betting
{
	BETTING_NONE,
	BETTING_CHECK,
	BETTING_BBING,
	BETTING_CALL,
	BETTING_QUARTER,
	BETTING_HALF,
	BETTING_FULL,
	BETTING_DOUBLE,
	BETTING_ALLIN,
	BETTING_DIE,
};

enum Jokbo
{
	JOKBO_NONE,
	JOKBO_NOPAIR,
	JOKBO_ONEPAIR,
	JOKBO_TWOPAIR,
	JOKBO_TRIFLE,
	JOKBO_STRAIGHT,
	JOKBO_BACKSTRAIGHT,
	JOKBO_ROYALSTRAIGHT,
	JOKBO_FLUSH,
	JOKBO_FULLHOUSE,
	JOKBO_FOURCARD,
	JOKBO_STRAIGHTFLUSH,
	JOKBO_BACKSTRAIGHTFLUSH,
	JOKBO_ROYALSTRAIGHTFLUSH,
	JOKBO_MAX,
};

enum BetLimit
{
    BETLIMIT_QUARTER,
    BETLIMIT_HALF,
    BETLIMIT_FULL,
};

struct PokerOption
{
    unsigned int uiSeedMoney;
    BetLimit	 eBetLimit;
};

struct JokboResult
{
    Jokbo	eJokbo;
    Card	kTopCard;
    Card	kSecondCard; // 두번째로 높은 카드를 비교할때는 투페어일때 뿐이다.
    Card	akFlush[4];  // 플러시
};

struct AiWeight
{
    bool isFourCard;
    bool isHouse;
    bool isFlush;
    bool isStraite;
    JokboResult result;
    
    void Init()
    {
        isFourCard = false;
        isHouse = false;
        isFlush = false;
        isStraite = false;
        result.eJokbo = JOKBO_NONE;
    }
};

static const int MAX_CARD_Y = 4;
static const int MAX_CARD_X = 14;

struct CardBit
{
    bool abCardBit[MAX_CARD_Y][MAX_CARD_X];
};


static const unsigned int MAX_FIRSTCARD_COUNT = 4;
static const unsigned int MAX_OPENCARD_COUNT = 4;
static const unsigned int MAX_HIDDENCARD_COUNT = 3;
static const unsigned int MAX_POKERPLAYER_COUNT = 5;
static const int INVALID_PLAYER_INDEX = -1;

/*
1. 노페어 : 탑카드의 숫자, 무늬 비교
2. 원페어 : 탑카드의 숫자, 무늬 비교 (같은 아워이어도 스페이드쪽이 이김)
3. 투페어 : 탑카드의 숫자, 세컨카드의 숫자, 같으면 탑카드의 무늬 비교 (같은 아카투페어이면 스페이드 에이스 갖고 있는쪽이 이김)
4. 트리플 : 탑카드의 숫자
5. 스트레이트 : 동일
6. 플러시 : 높은 숫자를 차례로 비교
7. 포카드 : 동일
8. 스티플 : 동일

투페어와 플러시만 예외상황이고 나머지는 동일한 룰에 따른다.
*/


struct Deal3CardInfo
{
	unsigned char ucPlayerIndex;
	unsigned char aucCard[4];
};
struct DealCardInfo
{
	unsigned char ucPlayerIndex;
	unsigned char ucCard;
};

struct PokerPlayerInfo
{
	unsigned int	nPlayerKey;
	unsigned int	nTotalMoney;
	bool			bDie;
	Card			akFirstCard[MAX_FIRSTCARD_COUNT];
	Card			kDropCard;
	Card			akOpenCard[MAX_OPENCARD_COUNT];
	Card			akHiddenCard[MAX_HIDDENCARD_COUNT];
	bool			bSchoolMoney;
	unsigned int	nTempSchoolMoney;
	bool			bChoice;
	Betting			eBet1;
	unsigned int	nLastBet1Money;
	unsigned int	nTempBet1Money;
	Betting			eBet2;
	unsigned int	nLastBet2Money;
	unsigned int	nTempBet2Money;
	Betting			eBet3;
	unsigned int	nLastBet3Money;
	unsigned int	nTempBet3Money;
	Betting			eBet4;
	unsigned int	nLastBet4Money;
	unsigned int	nTempBet4Money;
	float			thinkTime;

	PokerPlayerInfo()
	{
		Init();
	}

	void Init()
	{
		nPlayerKey = 0;
		nTotalMoney = 0;
		thinkTime = 0;

		ClearBettingInfo();
	}
	void ClearBettingInfo()
	{
		bDie = false;
		for (unsigned int i = 0; i < MAX_OPENCARD_COUNT; i++)
		{
			akOpenCard[i].Clear();
		}
		for (unsigned int i = 0; i < MAX_HIDDENCARD_COUNT; i++)
		{
			akHiddenCard[i].Clear();
		}
		bSchoolMoney = false;
		nTempSchoolMoney = 0;
		bChoice = false;
		eBet1 = BETTING_NONE;
		nLastBet1Money = 0;
		nTempBet1Money = 0;
		eBet2 = BETTING_NONE;
		nLastBet2Money = 0;
		nTempBet2Money = 0;
		eBet3 = BETTING_NONE;
		nLastBet3Money = 0;
		nTempBet3Money = 0;
		eBet4 = BETTING_NONE;
		nLastBet4Money = 0;
		nTempBet4Money = 0;
		thinkTime = 0;
	}

	bool Changed(const PokerPlayerInfo& rhs)
	{
		bool changed = false;
		for (int i = 0; i < MAX_OPENCARD_COUNT; i++)
		{
			changed |= (!akOpenCard[i].SameCard(rhs.akOpenCard[i]));
		}
		changed |= (nTotalMoney != rhs.nTotalMoney);
		changed |= (eBet1 != rhs.eBet1);
		changed |= (eBet2 != rhs.eBet2);
		changed |= (eBet3 != rhs.eBet3);
		changed |= (eBet4 != rhs.eBet4);

		return changed;
	}

	void GetStringInfo(char szInformation[]) const
	{
		szInformation[0] = 0;

		sprintf(szInformation, "%d", nTotalMoney);
		strcat(szInformation, "\n");

		//char szCard[128];
		//strcat_s(szInformation, 256, GetJokboStringInfo(m_kJokboResult.eJokbo, szCard));
		//strcat_s(szInformation, 256, " : ");
		//strcat_s(szInformation, 256, GetCardStringInfo(m_kJokboResult.kTopCard, szCard));
		//strcat_s(szInformation, 256, "\n");

		for (unsigned int ui = 0; ui < MAX_OPENCARD_COUNT; ui++)
		{
			strcat_s(szInformation, 256, akOpenCard[ui].GetString());
		}
		strcat_s(szInformation, 256, "\n");

		//for (unsigned int ui = 0; ui < MAX_HIDDENCARD_COUNT; ui++)
		//{
		//	strcat_s(szInformation, 256, GetCardStringInfo(m_kPokerPlayerInfo.akHiddenCard[ui], szCard));
		//}
		//strcat_s(szInformation, 256, "\n");

		switch (eBet1)
		{
		case BETTING_NONE:	strcat(szInformation, "B1_NO");	break;
		case BETTING_CHECK:	strcat(szInformation, "B1_CH");	break;
		case BETTING_BBING:	strcat(szInformation, "B1_BB");	break;
		case BETTING_CALL:	strcat(szInformation, "B1_CA");	break;
		case BETTING_QUARTER:	strcat(szInformation, "B1_QU");	break;
		case BETTING_HALF:	strcat(szInformation, "B1_HA");	break;
		case BETTING_FULL:	strcat(szInformation, "B1_FU");	break;
		case BETTING_DOUBLE:	strcat(szInformation, "B1_DO");	break;
		case BETTING_ALLIN:	strcat(szInformation, "B1_AL");	break;
		case BETTING_DIE:	strcat(szInformation, "B1_DI");	break;
		}
		//sprintf_s(szCard, 128, "  %d", m_kPokerPlayerInfo.uiBet1Money);
		//strcat(szInformation, szCard);
		strcat(szInformation, "\n");

		//switch (eBet2)
		//{
		//case BETTING_NONE:	strcat(szInformation, "B2_NO");	break;
		//case BETTING_CHECK:	strcat(szInformation, "B2_CH");	break;
		//case BETTING_BBING:	strcat(szInformation, "B2_BB");	break;
		//case BETTING_CALL:	strcat(szInformation, "B2_CA");	break;
		//case BETTING_QUARTER:	strcat(szInformation, "B2_QU");	break;
		//case BETTING_HALF:	strcat(szInformation, "B2_HA");	break;
		//case BETTING_FULL:	strcat(szInformation, "B2_FU");	break;
		//case BETTING_DOUBLE:	strcat(szInformation, "B2_DO");	break;
		//case BETTING_ALLIN:	strcat(szInformation, "B2_AL");	break;
		//case BETTING_DIE:	strcat(szInformation, "B2_DI");	break;
		//}
		////sprintf_s(szCard, 128, "  %d", m_kPokerPlayerInfo.uiBet2Money);
		////strcat(szInformation, szCard);
		//strcat(szInformation, "\n");

		//switch (eBet3)
		//{
		//case BETTING_NONE:	strcat(szInformation, "B3_NO");	break;
		//case BETTING_CHECK:	strcat(szInformation, "B3_CH");	break;
		//case BETTING_BBING:	strcat(szInformation, "B3_BB");	break;
		//case BETTING_CALL:	strcat(szInformation, "B3_CA");	break;
		//case BETTING_QUARTER:	strcat(szInformation, "B3_QU");	break;
		//case BETTING_HALF:	strcat(szInformation, "B3_HA");	break;
		//case BETTING_FULL:	strcat(szInformation, "B3_FU");	break;
		//case BETTING_DOUBLE:	strcat(szInformation, "B3_DO");	break;
		//case BETTING_ALLIN:	strcat(szInformation, "B3_AL");	break;
		//case BETTING_DIE:	strcat(szInformation, "B3_DI");	break;
		//}
		////sprintf_s(szCard, 128, "  %d", m_kPokerPlayerInfo.uiBet3Money);
		////strcat(szInformation, szCard);
		//strcat(szInformation, "\n");

		//switch (eBet4)
		//{
		//case BETTING_NONE:	strcat(szInformation, "B4_NO");	break;
		//case BETTING_CHECK:	strcat(szInformation, "B4_CH");	break;
		//case BETTING_BBING:	strcat(szInformation, "B4_BB");	break;
		//case BETTING_CALL:	strcat(szInformation, "B4_CA");	break;
		//case BETTING_QUARTER:	strcat(szInformation, "B4_QU");	break;
		//case BETTING_HALF:	strcat(szInformation, "B4_HA");	break;
		//case BETTING_FULL:	strcat(szInformation, "B4_FU");	break;
		//case BETTING_DOUBLE:	strcat(szInformation, "B4_DO");	break;
		//case BETTING_ALLIN:	strcat(szInformation, "B4_AL");	break;
		//case BETTING_DIE:	strcat(szInformation, "B4_DI");	break;
		//}
		////sprintf_s(szCard, 128, "  %d", uiBet4Money);
		////strcat(szInformation, szCard);
		//strcat(szInformation, "\n");
	}

};

struct PlayerManInfo
{
	unsigned int	curPlayerKey;
	unsigned int	curPlayerIndex;
	unsigned int	sunPlayerIndex;
	unsigned int	leftTopIndex;
	unsigned int	turnIndex;
	float thinkTime;

	PlayerManInfo()
	{
		Init();
	}

	void Init()
	{
		curPlayerKey = INVALID_PLAYER_INDEX;
		Clear();
	}
	void Clear()
	{
		curPlayerIndex = INVALID_PLAYER_INDEX;
		sunPlayerIndex = INVALID_PLAYER_INDEX;
		leftTopIndex = INVALID_PLAYER_INDEX;
		turnIndex = INVALID_PLAYER_INDEX;
		thinkTime = 0;
	}
};

struct TableInfo
{
	unsigned int seedMoney;
	unsigned int titleMoney;
	unsigned int callMoney;
	unsigned int raiseCount; // 레이스 카운트 이것으로 Both인지를 알수 있다.
	TableInfo()
	{
		Init();
	}

	void Init()
	{
		seedMoney = 0;
		Clear();
	}

	void Clear()
	{
		titleMoney = 0;
		callMoney = 0;
		raiseCount = 0;
	}

	bool Changed(const TableInfo& rhs)
	{
		bool changed = false;
		changed |= (seedMoney != rhs.seedMoney);
		changed |= (titleMoney != rhs.titleMoney);
		changed |= (callMoney != rhs.callMoney);
		changed |= (raiseCount != rhs.raiseCount);

		return changed;
	}

	void GetStringInfo(char szInformation[]) const
	{
		szInformation[0] = 0;

		sprintf(szInformation, " %d \n %d \n %d \n %d", seedMoney, titleMoney, callMoney, raiseCount);
	}
};
#endif // __POKER_DEFINES_H__


