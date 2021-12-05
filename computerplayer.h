/*
 * computerplayer.h
 *
 */

#ifndef CHECKERS_COMPUTERPLAYER_H
#define CHECKERS_COMPUTERPLAYER_H

#include "player.h"
#include <chrono>
#include <thread>

using namespace std::this_thread;
using namespace std::chrono;


class computerplayer : public player {
public:
    array<piece*, 12> * Ppieces;
    array<piece*, 12> * Opieces;

    computerplayer(array<piece*, 12> * pieces1, array<piece*, 12> * pieces2);
    virtual void handlePlayer(string &source, string &destination);
};

#endif // CHECKERS_COMPUTERPLAYER_H
