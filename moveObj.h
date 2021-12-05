/*
 * moveObj.h
 *
 */

#ifndef CHECKERS_MOVEOBJ_H
#define CHECKERS_MOVEOBJ_H
#include <string>

using namespace std;


class moveObj {
public:
    string space; 		// Where the actual index is.
    string pieceJumped; // If it is a jump move, what piece location is jumped.
    bool isJump;  		// Is this a jump move?
    bool kingMe;        // Is this a move that will king the piece that is being moved.
	
	moveObj(string, bool ,string);
};

#endif // CHECKERS_MOVEOBJ_H
