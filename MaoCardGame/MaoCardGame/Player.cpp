#include "stdafx.h"
#include <vector>
#include "Player.h"
#include "Card.h"
using namespace std;


int Player::intGetHandSize()
{
	if (vtrHand.empty())
	{
		intHandSize = 0;
	}

	else
	{
		intHandSize = vtrHand.size();
	}
	
	return intHandSize;
}


string Player::strGetName()
{
	return strName;
}


Card Player::crdPlay()
{
	intCardIndex = vtrHand.size();

	for (int intI = 0; intI < intCardIndex; intI++)
	{
		cout << intI + 1 << ". " << vtrHand[intI].strName() << endl;
	}

	bool blCheck = false;

	while (blCheck == false)
	{
		bool blValidInput;

		do
		{
			cout << "Input: ";
			cin >> intCardIndex;
			blValidInput = intCardIndex;
			intCardIndex--;

			if (!blValidInput)
			{
				cin.clear();
				while (cin.get() != '\n');
			}
		}
		while (!blValidInput);

		if (intCardIndex > signed(vtrHand.size() - 1) || intCardIndex < 0)
		{
			blCheck = false;
			cout << "Please put in a correct value between 1 and " << vtrHand.size() << endl;
		}
		else
		{
			blCheck = true;
		}
	}

	return vtrHand[intCardIndex];
}

 
void Player::vdDrawCard(Card crdAdd)
{
	Player::vtrHand.push_back(crdAdd);
}


std::vector <Card> Player::vtrGetHand()
{
	return vtrHand;
}