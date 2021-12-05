/*
 * checkerboard.cpp
 *
 * Description: This will contain the board class. This class will consist
 * of functions that print and update the board and player statistics, which
 * is just how many pieces each player has. Will also contain a list of the last
 * 10 moves (5 for red, 5 for black).
 *
 * Cleaned up 12/1/2021
 *
 */

#include "checkerboard.h"


using namespace std;

CheckerBoard::CheckerBoard(array<piece*, 12> & pieces1, array<piece*, 12> & pieces2){

    // Initialize board squares.
    InitializePieceMap();

    // Initialize all red pieces to the top of the board and black pieces to bottom.
    for(int i = 0; i < 12; i++){
        pieces1[i] = new piece(RED, xyMap1D[i]);
        pieces2[i] = new piece(BLACK, xyMap1D[20 + i]);
    }

    for(int j = 0; j < 8; j++){
        for(int i = 0; i < 8; i++){
            spaces[j][i] = nullptr;
        }
    }

    for(int i = 0; i < 12; i++){
        UpdateSpace(pieces1[i]->position, pieces1[i]);
        UpdateSpace(pieces2[i]->position, pieces2[i]);
    }
}

/*
 * This function only runs once to print the checker board. After the initial printing,
 * the board will be updated as needed using cursor move functions. This prevents having
 * to reprint the whole board each time something changes.
 *
 */
// Need to set up a data structure for the board.
// Each space will be have a field that indicates the piece: RO, BO, RK, BK, or SpaceSpace.

void CheckerBoard::PrintBoard(){

    cout << "\n\033[K\n\033[K\t   0      1      2      3      4      5      6      7\n";
    cout << "\t_________________________________________________________\n";
    cout << "\t|      |######|      |######|      |######|      |######|\n";
    cout << "   A\t|      |######|      |######|      |######|      |######|\n";
    cout << "\t|______|######|______|######|______|######|______|######|\n";

    cout << "\t|######|      |######|      |######|      |######|      |\n";
    cout << "   B\t|######|      |######|      |######|      |######|      |\n";
    cout << "\t|######|______|######|______|######|______|######|______|\n";

    cout << "\t|      |######|      |######|      |######|      |######|\n";
    cout << "   C\t|      |######|      |######|      |######|      |######|\n";
    cout << "\t|______|######|______|######|______|######|______|######|\n";

    cout << "\t|######|      |######|      |######|      |######|      |\n";
    cout << "   D\t|######|      |######|      |######|      |######|      |\n";
    cout << "\t|######|______|######|______|######|______|######|______|\n";

    cout << "\t|      |######|      |######|      |######|      |######|\n";
    cout << "   E\t|      |######|      |######|      |######|      |######|\n";
    cout << "\t|______|######|______|######|______|######|______|######|\n";

    cout << "\t|######|      |######|      |######|      |######|      |\n";
    cout << "   F\t|######|      |######|      |######|      |######|      |\n";
    cout << "\t|######|______|######|______|######|______|######|______|\n";

    cout << "\t|      |######|      |######|      |######|      |######|\n";
    cout << "   G\t|      |######|      |######|      |######|      |######|\n";
    cout << "\t|______|######|______|######|______|######|______|######|\n";

    cout << "\t|######|      |######|      |######|      |######|      |\n";
    cout << "   H\t|######|      |######|      |######|      |######|      |\n";
    cout << "\t|######|______|######|______|######|______|######|______|\n";
    cout << "\r\033[26A"; // Reset cursor to top left corner of checkers board.

    // Populates all the spaces with the initial pieces.
    for(auto & it : xyMap2D){
        DrawSpace(it.first);
    }
}

/*
 * Creates a map that relates board position strings, such as "A4" with indexes,
 * such as 0, 1, 2, 3 for 1D. A 2D map is also made to associate position strings
 * with an x and y index, such as {0, 2}.
 */
