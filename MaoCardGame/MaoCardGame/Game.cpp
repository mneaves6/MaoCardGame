#include "stdafx.h"
#include <vector>
#include <random>
#include "Game.h"
using namespace std;


bool Game::blCheckLegalMove(Card crdX)
{
	Card crdTop = crdLast();

	if (crdTop.valGet() != JACK && crdX.valGet() == JACK)
	{
		return true;
	}

	if (crdTop.valGet() == QUEEN && crdX.valGet() % 2 == 0)
	{
		return false;
	}

	if (crdTop.valGet() == KING && crdX.valGet() % 2 == 1)
	{
		return false;
	}

	if (crdTop.valGet() == JACK && crdX.valGet() != JACK && intDrawTwo == 0)
	{
		return true;
	}

	if (intDrawTwo > 0)
	{
		if (crdX.valGet() == SEVEN || crdX.valGet() == JACK)
		{
			return !(crdTop.valGet() == JACK && crdX.valGet() == JACK);
		}
	}

	if ((intDrawTwo == 0) && (crdTop.steGet() == crdX.steGet() || crdTop.valGet() == crdX.valGet()))
	{
		return !(crdTop.valGet() == JACK && crdX.valGet() == JACK);
	}

	return false;
}


void Game::vdShuffle()
{
	Card crdHold;

	if (vtrDiscard.size() == 52)
	{
		int i = rand() % vtrDiscard.size();

		crdHold = vtrDiscard[i];
		vtrDiscard.erase(vtrDiscard.begin() + i);

		if (crdHold.valGet() != TWO)
		{
			vdCardFunction(crdHold);
		}
	}

	else
	{
		crdHold = crdLast();
		vtrDiscard.pop_back();
	}

	while (vtrDiscard.size() > 0)
	{
		int intI = rand() % vtrDiscard.size();
		Card throwCard = vtrDiscard[intI];

		vtrDeck.push_back(throwCard);
		vtrDiscard.erase(vtrDiscard.begin() + intI);
	}

	vtrDiscard.push_back(crdHold);

	return;
}


void Game::vdDeal()
{
	//Added srand here because deal is only used once.
	srand(time(0));

	for (int intSuite = 0; intSuite <= 3; intSuite++)
	{
		for (int faceValue = 0; faceValue <= 12; faceValue++)
		{
			vtrDiscard.push_back(Card(Value(faceValue), Suite(intSuite)));
		}
	}

	vdShuffle();

	for (unsigned int intPlayerNumber = 0; intPlayerNumber < vtrPlayers.size(); intPlayerNumber++)
	{
		for (int intHandNumber = 0; intHandNumber < 7; intHandNumber++)
		{
			vtrPlayers[intPlayerNumber].vdDrawCard(vtrDeck[vtrDeck.size() - 1]);
			vtrDeck.pop_back();
		}
	}

	return;
}


bool Game::blWinCondition(Player y)
{
	return (y.intGetHandSize() == 0);
}



Card Game::crdLast()
{
	return vtrDiscard[vtrDiscard.size() - 1];
}


void Game::vdCardFunction(Card crdX)
{
	switch (crdX.valGet())
	{
	case TWO:
		if (blReverse == true)
		{
			intPlayerTurn++;
			if (unsigned(intPlayerTurn) > vtrPlayers.size())
			{
				intPlayerTurn = 0;
			}
		}
		else
		{
			intPlayerTurn--;
			if (intPlayerTurn < 0)
			{
				intPlayerTurn = vtrPlayers.size();
			}
		}
		return;

	case SEVEN:
		intDrawTwo++;
		return;

	case EIGHT:
		if (blReverse)
		{
			blReverse = false;
		}
		else
		{
			blReverse = true;
		}
		return;

	case JACK:
		if (intDrawTwo != 0)
		{
			intDrawTwo++;
		}
		return;

	case ACE:
		if (blReverse == true)
		{
			intPlayerTurn--;
			if (intPlayerTurn < 0)
			{
				intPlayerTurn = vtrPlayers.size();
			}
		}
		else
		{
			intPlayerTurn++;
			if (unsigned(intPlayerTurn) > vtrPlayers.size())
			{
				intPlayerTurn = 0;
			}
		}
		return;
	}

	return;
}


void Game::vdPlayerPlay(Player& plyY)
{
	cout << "It is your turn " << plyY.strGetName() << "." << endl;

	Card crdSelect = plyY.crdPlay();

	if (blCheckLegalMove(crdSelect))
	{
		plyY.vtrGetHand().erase(plyY.vtrGetHand().begin() + intFindCardIndex(plyY, crdSelect));
		vtrDiscard.push_back(crdSelect);
		vdCardFunction(crdSelect);
		cout << plyY.strGetName() << " has played " << crdSelect.strName() << endl;
	}

	else
	{
		cout << "You can't do that, ";
		Card crdTop;

		if (intDrawTwo > 0)
		{
			cout << "take " << intDrawTwo * 2 << " cards.";

			for (int i = 0; i < intDrawTwo * 2; i++)
			{
				if (vtrDeck.size() == 0)
				{
					vdShuffle();
				}
				
				if (vtrDeck.size() == 0)
				{
					cout << endl << "Looks like there are no cards in the deck. You lucked out this time!";
					break;
				}

				crdTop = vtrDeck[vtrDeck.size() - 1];
				plyY.vdDrawCard(crdTop);
				vtrDeck.pop_back();
			}

			intDrawTwo = 0;
		}

		else
		{
			if (vtrDeck.size() == 0)
			{
				vdShuffle();
			}
			
			if (vtrDeck.size() == 0)
			{
				cout << "good thing there's no more cards to draw..." << endl;
			}

			else
			{
				cout << "take a card.";
				crdTop = vtrDeck[vtrDeck.size() - 1];
				plyY.vdDrawCard(crdTop);
				vtrDeck.pop_back();
			}
		}

		cout << endl;
	}
	
	system("cmd /c cls");

	cout << plyY.strGetName() << " has " << plyY.intGetHandSize() << " cards now." << endl << endl;

	return;
}


std::vector <Player> Game::getPlayerVec()
{
	return vtrPlayers;
}


void Game::vdAddPlayer(Player plyY)
{
	vtrPlayers.push_back(plyY);
}


bool Game::blGetReverse()
{
	return blReverse;
}


int Game::intFindCardIndex(Player& plyY, Card crdX)
{

	for (unsigned int intI = 0; intI < plyY.vtrGetHand().size(); intI++)
	{
		if (plyY.vtrGetHand()[intI].strName() == crdX.strName())
		{
			return intI;
		}
	}
		
	return 0;
}


int Game::intGetPlayerTurn()
{
	return intPlayerTurn;
}


void Game::vdChangeTurn()
{
	if (blReverse)
	{
		intPlayerTurn--;

		if (intPlayerTurn < 0)
		{
			intPlayerTurn = vtrPlayers.size() - 1;
		}
	}

	else
	{
		intPlayerTurn++;

		if (unsigned(intPlayerTurn) > vtrPlayers.size() - 1)
		{
			intPlayerTurn = 0;
		}
	}

	return;
}


void Game::vdNoCardsinHand(Player& plyY)
{
	if (vtrDeck.size() == 0)
	{
		vdShuffle();
	}

	Card crdTop = vtrDeck[vtrDeck.size() - 1];
	plyY.vdDrawCard(crdTop);

	cout << "Oh, looks like you need a card " << plyY.strGetName() << "." << endl;

	vtrDeck.pop_back();
}