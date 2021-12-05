/*
 * player.cpp
 *
 */

#include "player.h"


player::player(array<piece*, 12> * pieces1, array<piece*, 12> * pieces2) {
	Ppieces = pieces1;
	Opieces = pieces2;
}


void player::handlePlayer(string &source, string &destination) {}