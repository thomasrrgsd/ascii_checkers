/*
 * checkers.cpp
 *
 */

#include "checkers.h"

using namespace std;


Checkers::Checkers(int numPlayers){

	gameType = numPlayers;
	
    // Set up the checkerboard. 
    board = new CheckerBoard(pieces1, pieces2);

    numPieces1 = 12;    // Everybody starts with 12 pieces each.
    numPieces2 = 12;
	
	noMoves1 = false;
	noMoves2 = false;

	// Allocate player objects. Assign whether computer or human based on numPlayers
	// passed in.
    switch(numPlayers){ // Here we allocate player objects.
        case CPU_VS_CPU:
            player1 = new computerplayer(&pieces1, &pieces2); 	// Computer player
            player2 = new computerplayer(&pieces2, &pieces1); 	// Computer player
            break;
        case CPU_VS_HUMAN:
            player1 = new humanplayer(&pieces1, &pieces2); 		// Human player
            player2 = new computerplayer(&pieces2, &pieces1); 	// Computer player
            break;
        case HUMAN_VS_HUMAN:
            player1 = new humanplayer(&pieces1, &pieces2); 		// Human player
            player2 = new humanplayer(&pieces2, &pieces1); 		// Human player
            break;
        default:
            break;
    }
}

/*
 * When playing the game we have to do certain things:
 * 	- Get player input
 * 	- Check that the move is legal
 *  - Move pieces and update board
 *	- Update player stats
 *	- Add move to previous list
 *	- Print previous 10 moves
 *	- If no moves or 0 pieces then end game
 *	- Get next move, repeat.
 *
 */
int Checkers::PlayGame(){  //inheritance of the board game

    // Code before the while loop is used to set up game board.

    cout << "\033[2J" << "\033[H";	// Clear the screen

    piece* tempPiece;
    int whoWon = 0;
	string space1 = "  ";	// The "from" space
	string space2 = "  ";	// The "to" space
	string thisMove;

	board->PrintBoard();
    UpdatePlayerStats();
    UpdatePreviousMoves("  " , "  ");   // Game begin indicator.

   while(!(whoWon = CheckGameOver())){  // while not game over

        UpdatePlayerStats();
        board->updateValidMoves();

		if(IsThereNoMove()){
			whoWon = CheckGameOver();
			break;
		}
		if(gameType == CPU_VS_HUMAN || gameType == HUMAN_VS_HUMAN){
			PrintPlayer(PLAYER_1);
		}
        player1->handlePlayer(space1, space2);
        if(space1 == "quit" || space2 == "quit"){
            break;
        }
        if(!HandleCurrentMove(space1, space2)){
            UpdatePreviousMoves(space1, space2, PLAYER_1);
        }
        else{
            UpdatePreviousMoves("00" , "00");   // Indicates invalid move.
        }

		UpdatePlayerStats();
        board->updateValidMoves();
        
		if(IsThereNoMove()){
			whoWon = CheckGameOver();
			break;
		}
		if(gameType == HUMAN_VS_HUMAN){
			PrintPlayer(PLAYER_2);
		}
		player2->handlePlayer(space1, space2);
		if(space1 == "quit" || space2 == "quit"){
            break;
        }
		if(!HandleCurrentMove(space1, space2)){
           UpdatePreviousMoves(space1, space2, PLAYER_2);
		}
		else{
           UpdatePreviousMoves("00" , "00");   // Indicates invalid move.
		}
   }

    WinnerTieDisplay(whoWon);
    return 0;
}

/*
 * Return 0: To and from space were valid, space had a piece on it, move was on valid move list.
 * Return 1: Move was not on valid move list.
 * Return 2: Space to move from was empty (no piece to move).
 * Return 3: Given invalid space label (e.g. M4, A1, B0).
 *
 */
