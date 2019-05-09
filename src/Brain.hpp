#ifndef HEADER_BRAIN
#define HEADER_BRAIN

#include <unordered_map>
#include <vector>
#include "./Definitions.hpp"
#include "./MoveGeneration/Gaddag.h"
#include "./MoveGeneration/LoadGaddag.h"
#include "./MoveGeneration/LoadNode.h"
#include "./TrainerMode/RackOfTiles.hpp"
#include "./TrainerMode/Timer.hpp"
#include <utility>
#include "./Board/Board_and_tiles/Board_and_tiles/Board.h"
#include "./TrainerMode/Trainer.hpp"
#include "../src/ScoreEvaluation/LoadHeuristics.hpp"
#include "../src/ScoreEvaluation/Evaluator.hpp"
#include "../src/ScoreEvaluation/VCValueEvaluator.hpp"

class GameBrain
{
private:
   
	
    static Node *_gaddagInstance;

    static inline Node *createGaddag()
    {
        LoadGaddag gaddagConstructor;
        Node *gaddagRoot = gaddagConstructor.constructGaddag();
        return gaddagRoot;
    }

    AiMode *ourBelovedIntelligentAgent;
    bool IsFinished();
    void communicatorThreadSynch();

public:
    int bagSize;
    bool isFuckinBitchEmpty;
    LoadHeuristics *heuristicsLoader;
    Trainer trainer;
    TimerGUI *T1;
    TimerGUI *T2;
    TimerGUI *T3;
    Move *bestMove;

    void refillTiles(std::vector<char> &, Move *);
    bool turn_TrainerMode;
    bool iWantToReceive;
    PossibleMoves returnOfReceiver;
    vector<char> AI_Tiles, HumanTiles;
    TrainerComm *comm;
    Board *MyBoard;
    RackOfTiles *rackoftiles;
    std::unordered_map<char, int> bag;
    GamePhase game_phase;
	vector<char> getAITiles();
    static Node *__get_gaddag();
    bool readyToSend;
    std::string sendMessage;

    void updateBoard(Move *);
    std::string constructString(Move *, int, int, unsigned long, unsigned long, unsigned long, std::vector<char> &, std::string);
    std::string constructEndGameString(int ourScore,int opponentScore );

    GameBrain(TrainerComm *comm, Board *MyBoard, bool);
    void setTurnOfTrainerMode(bool);
    void updateBag(std::vector<char> &);
    void initialize_computer_vs_computer();
    Move* work_computer_vs_computer();
    void work_human_vs_computer();
    void fillComputerTiles(std::vector<char>&);
};

#endif
