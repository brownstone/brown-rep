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
	BETTING_NONE    = 0x0,
	BETTING_CHECK   = 0x1,
	BETTING_BBING   = 0x2,
	BETTING_CALL    = 0x4,
	BETTING_QUARTER = 0x8,
	BETTING_HALF    = 0x10,
	BETTING_FULL    = 0x20,
	BETTING_DOUBLE  = 0x40,
	//BETTING_ALLIN   = 0x80,
	BETTING_DIE     = 0x80,
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

enum BetAction
{
    BET_ACTION_NONE,
    BET_ACTION_THINK_PREPARE,
    BET_ACTION_THINK,
    BET_ACTION_BETTING,
    BET_ACTION_THROW,
    BET_ACTION_DONE,
    BET_ACTION_MAX,
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

	JokboResult()
	{
		Init();
	}

	void Init()
	{
		eJokbo = JOKBO_NONE;
		kTopCard.Clear();
		kSecondCard.Clear();
		akFlush[0].Clear();
		akFlush[1].Clear();
		akFlush[2].Clear();
		akFlush[3].Clear();
	}

	bool Changed(const JokboResult& rhs)
	{
		bool changed = false;
		changed |= (eJokbo != rhs.eJokbo);
		changed |= !kTopCard.SameCard(rhs.kTopCard);
		changed |= !kSecondCard.SameCard(rhs.kSecondCard);
		changed |= !akFlush[0].SameCard(rhs.akFlush[0]);
		changed |= !akFlush[1].SameCard(rhs.akFlush[1]);
		changed |= !akFlush[2].SameCard(rhs.akFlush[2]);
		changed |= !akFlush[3].SameCard(rhs.akFlush[3]);

		return changed;
	}

	char* GetStringInfo(char szInformation[]) const
	{
		szInformation[0] = 0;

		static const char* szJokboName[] = {
			"NONE",
			"TOP",
			"OnePair",
			"TwoPair",
			"Trifle",
			"Straight",
			"BackStraight",
			"RoyalStraight",
			"Flush",
			"FullHouse",
			"FourCard",
			"StraightFlush",
			"BackStraightFlush",
			"RoyalStraightFlush",
		};

		switch (eJokbo)
		{
		case  JOKBO_NOPAIR:
		case  JOKBO_ONEPAIR:
		case  JOKBO_TWOPAIR:
		case  JOKBO_TRIFLE:
			sprintf(szInformation, "%s %s", kTopCard.GetNumberToString(), szJokboName[eJokbo]);
			break;
		default: 
			strcpy(szInformation, szJokboName[eJokbo]);
			break;
		}

		return szInformation;
	}
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


static const unsigned int MAX_FIRSTCARD_COUNT = 3;
static const unsigned int MAX_HIDDENCARD_COUNT = 2;
static const unsigned int MAX_OPENCARD_COUNT = 4;
static const unsigned int MAX_LASTCARD_COUNT = 1;
static const unsigned int MAX_HANDCARD_COUNT = MAX_HIDDENCARD_COUNT + MAX_OPENCARD_COUNT + MAX_LASTCARD_COUNT;
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
struct BettingInput
{
    unsigned char ucPlayerIndex;
    unsigned char ucBetIndex;
    unsigned char ucTurnCount;
    unsigned char ucBetting;
};


struct PokerPlayerInfo
{
	unsigned int	nPlayerKey;
	unsigned int	nTotalMoney;
	bool			bDie;
	Card			akFirstCard[MAX_FIRSTCARD_COUNT];
	Card			akHiddenCard[MAX_HIDDENCARD_COUNT];
	Card			akOpenCard[MAX_OPENCARD_COUNT];
	Card			kLastCard;
	bool			bSchoolMoney;
	unsigned int	nTempSchoolMoney;
	bool			bChoice;

    BetAction       eBetAction;
    float           fThinkTime;
    float           fThrowTime;
    bool            onMyTurn;
    int             ePrepareBetting;


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

	PokerPlayerInfo()
	{
		Init();
	}

