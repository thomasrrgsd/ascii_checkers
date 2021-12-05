/*
 * checkerboard.h
 *
 */
 
#ifndef CHECKERS_CHECKERBOARD_H_
#define CHECKERS_CHECKERBOARD_H_

#include <iostream>
#include <iomanip>
#include <string>
#include <map>
#include "piece.h"
#include "moveObj.h"
#include <algorithm>
#include <list>

using namespace std;


// The checkerboard holds data and functions related to piece position and potential moves
class CheckerBoard {
public:
    map<string, array<int, 2>> xyMap2D;
    map<array<int, 2>, string> xyMap2DInverted;
    map<int, string> xyMap1D;

    piece* spaces[8][8];  // holding a pointer to a piece

    std::list<string> kingList = {"A0","A2","A4","A6","H1","H3","H5","H7"};

    CheckerBoard(array<piece*, 12> & pieces1, array<piece*, 12> & pieces2);					// Default Constructor.
    void PrintBoard();			// Initial board printing.
    void InitializePieceMap();
    piece* CheckSpace(string location);
    bool UpdateSpace(string location, piece* newPiece);
    bool DrawSpace(string location);
    bool IsValidSpace(string position);

    moveObj* checkValidMove(string location, piece* currentPiece);  // before a move can be made, it checks to make sure that move is in the list of valid moves for said piece
    void updateValidMoves();  // updates every piece on the board with their current available moves.
    void probe(int i, int j);

    void kingMoveCheck(moveObj *newMove);


};

#endif	// CHECKERS_CHECKERBOARD_H_