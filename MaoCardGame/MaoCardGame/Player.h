#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "Card.h"


class Player
{
public:
	Player(string strName = "Max") : strName(strName) {}
	int intGetHandSize();
	string strGetName();
	Card crdPlay();
	void vdDrawCard(Card crdAdd);
	std::vector <Card> vtrGetHand();

private:
	int intCardIndex, intHandSize;
	std::vector <Card> vtrHand;
	string strName;
};