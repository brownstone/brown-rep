#ifndef __SEVEN_POKER_H__
#define __SEVEN_POKER_H__

#include "PokerDefines.h"

class SevenPoker
{
public:
	SevenPoker();
	virtual ~SevenPoker();

	static const int MAX_Y = 4;
	static const int MAX_X = 14;

	struct CardBit
	{
		bool abCardBit[MAX_Y][MAX_X];
	};

	void GetJokboResultForFindSun(const Player::PokerPlayerInfo& kPokerPlayerInfo, JokboResult& kJokboResult) const;
	void GetJokboResultForSettle(const Player::PokerPlayerInfo& kPokerPlayerInfo, JokboResult& kJokboResult) const;
	bool CompareJokbo(const JokboResult& lhs, const JokboResult& rhs) const;
	Betting GetBetting(Betting ePriviousBetting) const;
    
private:
	void CalcJokbo(CardBit& kCardBit, JokboResult& kJokboResult) const;

};

#endif // __SEVEN_POKER_H__
