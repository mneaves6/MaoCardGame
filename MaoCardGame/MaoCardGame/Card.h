#pragma once
#include <cstdlib>
#include <ctime>
#include <string>
using std::string;


enum Suite { CLUBS, DIAMONDS, HEARTS, SPADES };
enum Value { ACE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING };


class Card
{
public:
	Card(Value valFace = ACE, Suite steSuite = CLUBS) : steSuite(steSuite), valFace(valFace) {}
	Suite steGet() { return steSuite; }
	Value valGet() { return valFace; }
	static string strSuiteName(Suite steS);
	static string strValueName(Value valV);
	string strName() { return strValueName(valFace) + " of " + strSuiteName(steSuite); }

private:
	Suite steSuite;
	Value valFace;
};