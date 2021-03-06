// MaoCardGame.cpp : Defines the entry point for the console application.
//


#include "stdafx.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>
#include "Card.h"
#include "Player.h"
#include "Game.h"
using namespace std;


const int INTMINPLAYERS = 2;
const int INTMAXPLAYERS = 6;


int main()
{
	cout << "Welcome to Mao!" << endl;
	cout << "A card game where the rule is not explaining them." << endl;
	cout << " " << endl;

	int intNumberPlayer = 0;
	bool blValidInput;

	while (intNumberPlayer < INTMINPLAYERS || intNumberPlayer > INTMAXPLAYERS)
	{
		do
		{
			cout << "How many players are there?" << endl;
			cin >> intNumberPlayer;
			blValidInput = intNumberPlayer;
			if (!blValidInput)
			{
				cin.clear();
				while (cin.get() != '\n');
			}

			cout << endl;
		}
		while (!blValidInput);

		if (intNumberPlayer < INTMINPLAYERS)
		{
			cout << "Not enough players." << endl;
		}
		
		else if (intNumberPlayer > INTMAXPLAYERS)
		{
			cout << "Too many players. MAX: " << INTMAXPLAYERS << endl;
		}
		cout << endl;
	}

	Game gmMao;
	string strEnterName;

	cin.ignore();

	for (int i = 0; i < intNumberPlayer; i++)
	{
		bool blDoubleName = false;

		do
		{
			blDoubleName = false;
			cout << "Enter the name of Player " << i + 1 << ": ";
			getline(cin, strEnterName);

			if (gmMao.getPlayerVec().size() > 0)
				for (unsigned int intK = 0; intK < gmMao.getPlayerVec().size(); intK++)
				{
					if (strEnterName == gmMao.getPlayerVec()[intK].strGetName())
					{
						cout << "That name has already been used..." << endl << endl;
						blDoubleName = true;
						break;
					}
				}

		}
		while (blDoubleName);

		Player play(strEnterName);

		gmMao.vdAddPlayer(play);
	}

	int intTurn = gmMao.intGetPlayerTurn();

	gmMao.vdDeal();

	cout << endl << "A " << gmMao.crdLast().strName() << " is placed on the discard pile." << endl;
	cout << "Let the game begin!" << endl << endl;

	do
	{
		intTurn = gmMao.intGetPlayerTurn();

		if (gmMao.getPlayerVec()[intTurn].intGetHandSize() == 0)
		{
			cout << "You can't end on a two " << gmMao.getPlayerVec()[intTurn].strGetName() << "." << endl;

			gmMao.vdNoCardsinHand(gmMao.getPlayerVec()[intTurn]);
		}
		else
		{
			gmMao.vdPlayerPlay(gmMao.getPlayerVec()[intTurn]);
		}

		gmMao.vdChangeTurn();

		cout << "::: Card in Play: " << gmMao.crdLast().strName() << ". :::" << endl;

	}
	while (!(gmMao.blWinCondition(gmMao.getPlayerVec()[intTurn]) && intTurn != gmMao.intGetPlayerTurn()));

	cout << endl << gmMao.getPlayerVec()[intTurn].strGetName() << " wins the game!" << endl << endl;

	system("pause");

	return 0;
}