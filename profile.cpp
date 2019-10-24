#include "profile.h"

#include <iostream>
#include <string>
#include <sstream>

// -----------------------------------------------------------------------------
//                      Profile PRIVATE FUNCTIONS
// -----------------------------------------------------------------------------

void Profile::updateCountTable(std::vector<int>& table,
                               const int index,
                               const int taken)
{
    switch(table[index]) {
        case 0:
            if (taken) {
                table[index] = 1;
                ++d_mispredictions;
            }
            break;
        case 1:
            if (taken) {
                table[index] = 3;
                ++d_mispredictions;
            } else {
                table[index] = 0;
            }
            break;
        case 2:
            if (taken) {
                table[index] = 3;
            } else {
                table[index] = 0;
                ++d_mispredictions;
            }
            break;
        case 3:
            if (!taken) {
                table[index] = 2;
                ++d_mispredictions;
            }
            break;
    }
}

// -----------------------------------------------------------------------------
//                      Profile PUBLIC FUNCTIONS
// -----------------------------------------------------------------------------

// CREATORS
Profile::Profile(int size, std::ifstream& traceFile, std::ifstream& csv) 
: Predictor(size, traceFile)
, d_easyTable(size, 0)
, d_hardTable(size, 0)
, d_globalRegister(0)
, d_csv (csv)
{
    switch(size) {
        case 512:
            d_mask = 0;
            break;
        case 1024:
            d_mask = 1;
            break;
        case 2048:
            d_mask = 2;
            break;
        case 4096:
            d_mask = 3;
            break;
        case 8192:
            d_mask = 4;
            break;
        case 16384:
            d_mask = 5;
            break;
        case 524288:
            d_mask = 6;
            break;
    }
}

void Profile::buildMap()
{
    std::vector<std::string> row; 
    std::string line, word, temp; 

    uint64_t addr;
    int branch_bias;
    d_csv >> temp;
    while (d_csv >> line) { 
        row.clear();
        //getline(d_csv, line);
        std::stringstream s(line);
        while (std::getline(s, word, ',')) {
            row.push_back(word); 
        }
        addr = stoull(row[0]);
        branch_bias = atoi(row[3].data());
        d_map.emplace(addr,branch_bias);
    }
}

// MODIFIERS
void Profile::predict()
{
    buildMap();

    uint64_t addr;
    int taken;
    int xOr;
    int index;
    typedef std::map<uint64_t, int>::iterator It;
    while (d_traceFile >> addr >> taken) {
        It it = d_map.find(addr);
        int lower = (d_globalRegister &  d_bit_masks[d_mask]);
        xOr = index ^ lower;
        index = addr & d_bit_masks[d_mask];
        if (it->second) { //hard
            updateCountTable(d_hardTable, xOr, taken);

            // sort global history
            d_globalRegister <<= 1;
            d_globalRegister |= taken;
        } else { //easy
            updateCountTable(d_easyTable, xOr, taken);
        }
        ++d_totalPredictions;
    }
}