int Checkers::HandleCurrentMove(string from, string to){

    piece* tempPiece;

    piece* jumpedPiece;

    moveObj* validMove;

    if(board->IsValidSpace(from) && board->IsValidSpace(to)){
        tempPiece = board->CheckSpace(from);  // CheckSpace returns a piece.
        if(tempPiece != nullptr){
            if((validMove = board->checkValidMove(to, tempPiece))){   // Need to add here to check for king and jump.
                board->UpdateSpace(to, tempPiece);
                board->UpdateSpace(from, nullptr);
                if(validMove->kingMe){
                    tempPiece->king = true;
                }
                if(validMove->isJump){  // If true, we must update the space that is jumped.
                    jumpedPiece = board->CheckSpace(validMove->pieceJumped);  // CheckSpace returns a piece.
                    board->UpdateSpace(validMove->pieceJumped, nullptr);
                    if(tempPiece->color == RED){
                        numPieces2--;
                    } else{
                        numPieces1--;
                    }
                    board->DrawSpace(validMove->pieceJumped);

                    jumpedPiece->position = "  ";  // changes its position to nothing
                    // delete the valid moves for this piece
                    jumpedPiece->validMoves.erase(jumpedPiece->validMoves.begin(), jumpedPiece->validMoves.end());

                }
                board->DrawSpace(to);
                board->DrawSpace(from);

                tempPiece->position = to;

                return 0;
            }
            else{
                return 1;
            }
        }
        else{
            return 2;
        }
    }
    else{
        return 3;
    }
}


/*
 * If either player has no pieces left the game is over.
 * If either player cannot make a move then that player loses.
 * If both players cannot make a move then the game ends in a tie.
 *
 * Return 0: Game not over.
 * Return 1: Player 1 wins.
 * Return 2: Player 2 wins.
 * Return 3: It is a tie.
 *
 */
int Checkers::CheckGameOver(){

	// Player 1 has no pieces, or player 1 has no moves and player 2 has moves.
    if((numPieces1 == 0) || (noMoves1 && !noMoves2)){
        return 2;
    }
	// Player 2 has no pieces, or player 2 has no moves and player 1 has moves.
    else if((numPieces2 == 0) || (!noMoves1 && noMoves2)){
        return 1;
    }
	// Its a tie. Neither player has any moves.
	else if(noMoves1 && noMoves2){
		return 3;
	}
	return 0;
}

/*
 * Return true if a player, or both players have no moves.
 *
 */
bool Checkers::IsThereNoMove(){
	
	noMoves1 = true;
	noMoves2 = true;
	
	// Check player 1 pieces for a single move.
	for(auto checkPiece : pieces1){
		if(!checkPiece->validMoves.empty()){
			noMoves1 = false;
			break;
		}
	}
	
	// Check player 2 pieces for a single move.
	for(auto checkPiece : pieces2){
		if(!checkPiece->validMoves.empty()){
			noMoves2 = false;
			break;
		}
	}
	
	return (noMoves1 || noMoves2);
}

/*
 * If handed "00", "00" then prints invalid move. If handed "  ", "  " then
 * print beginning of game. Other wise print the move and the player color
 * associated with the move.
 *
 */
void Checkers::UpdatePreviousMoves(string strFrom, string strTo, int whichPlayer){

    string thisMove = strFrom + " --> " + strTo;
    if(thisMove == "00 --> 00"){    // Invalid move was attempted.
        thisMove = "Invalid Move";
    }
    else if(thisMove == "   -->   "){
        thisMove = "Begin Game  ";     // Game just started
    } else {
		switch(whichPlayer){
			case PLAYER_1:
				thisMove += ", Red  ";
				break;
			case PLAYER_2:
				thisMove += ", Black";
				break;
			default:
				thisMove += "   ";
				break;
		}
	}

    int numMoves = 0;

    prevMoves.push_front(thisMove);

    if(prevMoves.size() > 10){	// We only display 10 to prevent having
        prevMoves.pop_back();	// a massive list on the screen.
    }

	cout << "\033[s";	// Save cursor home position.
	cout << "\r\033[12B\033[68C" << "Previous 10 Moves: ";

	if(prevMoves.empty()){	// If list is empty we are done.
		cout << "\033[u";
		return;
	}

	for(auto & prevMove : prevMoves){	// List not empty, print it out.
		numMoves++;
		cout << "\r\033[1B\033[68C";
		if(numMoves != 10) {
			cout << " ";
		}
		cout << numMoves << ": " << prevMove;
	}

	cout << "\033[u";	// Restore cursor to home position.
}

/*
 * Uses numPieces1 and numPieces2 to update the number of pieces 
 * left on the board.
 *
 */
