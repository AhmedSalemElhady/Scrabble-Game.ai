#include "./Move.hpp"

#include <string>
#include <iostream>

//NOTE: Feel Free To Add But See Notes in Move.h Before Adding .....
// Initialize
Move::Move()
{
    //EMPTY
}
Move::Move(std::string word, bool horizontal, Position position, int usedTiles)
{
    this->word = word;
    this->horizontal = horizontal;
    this->startPosition = position;
    this->moveUsedTiles = (char)usedTiles;
}

// Setting Move Score.
void Move::setScore(int score)
{
    this->moveScore = score;
}

std::string Move::moveServerFormat()
{

    return "   E";
} // Format the move for server's use.
std::string Move::moveGUIFormat() // if Needed.
{

    return "   E";
} // For GUI use.