void CheckerBoard::InitializePieceMap(){

    string tempStr = "A0";
    int index = 0;

    // Initialize 1D map.
    for(int j = 0; j < 8; j++){
        for(int i = index; i < (index + 4); i++){
            xyMap1D[i] = tempStr;
            tempStr[1] = tempStr[1] + 2;
        }
        index = index + 4;
        if(tempStr[1] == '8'){
            tempStr[1] = '1';
        } else{
            tempStr[1] = '0';
        }
        tempStr[0]++;
    }

    tempStr = "A0";
    index = 0;

    // Initialize 2D map.
    for(int j = 0; j < 8; j++){
        for(int i = 0; i < 4; i++){
            xyMap2D[tempStr] = {(tempStr[1] - '0'), j};
            tempStr[1] = tempStr[1] + 2;
        }
        if(tempStr[1] == '8'){
            tempStr[1] = '1';
        } else{
            tempStr[1] = '0';
        }
        tempStr[0]++;
    }

    for (auto & i : xyMap2D) {                   // inverts the 2D map
        xyMap2DInverted[i.second] = i.first;
    }
}


piece* CheckerBoard::CheckSpace(string location){

    int x = 0;
    int y = 0;
    // Must use find member function to determine if location is valid.
    auto it = xyMap2D.find(location);
    if(it == xyMap2D.end()){
        return nullptr;
    }
    else {
        x = (*it).second[0];
        y = (*it).second[1];
        return spaces[x][y];
    }
}

/*
 * Expects an input of a valid black space on checkerboard. Checks
 * that input is in the map list of valid locations.
 * If the conditions are not met, returns false.
 */
bool CheckerBoard::UpdateSpace(string location, piece* newPiece){

    int x = 0;
    int y = 0;


    auto it = xyMap2D.find(location);
    if(it == xyMap2D.end()){
        return false;
    }
    else {
        x = (*it).second[0];
        y = (*it).second[1];
        spaces[x][y] = newPiece;
        return true;
    }
}

moveObj* CheckerBoard::checkValidMove(string location, piece* currentPiece){

    // before a move can be made, it checks
    // to make sure that move is in the list of valid moves for said piece
    if(currentPiece == nullptr){ // There is no piece, or it was an invalid space.
        return nullptr;
    }

    for(auto & validMoveObj : currentPiece->validMoves){
        if(validMoveObj->space == location){
            return validMoveObj;
        }
    }

    return nullptr;
}

/*
 * Updates every piece on the board with their current available moves. Iterates through
 * xy2D map and probes each valid board space (map only contains valid spaces). If the space
 * is not nullptr then there is a piece in that spot and so it must be checked. The valid move
 * list is cleared out for that piece and a new list is generated using the function probe.
 *
 */
void CheckerBoard::updateValidMoves() {

    int x = 0;
    int y = 0;

    for(auto & i : xyMap2D){
        x = i.second[0];    // Gather x and y coordinate from 2D Map.
        y = i.second[1];

        if(spaces[x][y] != nullptr) {


            spaces[x][y]->validMoves.clear();
            // Clear out old move list and free each valid move

            probe(x, y);
            // Creates new move list.

        }
    }
}

/*
 * Description
 *
 * Given array indices i and j, must probe and give valid future moves to said piece.
 * will provide a list of valid moves for a said checkers piece
 *
 */