void Checkers::UpdatePlayerStats() const{
	
	cout << "\033[s"; // Save cursor home position
	
	cout << "\r\033[3B\033[68C" << "Player 1 / Red Player: " << "\r\n\033[68C"
			<< setw(2) << setfill('0') << numPieces1 << " Pieces";
	cout << "\r\n\r\n\033[68C" << "Player 2 / Black Player: " << "\r\n\033[68C"
			<< setw(2) << setfill('0') << numPieces2 << " Pieces";

	cout << "\033[u";	// Restore cursor to home position.
}

/*
 * Passes in 1 for player 1 winning, 2 for player 2 winning and
 * 3 for a tie.
 *
 */
void Checkers::WinnerTieDisplay(int whoWon){

    char throwAway[25];
    throwAway[0] = 'p';
    cout << "\033[2J" << "\033[H";	// Clear the screen
	cout << "\033[s";
    cout << "\n\n";
    switch(whoWon) {
        case 1:
            // Draw player 1 win screen.

            cout << "      ___           ___          _____       " << endl;
            cout << "     /  /\\         /  /\\        /  /::\\      " << endl;
            cout << "    /  /::\\       /  /:/_      /  /:/\\:\\     " << endl;
            cout << "   /  /:/\\:\\     /  /:/ /\\    /  /:/  \\:\\    " << endl;
            cout << "  /  /:/~/:/    /  /:/ /:/_  /__/:/ \\__\\:|   " << endl;
            cout << " /__/:/ /:/___ /__/:/ /:/ /\\ \\  \\:\\ /  /:/   " << endl;
            cout << " \\  \\:\\/:::::/ \\  \\:\\/:/ /:/  \\  \\:\\  /:/    " << endl;
            cout << "  \\  \\::/~~~~   \\  \\::/ /:/    \\  \\:\\/:/     " << endl;
            cout << "   \\  \\:\\        \\  \\:\\/:/      \\  \\::/      " << endl;
            cout << "    \\  \\:\\        \\  \\::/        \\__\\/       " << endl;
            cout << "     \\__\\/         \\__\\/                     " << endl;
            cout << "      ___                       ___                       ___           ___        " << endl;
            cout << "     /  /\\                     /  /\\          ___        /  /\\         /  /\\       " << endl;
            cout << "    /  /::\\                   /  /::\\        /__/|      /  /:/_       /  /::\\      " << endl;
            cout << "   /  /:/\\:\\  ___     ___    /  /:/\\:\\      |  |:|     /  /:/ /\\     /  /:/\\:\\     " << endl;
            cout << "  /  /:/~/:/ /__/\\   /  /\\  /  /:/~/::\\     |  |:|    /  /:/ /:/_   /  /:/~/:/     " << endl;
            cout << " /__/:/ /:/  \\  \\:\\ /  /:/ /__/:/ /:/\\:\\  __|__|:|   /__/:/ /:/ /\\ /__/:/ /:/___   " << endl;
            cout << " \\  \\:\\/:/    \\  \\:\\  /:/  \\  \\:\\/:/__\\/ /__/::::\\   \\  \\:\\/:/ /:/ \\  \\:\\/:::::/   " << endl;
            cout << "  \\  \\::/      \\  \\:\\/:/    \\  \\::/         ~\\~~\\:\\   \\  \\::/ /:/   \\  \\::/~~~~    " << endl;
            cout << "   \\  \\:\\       \\  \\::/      \\  \\:\\           \\  \\:\\   \\  \\:\\/:/     \\  \\:\\        " << endl;
            cout << "    \\  \\:\\       \\__\\/        \\  \\:\\           \\__\\/    \\  \\::/       \\  \\:\\       " << endl;
            cout << "     \\__\\/                     \\__\\/                     \\__\\/         \\__\\/       " << endl;
            cout << "      ___                       ___           ___      " << endl;
            cout << "     /__/\\        ___          /__/\\         /  /\\     " << endl;
            cout << "    _\\_ \\:\\      /  /\\         \\  \\:\\       /  /:/_    " << endl;
            cout << "   /__/\\ \\:\\    /  /:/          \\  \\:\\     /  /:/ /\\   " << endl;
            cout << "  _\\_ \\:\\ \\:\\  /__/::\\      _____\\__\\:\\   /  /:/ /::\\  " << endl;
            cout << " /__/\\ \\:\\ \\:\\ \\__\\/\\:\\__  /__/::::::::\\ /__/:/ /:/\\:\\ " << endl;
            cout << " \\  \\:\\ \\:\\/:/    \\  \\:\\/\\ \\  \\:\\~~\\~~\\/ \\  \\:\\/:/~/:/ " << endl;
            cout << "  \\  \\:\\ \\::/      \\__\\::/  \\  \\:\\  ~~~   \\  \\::/ /:/  " << endl;
            cout << "   \\  \\:\\/:/       /__/:/    \\  \\:\\        \\__\\/ /:/   " << endl;
            cout << "    \\  \\::/        \\__\\/      \\  \\:\\         /__/:/    " << endl;
            cout << "     \\__\\/                     \\__\\/         \\__\\/   " << endl;
            break;
        case 2:
            // Draw player 2 win screen.

            cout << "                                  ___           ___           ___          " << endl;
            cout << "     _____                       /  /\\         /  /\\         /__/|         " << endl;
            cout << "    /  /::\\                     /  /::\\       /  /:/        |  |:|         " << endl;
            cout << "   /  /:/\\:\\    ___     ___    /  /:/\\:\\     /  /:/         |  |:|         " << endl;
            cout << "  /  /:/~/::\\  /__/\\   /  /\\  /  /:/~/::\\   /  /:/  ___   __|  |:|         " << endl;
            cout << " /__/:/ /:/\\:| \\  \\:\\ /  /:/ /__/:/ /:/\\:\\ /__/:/  /  /\\ /__/\\_|:|____     " << endl;
            cout << " \\  \\:\\/:/~/:/  \\  \\:\\  /:/  \\  \\:\\/:/__\\/ \\  \\:\\ /  /:/ \\  \\:\\/:::::/     " << endl;
            cout << "  \\  \\::/ /:/    \\  \\:\\/:/    \\  \\::/       \\  \\:\\  /:/   \\  \\::/~~~~      " << endl;
            cout << "   \\  \\:\\/:/      \\  \\::/      \\  \\:\\        \\  \\:\\/:/     \\  \\:\\          " << endl;
            cout << "    \\  \\::/        \\__\\/        \\  \\:\\        \\  \\::/       \\  \\:\\         " << endl;
            cout << "     \\__\\/                       \\__\\/         \\__\\/         \\__\\/         " << endl;
            cout << "      ___                       ___                       ___           ___        " << endl;
            cout << "     /  /\\                     /  /\\          ___        /  /\\         /  /\\       " << endl;
            cout << "    /  /::\\                   /  /::\\        /__/|      /  /:/_       /  /::\\      " << endl;
            cout << "   /  /:/\\:\\  ___     ___    /  /:/\\:\\      |  |:|     /  /:/ /\\     /  /:/\\:\\     " << endl;
            cout << "  /  /:/~/:/ /__/\\   /  /\\  /  /:/~/::\\     |  |:|    /  /:/ /:/_   /  /:/~/:/     " << endl;
            cout << " /__/:/ /:/  \\  \\:\\ /  /:/ /__/:/ /:/\\:\\  __|__|:|   /__/:/ /:/ /\\ /__/:/ /:/___   " << endl;
            cout << " \\  \\:\\/:/    \\  \\:\\  /:/  \\  \\:\\/:/__\\/ /__/::::\\   \\  \\:\\/:/ /:/ \\  \\:\\/:::::/   " << endl;
            cout << "  \\  \\::/      \\  \\:\\/:/    \\  \\::/         ~\\~~\\:\\   \\  \\::/ /:/   \\  \\::/~~~~    " << endl;
            cout << "   \\  \\:\\       \\  \\::/      \\  \\:\\           \\  \\:\\   \\  \\:\\/:/     \\  \\:\\        " << endl;
            cout << "    \\  \\:\\       \\__\\/        \\  \\:\\           \\__\\/    \\  \\::/       \\  \\:\\       " << endl;
            cout << "     \\__\\/                     \\__\\/                     \\__\\/         \\__\\/       " << endl;
            cout << "      ___                       ___           ___      " << endl;
            cout << "     /__/\\        ___          /__/\\         /  /\\     " << endl;
            cout << "    _\\_ \\:\\      /  /\\         \\  \\:\\       /  /:/_    " << endl;
            cout << "   /__/\\ \\:\\    /  /:/          \\  \\:\\     /  /:/ /\\   " << endl;
            cout << "  _\\_ \\:\\ \\:\\  /__/::\\      _____\\__\\:\\   /  /:/ /::\\  " << endl;
            cout << " /__/\\ \\:\\ \\:\\ \\__\\/\\:\\__  /__/::::::::\\ /__/:/ /:/\\:\\ " << endl;
            cout << " \\  \\:\\ \\:\\/:/    \\  \\:\\/\\ \\  \\:\\~~\\~~\\/ \\  \\:\\/:/~/:/ " << endl;
            cout << "  \\  \\:\\ \\::/      \\__\\::/  \\  \\:\\  ~~~   \\  \\::/ /:/  " << endl;
            cout << "   \\  \\:\\/:/       /__/:/    \\  \\:\\        \\__\\/ /:/   " << endl;
            cout << "    \\  \\::/        \\__\\/      \\  \\:\\         /__/:/    " << endl;
            cout << "     \\__\\/                     \\__\\/         \\__\\/   " << endl;
            break;
        case 3:
            // Draw game tied screen. AKA Stalemate
            cout << " ____    __             ___                                __             " << endl;
            cout << "/\\  _`\\ /\\ \\__         /\\_ \\                              /\\ \\__          " << endl;
            cout << "\\ \\,\\L\\_\\ \\ ,_\\    __  \\//\\ \\      __    ___ ___      __  \\ \\ ,_\\    __   " << endl;
            cout << " \\/_\\__ \\\\ \\ \\/  /'__`\\  \\ \\ \\   /'__`\\/' __` __`\\  /'__`\\ \\ \\ \\/  /'__`\\ " << endl;
            cout << "   /\\ \\L\\ \\ \\ \\_/\\ \\L\\.\\_ \\_\\ \\_/\\  __//\\ \\/\\ \\/\\ \\/\\ \\L\\.\\_\\ \\ \\_/\\  __/ " << endl;
            cout << "   \\ `\\____\\ \\__\\ \\__/.\\_\\/\\____\\ \\____\\ \\_\\ \\_\\ \\_\\ \\__/.\\_\\\\ \\__\\ \\____\\" << endl;
            cout << "    \\/_____/\\/__/\\/__/\\/_/\\/____/\\/____/\\/_/\\/_/\\/_/\\/__/\\/_/ \\/__/\\/____/" << endl;
            break;
        default:
            break;
    }
    cout << "\n\n Hit enter to return to main menu...";
    cin.getline(throwAway, 25);
    cin.getline(throwAway, 25);
	cout << "\033[u";
}

