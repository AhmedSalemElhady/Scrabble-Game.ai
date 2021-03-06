#include "AI_Human.hpp"
#include <time.h>

PossibleMoves getMoveConsole(Move *retrunableMove)
{
    std::cout << "enter your move:\n";
    int startCol, endCol, isHorizontal;
    std::cin >> startCol;
    if (startCol == -1)
    {
        retrunableMove->moveScore = -999999;
        return PASS;
    }
    else if (startCol == -2)
    {
        char x;
        std::cin >> x;
        retrunableMove->word = " ";
        retrunableMove->word[0] = x;
        return EXCHANGE;
    }

    std::cin >> endCol >> isHorizontal;

    // read el move nafsaha: el tiles elly msh mab3otaly
    std::cin.ignore();
    std::string move;
    std::cin >> move; // law#alboard -- 0:26,  small: notblank, capital: blank

    retrunableMove->horizontal = (isHorizontal == 1) ? true : false;
    retrunableMove->startPosition.COL = endCol;
    retrunableMove->startPosition.ROW = startCol;
    BoardToGrammer *b2g = new BoardToGrammer();
    retrunableMove->setScore(b2g->calculateScore(move, startCol, endCol, retrunableMove->horizontal));
    retrunableMove->word = move;
    return PLAY;
}

AI_Human::AI_Human()
{
    this->MyBoard = NULL;
    this->HumanTiles = NULL;
    this->AI_Agent = NULL;
    this->Bag = NULL;
    this->BoardStatus = NULL;
    this->Communicator = NULL;
}

bool AI_Human::SetBag(unordered_map<char, int> *bag)
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

bool AI_Human::SetCommunicator(TrainerComm *communicator)
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

bool AI_Human::SetTiles(vector<char> *tiles)
{
    try
    {
        this->HumanTiles = tiles;
        this->AI_Agent->setTiles(*tiles);
        return true;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    return false;
}

bool AI_Human::SetAgent(AiMode *AI_Agent)
{
    AI_Agent->setBagPointer(this->Bag);
    AI_Agent->setBoardToGrammar(b2g);
    this->AI_Agent = AI_Agent;
    return true;
}

bool AI_Human::SetBoard(Board *board)
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

void AI_Human::exchange(std::vector<char> *tiles, char tileToExchange, char newTile)
{
    for (int i = 0; i < tiles->size(); ++i)
    {
        if ((*tiles)[i] == tileToExchange)
        {
            (*tiles)[i] = newTile;
        }
    }
}

void AI_Human::exchangeTiles(std::vector<char> *tiles, char tileToExchange)
{
    // check if bag is empty:
    bool allZeroes = true;
    for (int c = 'a'; c <= 'z'; ++c)
    {
        if ((*this->Bag)[(char)c] > 0)
        {
            allZeroes = false;
            break;
        }
    }
    if (allZeroes == true)
    { // * check for space:
        if ((*this->Bag)[' '] > 0)
            allZeroes = false;
    }

    // *now check on flag:
    if (allZeroes == false)
    { //* i can exchaneg

        do
        {
            srand(time(NULL));
            int randChar = rand() % 27;
            if (randChar > 25)
            {
                if ((*this->Bag)[' '] > 0)
                {
                    --(*this->Bag)[' '];
                    ++(*this->Bag)[tileToExchange];
                    this->exchange(tiles, tileToExchange, ' ');
                    break;
                }
            }
            else
            {
                if ((*this->Bag)[randChar + 'a'] > 0)
                {
                    --(*this->Bag)[randChar];
                    ++(*this->Bag)[tileToExchange];
                    this->exchange(tiles, tileToExchange, randChar);
                }
            }
        } while (true);
    }
    else
    {
        return; //* can NEVER exhcange
    }
}

Move *AI_Human::DoWork(bool isFuckinBitchEmpty, int bagSize, LoadHeuristics *loader)
{
    Move *BestMove = nullptr;
    Move *PlayerMove = new Move();
    PossibleMoves ret = DUMMY;

    while (ret == DUMMY) // busy wait until a play is played
    {
        // TODO: replace with communicator:
        ret = this->Communicator->SendAndReceiveGUI("dummyText", false, true);
        // ret = getMoveConsole(PlayerMove);
    }

    if (ret == PLAY)
    {
        PlayerMove = this->Communicator->MovePtr;
        BestMove = this->AI_Agent->doWork(isFuckinBitchEmpty, bagSize - PlayerMove->moveUsedTiles, loader);
        if (BestMove == NULL)
        {
            this->messageToHuman = "Excellent !I Couldn't do better";
        }
        else
        {

            if (BestMove->moveScore > PlayerMove->moveScore)
            {
                this->messageToHuman = "Bravo! But You Could Do Better..";
            }

            if (BestMove->moveScore < PlayerMove->moveScore)
            {
                this->messageToHuman = "Marvellous! your move is better than what I thought";
            }

            if (BestMove->moveScore == PlayerMove->moveScore)
            {
                this->messageToHuman = "Excellent !I Couldn't do better";
            }
        }

        return PlayerMove;
    }
    else if (ret == PASS)
    {
        BestMove = this->AI_Agent->doWork(isFuckinBitchEmpty, bagSize, loader);
        if (BestMove == NULL)
        {
            this->messageToHuman = "Excellent !I Couldn't do better";
        }
        else
        {

            if (BestMove->moveScore > PlayerMove->moveScore)
            {
                this->messageToHuman = "Bravo! But You Could Do Better..";
            }

            if (BestMove->moveScore < PlayerMove->moveScore)
            {
                this->messageToHuman = "Marvellous! your move is better than what I thought";
            }

            if (BestMove->moveScore == PlayerMove->moveScore)
            {
                this->messageToHuman = "Excellent !I Couldn't do better";
            }
        }
        return NULL;
    }
    else
    {
        // *then exchange:
        this->exchangeTiles(this->HumanTiles, this->Communicator->ExchangedTiles[0]);
        return NULL;
    }

    return PlayerMove;
}