	void Init()
	{
		nPlayerKey = 0;
		nTotalMoney = 0;

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
		kLastCard.Clear();
		bSchoolMoney = false;
		nTempSchoolMoney = 0;
		bChoice = false;
        eBetAction = BET_ACTION_NONE;
        ePrepareBetting = 0;
        fThinkTime = 0.0f;
        fThrowTime = 0.0f;
        onMyTurn = false;
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
        changed |= (onMyTurn != rhs.onMyTurn);
        changed |= (ePrepareBetting != rhs.ePrepareBetting);
        

		return changed;
	}

	void GetStringInfo(char szInformation[]) const
	{
		szInformation[0] = 0;

		sprintf(szInformation, "%d", nTotalMoney);
		//strcat(szInformation, "\n");

		//char szCard[128];
		//strcat_s(szInformation, 256, GetJokboStringInfo(m_kJokboResult.eJokbo, szCard));
		//strcat_s(szInformation, 256, " : ");
		//strcat_s(szInformation, 256, GetCardStringInfo(m_kJokboResult.kTopCard, szCard));
		//strcat_s(szInformation, 256, "\n");

		//for (unsigned int ui = 0; ui < MAX_OPENCARD_COUNT; ui++)
		//{
		//	strcat_s(szInformation, 256, akOpenCard[ui].GetString());
		//}
		//strcat_s(szInformation, 256, "\n");

		//for (unsigned int ui = 0; ui < MAX_HIDDENCARD_COUNT; ui++)
		//{
		//	strcat_s(szInformation, 256, GetCardStringInfo(m_kPokerPlayerInfo.akHiddenCard[ui], szCard));
		//}
		//strcat_s(szInformation, 256, "\n");
	}

    void GetBetString(char szInformation[], int betIndex) const
    {
        szInformation[0] = 0;

        Betting bet;
        int money = 0;
        if (betIndex == 1)
        {
            bet = eBet1;
            money = nLastBet1Money;
        }
        if (betIndex == 2)
        {
            bet = eBet2;
            money = nLastBet2Money;
        }
        if (betIndex == 3)
        {
            bet = eBet3;
            money = nLastBet3Money;
        }
        if (betIndex == 4)
        {
            bet = eBet4;
            money = nLastBet4Money;
        }


        switch (bet)
        {
        case BETTING_NONE:	strcat(szInformation, " ");	break;
        case BETTING_CHECK:	sprintf(szInformation, "Check \n %d", money);	break;
        case BETTING_BBING:	sprintf(szInformation, "BBing \n %d", money);	break;
        case BETTING_CALL:	sprintf(szInformation, "Call \n %d", money);	break;
        case BETTING_QUARTER:	sprintf(szInformation, "Quarter \n %d", money);	break;
        case BETTING_HALF:	sprintf(szInformation, "Half \n %d", money);	break;
        case BETTING_FULL:	sprintf(szInformation, "Full \n %d", money);	break;
        case BETTING_DOUBLE:	sprintf(szInformation, "Double \n %d", money);	break;
        //case BETTING_ALLIN:	strcat(szInformation, "B1_AL");	break;
        case BETTING_DIE:	strcat(szInformation, "Die");	break;
        }
        //sprintf_s(szCard, 128, "  %d", m_kPokerPlayerInfo.uiBet1Money);
        //strcat(szInformation, szCard);
    }

};

struct PlayerManInfo
{
	unsigned int	curPlayerKey;
	unsigned int	curPlayerIndex;
	unsigned int	sunPlayerIndex;
	unsigned int	leftTopIndex;
	unsigned int	turnIndex;
    unsigned int    turnCount;

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
		sunPlayerIndex = INVALID_PLAYER_INDEX;
		leftTopIndex = INVALID_PLAYER_INDEX;
		turnIndex = INVALID_PLAYER_INDEX;
        turnCount = 0;
	}
    bool Changed(const PlayerManInfo& rhs)
    {
        bool changed = false;
        changed |= (sunPlayerIndex != rhs.sunPlayerIndex);
        changed |= (turnIndex != rhs.turnIndex);
        changed |= (turnCount != rhs.turnCount);

        return changed;
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

		sprintf(szInformation, " %d \n %d \n call: %d \n raise: %d", seedMoney, titleMoney, callMoney, raiseCount);
	}
};
#endif // __POKER_DEFINES_H__