void Checkers::PrintPlayer(int playerNum){
	
	cout << "\033[s";
	cout << "\r\033[28B\033[K";
	
	switch(playerNum){
		case PLAYER_1:
			cout << "\t\tRed Player  ";
			break;
		case PLAYER_2:
			cout << "\t\tBlack Player";
			break;
		default:
			cout << "\t\t            ";
			break;
	}
	
	cout << "\033[u";
}

/*
 * Destructor
 *
 */
Checkers::~Checkers() {
	
    for (array<piece*, 12>::iterator it = pieces1.begin(); (it) != pieces1.end(); it++) {
        delete (*it);
    }
    for (array<piece*, 12>::iterator it = pieces2.begin(); (it) != pieces2.end(); it++) {
        delete (*it);
    }

    delete player1;
    delete player2;
    delete board;
}

/*
 * Copy Constructor
 *
 */
Checkers::Checkers(const Checkers &other) {
	
	// None pointer type variables handled automatically.
	
	// Creates a new checkerboard and allocates the default pieces.
	board = new CheckerBoard(pieces1, pieces2);
	// All the board needs is to update its spaces. Nothing else changes.
	
	// Update our pieces to match other pieces, relies on piece assignment operator.
	for(int i = 0; i < 12; i++){
		*(pieces1[i]) = *(other.pieces1[i]);
		*(pieces2[i]) = *(other.pieces2[i]);
	}
	// Now our pieces lists are the same as the other pieces, except that they are
	// on the incorrect spaces. Though their positions are correct. So we just have
	// to run through and update the board spaces.
	
	// Clear out the spaces.
	for(int j = 0; j < 8; j++){
        for(int i = 0; i < 8; i++){
            board->spaces[j][i] = nullptr;
        }
    }

	// Re-initialize the board spaces to correctly have the updated pieces in right positions.
    for(int i = 0; i < 12; i++){
        board->UpdateSpace(pieces1[i]->position, pieces1[i]);
        board->UpdateSpace(pieces2[i]->position, pieces2[i]);
    }
	// When the initial draw is called, the board should look exactly like the board it was copied from.
	

	// Allocate player objects. Assign whether computer or human based on numPlayers
	// passed in. The player object has pointers to the newly allocated pieces.
    switch(other.gameType){
        case CPU_VS_CPU:
            player1 = new computerplayer(&pieces1, &pieces2); 	// Computer player
            player2 = new computerplayer(&pieces2, &pieces1); 	// Computer player
            break;
        case CPU_VS_HUMAN:
            player1 = new humanplayer(&pieces1, &pieces2); 		// Human player
            player2 = new computerplayer(&pieces2, &pieces1); 	// Computer player
            break;
        case HUMAN_VS_HUMAN:
            player1 = new humanplayer(&pieces1, &pieces2); 		// Human player
            player2 = new humanplayer(&pieces2, &pieces1); 		// Human player
            break;
        default:
            break;
    }
	
	// Relies on list assignment operator.
	prevMoves = other.prevMoves;
}

