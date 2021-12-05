/*
 * player.h
 *
 */

#ifndef CHECKERS_PLAYER_H
#define CHECKERS_PLAYER_H

#include <list>
#include <array>
#include "piece.h"

#define PLAYER_1	 (1)
#define PLAYER_2	 (2)
#define PLAYER_RED	 (1)
#define PLAYER_BLACK (2)

using namespace std;


class player {
public:
    array<piece*, 12> * Ppieces;
    array<piece*, 12> * Opieces;

    player(array<piece*, 12> * pieces1, array<piece*, 12> * pieces2);
    virtual void handlePlayer(string &source, string &destination);
private:
    void checkForJumps();
};

#endif // CHECKERS_PLAYER_H
