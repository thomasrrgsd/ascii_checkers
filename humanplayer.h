/*
 * humanplayer.h
 *
 */

#ifndef CHECKERS_HUMANPLAYER_H
#define CHECKERS_HUMANPLAYER_H

#include <list>
#include "player.h"
#include <iostream>
#include <array>
#include <algorithm>

using namespace std;


class humanplayer : public player {
public:
    array<piece*, 12> * Ppieces{};
    array<piece*, 12> * Opieces{};

    humanplayer(array<piece*, 12> *pieces1,
                array<piece*, 12> *pieces2);
    virtual void handlePlayer(string &source, string &destination);
private:
    void checkForJumps();
};

#endif // CHECKERS_HUMANPLAYER_H
