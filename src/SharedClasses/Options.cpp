
#include "Options.hpp"
#include <unordered_map>

static unordered_map<char, bool> VOWELS = {{'a', true}, {'b', false}, {'c', false}, {'d', false}, {'e', true}, {'f', false}, {'g', false}, {'h', false}, {'i', true}, {'j', false}, {'k', false}, {'l', false}, {'m', false}, {'n', false}, {'o', true}, {'p', false}, {'q', false}, {'r', false}, {'s', false}, {'t', false}, {'u', true}, {'v', false}, {'w', false}, {'x', false}, {'y', false}, {'z', false}};
Options::Options()
{ //nothing
}
bool Options::isVowel(char *letter)
{
    return VOWELS[*letter];
} // Returns Alphabetic Sorted Rack.

std::vector<char> *Options::unusedRackTiles(std::vector<char> *Rack, Move *move)
{
    std::unordered_map<char, int> rackLetters;
    std::vector<char> *remainedTiles = new std::vector<char>();

    rackLetters[BLANK] = 0; // usedTiles from The Rack.

    for (int index = 0; index < move->word.length(); ++index)
    {
        if (move->word[index] >= 0 && move->word[index] <= 25) // on Board char.
        {
            continue;
        }
        else
        {
            if ((move->word[index] >= 97 && move->word[index] <= 122))
            {
                rackLetters[move->word[index]] = 0; // usedTiles from The Rack.
            }
        }
    }

    for (int index = 0; index < move->word.length(); ++index)
    {
        if (move->word[index] >= 0 && move->word[index] <= 25) // on Board char.
        {
            continue;
        }
        else
        {
            if (move->word[index] >= 65 && move->word[index] <= 90)
            {
                rackLetters[BLANK]++; // usedTiles from The Rack.
            }
            else
            {
                rackLetters[move->word[index]]++; // usedTiles from The Rack.
            }
        }
    }
    for (int index = 0; index < Rack->size(); ++index)
    {
        if (rackLetters[(*Rack)[index]] == 0)
        {
            remainedTiles->push_back((*Rack)[index]);
        }
        else
        {
            rackLetters[(*Rack)[index]]--;
        }
    }

    return remainedTiles;
} // Returns unusedTile in a rack given a move.
std::vector<char> *Options::sortRack(std::vector<char> *Rack)
{
    std::vector<char> *sortedTiles = new std::vector<char>();
    std::unordered_map<char, int> rackLetters;

    for (int index = 0; index < Rack->size(); ++index)
    {
        rackLetters[(*Rack)[index]] = 0; // usedTiles from The Rack.
    }
    for (int index = 0; index < Rack->size(); ++index)
    {
        rackLetters[(*Rack)[index]]++; // usedTiles from The Rack.
    }

    int index = 97;
    while (index <= 122)
    {
        if (rackLetters[index] == 0)
        {
            index++;
        } // usedTiles from The Rack.
        else
        {
            sortedTiles->push_back(index);
            rackLetters[index]--;
        }
    }
    while (rackLetters[BLANK] > 0)
    {
        sortedTiles->push_back(BLANK);
        rackLetters[BLANK]--;
    }

    return sortedTiles;
} // Returns Alphabetic Sorted Rack.