void CheckerBoard::probe(int i, int j) {


    int x = i;
    int y = j;

    int probeX = i;
    int probeY = j;
    piece* probePiece = spaces[probeX][probeY];
    string positionStr;
    string positionStr2;

    int checkSquare1[4][2] = {{x+1, y+1},{x-1,y+1},{x+1, y-1},{x-1,y-1}};
    int checkSquare2[4][2] = {{x+2, y+2},{x-2,y+2},{x+2, y-2},{x-2,y-2}};
    int startIndex = 0;
    int endIndex = 0;

    // This code determines which indexes to check based on if the piece is a king or pawn.
    if(probePiece->king){   // Check all the indexes.
        startIndex = 0;
        endIndex = 4;
    }
    else if(probePiece->color == RED){  // Check increasing y indexes (RED PIECE).
        startIndex = 0;
        endIndex = 2;
    }
    else{   // Check decreasing y indexes (BLACK PIECE).
        startIndex = 2;
        endIndex = 4;
    }

    for(int k = startIndex; k < endIndex; k++) {
        // For each set of indices check square 1 and possibly square 2.
        x = checkSquare1[k][0];
        y = checkSquare1[k][1];
        array<int, 2> value{x, y};

        // Check that the indices for square 1 are a valid position.
        auto it = xyMap2DInverted.find(value);
        if (it == xyMap2DInverted.end()) {
            continue;   // Move on to next iteration.
        }
        else{
            positionStr = it->second;
        }

        // If nullptr then it is a valid move.
        if(spaces[x][y] == nullptr){           // Added newMove here rather than using a string.

            auto newMove = new moveObj(positionStr, false, " ");

            kingMoveCheck(newMove);  // Will mark it as a move that makes the piece a king
            spaces[probeX][probeY]->validMoves.push_front(newMove);


            continue;   // Move on to next index.
        }
        else {  // There is a piece in this space, we need to check for a jump.
            piece* jumpPiece = spaces[x][y];
            if(probePiece->color != jumpPiece->color){  // Different colors, check for empty space in square 2.
                x = checkSquare2[k][0];
                y = checkSquare2[k][1];
                value[0] = x;
                value[1] = y;
                it = xyMap2DInverted.find(value);
                if (it == xyMap2DInverted.end()) {
                    continue;   // Move on to next iteration.
                }
                else{
                    positionStr2 = it->second;
                }
                if(spaces[x][y] == nullptr){

                    auto * newMove = new moveObj(positionStr2, true, positionStr);
                    // The piece position is not updated automatically.

                    kingMoveCheck(newMove); //will mark it as a move that makes the piece a king

                    spaces[probeX][probeY]->validMoves.push_front(newMove);

                    continue;
                }
            }
        }

    }
}

/* Description
 *
 * Checks to see if a destination is inside the list of moves that are
 * considered to be kinging moves.
 *
 */

void CheckerBoard::kingMoveCheck(moveObj* newMove){

    auto it = find(kingList.begin(), kingList.end(), newMove->space);

    if (it != kingList.end()) {
        newMove->kingMe = true;
    }
}


/* Description:
 *
 * Draws the piece on the board when a move is made.
 * Uses a cursor positioning system to accurately move pieces
 */

bool CheckerBoard::DrawSpace(string location){
    // Check that each string is 2 characters.
    auto it = xyMap2D.find(location);
    if(it == xyMap2D.end()){
        return false;
    }

    int x = (*it).second[0];
    int y = (*it).second[1];

    // Positions the cursor.
    cout << "\033[s";	// Save cursor home position.
    cout << "\033[3B";
    for(int i = 0; i < y; i++){
        cout << "\033[3B";
    }
    cout << "\033[11C";
    for(int i = 0; i < x; i++){
        cout << "\033[7C";
    }

    // Prints the piece, prints space space if no piece.
    if(spaces[x][y] == nullptr){
        cout << "  ";
    }
    else {
        spaces[x][y]->printPiece();
    }

    cout << "\033[u";	// Restore cursor home position.

    return true;
}

/* Description:
 *
 * Checks the valid move list for the position that is passed in
 * Ensures that this move is okay to make when it is passed in.
 *
 */

bool CheckerBoard::IsValidSpace(string position){

    // Search the map.
    auto it = xyMap2D.find(position);
    if (it == xyMap2D.end()) {
        return false;   // Position not found, is not valid.
    }
    else{
        return true;
    }
}