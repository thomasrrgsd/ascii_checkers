/*
 * piece.h
 *
 */

#ifndef CHECKERS_PIECE_H_
#define CHECKERS_PIECE_H_

#include <string>
#include "moveObj.h"
#include <list>
#include <iterator>
#include <algorithm>
#include <iostream>

#define RED		(true)
#define BLACK	(false)

using namespace std;

/*
 * Piece contains information about its color, whether its a king,
 * its position and a list of allowable moves by this piece. Because
 * the piece class allocates moveObjs to the heap, these objects must
 * be deleted manually and manually handled for copies and assigns (Ro3).
 *
 */
class piece {
public:
    bool color; // 1 will be Red, 0 will be Black
    bool king;  // True is a king, False is not a king
    string position;

    list <moveObj*> validMoves;     // Every piece has a list containing every possible move location that it can
    // make next. Also tracks king me moves and jump moves.

    piece(bool,string);
	~piece();
	piece(const piece &other);
	piece& operator=(const piece &other);
	
    void printPiece() const;
};

#endif // CHECKERS_PIECE_H_