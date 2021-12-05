/*
 * boardgame.h
 *
 */

#ifndef BOARDGAME_H_
#define BOARDGAME_H_

/*
 * Abstract base class that describes a boardgame. You can play the game.
 * The number of players playing is specified as an input parameter.
 *
 */
class AbstractBoardGame {
public:
    virtual int PlayGame() = 0;
};

#endif //BOARDGAME_H_