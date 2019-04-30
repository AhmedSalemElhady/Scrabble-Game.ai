#pragma once
#include "AI_Human.hpp"
#include "AI_AI.hpp"
#include "Timer.hpp"
#include "RackOfTiles.hpp"
#include"../SharedClasses/BoardCommunicator.hpp"

class Trainer {
    Board* MyBoard;
    vector<char> AI_Tiles,HumanTiles;
    AI_Human Human;
    AI_AI AI;
    Timer Time;
    RackOfTiles MyRack;
};