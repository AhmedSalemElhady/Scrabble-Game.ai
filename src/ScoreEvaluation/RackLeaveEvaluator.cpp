// #pragma once
// #include "Evaluator.hpp"

// double Evaluator::equity(std::vector<char> &Rack, bool isEmptyBoard, Move &move) const
// {
//     return CalculateRackLeave(Rack, move);
// }

// double Evaluator::CalculateRackLeave(std::vector<char> &Rack, Move &move) const
// {

//     return leaveValue(); //(position.currentPlayer().rack() - move).tiles()
// }

// double ScorePlusLeaveEvaluator::leaveValue(const LetterString &leave) const
// {
//     LetterString alphabetized = String::alphabetize(leave);

//     if (QUACKLE_STRATEGY_PARAMETERS->hasSuperleaves() && QUACKLE_STRATEGY_PARAMETERS->superleave(alphabetized))
//         return QUACKLE_STRATEGY_PARAMETERS->superleave(alphabetized);

//     double value = 0;

//     if (!leave.empty())
//     {
//         double synergy = 0;
//         LetterString uniqleave;

//         if (QUACKLE_STRATEGY_PARAMETERS->hasWorths())
//             for (const auto &leaveIt : leave)
//                 value += QUACKLE_STRATEGY_PARAMETERS->tileWorth(leaveIt);

//         if (QUACKLE_STRATEGY_PARAMETERS->hasSyn2())
//             for (unsigned int i = 0; i < alphabetized.length() - 1; ++i)
//                 if (alphabetized[i] == alphabetized[i + 1])
//                     value += QUACKLE_STRATEGY_PARAMETERS->syn2(alphabetized[i], alphabetized[i]);

//         uniqleave += alphabetized[0];
//         for (unsigned int i = 1; i < alphabetized.length(); ++i)
//             if (uniqleave[uniqleave.length() - 1] != alphabetized[i])
//                 uniqleave += alphabetized[i];

//         if (uniqleave.length() >= 2 && QUACKLE_STRATEGY_PARAMETERS->hasSyn2())
//         {
//             for (unsigned int i = 0; i < uniqleave.length() - 1; ++i)
//                 for (unsigned int j = i + 1; j < uniqleave.length(); ++j)
//                     synergy += QUACKLE_STRATEGY_PARAMETERS->syn2(uniqleave[i], uniqleave[j]);

//             // TODO handle the Q

//             bool holding_bad_tile = false;
//             for (unsigned int i = 0; i < uniqleave.length(); ++i)
//             {
//                 if (QUACKLE_STRATEGY_PARAMETERS->tileWorth(uniqleave[i]) < -5.5)
//                 {
//                     holding_bad_tile = true;
//                 }
//             }

//             if ((synergy > 3.0) && !holding_bad_tile)
//             {
//                 synergy += 1.5 * (synergy - 3.0);
//             }

//             value += synergy;
//         }
//     }

//     int vowels = 0;
//     int cons = 0;

//     for (const auto &leaveIt : leave)
//     {
//         if (leaveIt != QUACKLE_BLANK_MARK)
//         {
//             if (QUACKLE_ALPHABET_PARAMETERS->isVowel(leaveIt))
//                 vowels++;
//             else
//                 cons++;
//         }
//     }

//     const float vcvalues[8][8] =
//         {
//             {0.0, 0.0, -1.0, -2.5, -5.0, -8.5, -13.5, -18.5},
//             {-1.0, 0.0, 0.5, 0.0, -1.5, -5.0, -10.0, 0.0},
//             {-3.5, -1.0, 0.5, 1.5, -1.5, -3.0, 0.0, 0.0},
//             {-7.0, -3.5, -0.5, 2.5, 0.0, 0.0, 0.0, 0.0},
//             {-10.0, -6.5, -3.0, 0.0, 0.0, 0.0, 0.0, 0.0},
//             {-13.5, -11.5, -8.0, 0.0, 0.0, 0.0, 0.0, 0.0},
//             {-18.5, -16.5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
//             {-23.5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
//         };

// #ifdef DEBUG_BOARD
//     UVcout << QUACKLE_ALPHABET_PARAMETERS->userVisible(leave) << " has " << vowels << " vowels, " << cons << " cons.  value of " << vcvalues[vowels][cons] << endl;
// #endif

//     value += vcvalues[vowels][cons];

//     if (value < -40)
//         value = -40;

// #ifdef DEBUG_BOARD
//     UVcout << "leave " << QUACKLE_ALPHABET_PARAMETERS->userVisible(leave) << " worth " << value << " uniq " << QUACKLE_ALPHABET_PARAMETERS->userVisible(uniqleave) << " synergy " << synergy << endl;
// #endif

//     return value;
// }