/*
 * Assignment operator
 * 1. Check that its not trying to assign from itself.
 * 2. Delete all previous objects.
 * 3. Follow the constructors logic to re-initialize to other checkers game.
 *
 */
Checkers& Checkers::operator=(const Checkers &other) {
    
	if (&other == this) { // If this, then return this.
        return *this;
    }
	
    for (array<piece*, 12>::iterator it = pieces1.begin(); (it) != pieces1.end(); it++) {
        delete (*it);
    }
    for (array<piece*, 12>::iterator it = pieces2.begin(); (it) != pieces2.end(); it++) {
        delete (*it);
    }

    delete player1;
    delete player2;
    delete board;

	// None pointer type variables handled automatically.
	
	// Creates a new checkerboard and allocates the default pieces.
	board = new CheckerBoard(pieces1, pieces2);
	// All the board needs is to update its spaces. Nothing else changes.
	
	// Update our pieces to match other pieces, relies on piece assignment operator.
	for(int i = 0; i < 12; i++){
		*(pieces1[i]) = *(other.pieces1[i]);
		*(pieces2[i]) = *(other.pieces2[i]);
	}
	// Now our pieces lists are the same as the other pieces, except that they are
	// on the incorrect spaces. Though their positions are correct. So we just have
	// to run through and update the board spaces.
	
	// Clear out the spaces.
	for(int j = 0; j < 8; j++){
        for(int i = 0; i < 8; i++){
            board->spaces[j][i] = nullptr;
        }
    }

	// Re-initialize the board spaces to correctly have the updated pieces in right positions.
    for(int i = 0; i < 12; i++){
        board->UpdateSpace(pieces1[i]->position, pieces1[i]);
        board->UpdateSpace(pieces2[i]->position, pieces2[i]);
    }
	// When the initial draw is called, the board should look exactly like the board it was copied from.
	

	// Allocate player objects. Assign whether computer or human based on numPlayers
	// passed in. The player object has pointers to the newly allocated pieces.
    switch(other.gameType){
        case CPU_VS_CPU:
            player1 = new computerplayer(&pieces1, &pieces2); 	// Computer player
            player2 = new computerplayer(&pieces2, &pieces1); 	// Computer player
            break;
        case CPU_VS_HUMAN:
            player1 = new humanplayer(&pieces1, &pieces2); 		// Human player
            player2 = new computerplayer(&pieces2, &pieces1); 	// Computer player
            break;
        case HUMAN_VS_HUMAN:
            player1 = new humanplayer(&pieces1, &pieces2); 		// Human player
            player2 = new humanplayer(&pieces2, &pieces1); 		// Human player
            break;
        default:
            break;
    }
	
	// Relies on list assignment operator.
	prevMoves = other.prevMoves;
	
	
    return *this;
}


