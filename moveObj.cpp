/*
 * moveObj.cpp
 *
 */

#include "moveObj.h"

using namespace std;

/*
 * Constructor
 *
 */
moveObj::moveObj(string sp, bool j = false, string pj = " "){

    space = sp;
    isJump = j;
    pieceJumped = pj;
    kingMe = false;
}