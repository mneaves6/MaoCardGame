#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <random>
#include "Player.h"
#include "Card.h"
#include "Game.h"


class Game
{
public:
	Game(int intPlayerTurn = 0, bool blReverse = false, int intDrawTwo = 0) : intPlayerTurn(0), blReverse(false), intDrawTwo(0) {}
	bool blCheckLegalMove(Card crdX);
	void vdShuffle();
	void vdDeal();
	Card crdLast();
	bool blWinCondition(Player plyY);
	void vdCardFunction(Card crdX);
	void vdPlayerPlay(Player& plyY);
	std::vector <Player> getPlayerVec();
	void vdAddPlayer(Player plyY);
	bool blGetReverse();
	int intFindCardIndex(Player& plyY, Card crdX);
	int intGetPlayerTurn();
	void vdChangeTurn();
	void vdNoCardsinHand(Player& plyY);

private:
	int intDrawTwo;
	int intPlayerTurn;
	std::vector <Card> vtrDiscard;
	std::vector <Card> vtrDeck;
	std::vector <Player> vtrPlayers;
	bool blReverse;
};