
#pragma once
#include "AI_AI.hpp"

AI_AI::AI_AI()
{
    this->MyBoard = NULL;
    this->AI_Tiles = NULL;
    this->AI_Agent = NULL;
    this->Bag = NULL;
    this->BoardStatus = NULL;
    this->Communicator = NULL;
}
bool AI_AI::SetBag(unordered_map<char, int> *bag)
{
    try
    {
        this->Bag = bag;
        return true;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    return false;
}

bool AI_AI::SetCommunicator(TrainerComm *communicator)
{
    try
    {
        this->Communicator = communicator;
        return true;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    return false;
}

bool AI_AI::SetTiles(vector<char> *tiles)
{
    try
    {
        this->AI_Tiles = tiles;
        return true;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    return false;
}

bool AI_AI::SetBoard(Board *board)
{
    try
    {
        this->MyBoard = board;
        return true;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    return false;
}

Move *AI_AI::DoWork()
{
    Move BestMove;
    return &BestMove;
}

bool AI_AI::SetAgent()
{
    if (this->Bag == NULL || this->BoardStatus == NULL || this->Communicator == NULL || this->AI_Tiles == NULL || this->MyBoard == NULL)
    {
        return false;
    }
}
