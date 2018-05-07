#include "stdafx.h"
#include "Card.h"


string Card::strSuiteName(Suite steS)
{
	switch (steS)
	{
	case CLUBS:
		return "Clubs";

	case DIAMONDS:
		return "Diamonds";

	case HEARTS:
		return "Hearts";

	case SPADES:
		return "Spades";

	default:
		throw std::out_of_range("Suite value out of range");
	}
}


string Card::strValueName(Value valV)
{
	switch (valV)
	{
	case ACE:
		return "Ace";

	case TWO:
		return "Two";

	case THREE:
		return "Three";

	case FOUR:
		return "Four";

	case FIVE:
		return "Five";

	case SIX:
		return "Six";

	case SEVEN:
		return "Seven";

	case EIGHT:
		return "Eight";

	case NINE:
		return "Nine";

	case TEN:
		return "Ten";

	case JACK:
		return "Jack";

	case QUEEN:
		return "Queen";

	case KING:
		return "King";

	default:
		throw std::out_of_range("Face value out of range");
	}
}