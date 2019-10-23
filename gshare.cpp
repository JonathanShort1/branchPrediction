#include "gshare.h"

#include <iostream>

// -----------------------------------------------------------------------------
//                      GShare PRIVATE FUNCTIONS
// -----------------------------------------------------------------------------

void GShare::updateCountTable(const int index, const int taken)
{
    switch(d_table[index]) {
        case 0:
            if (taken) {
                d_table[index] = 1;
                ++d_mispredictions;
            }
            break;
        case 1:
            if (taken) {
                d_table[index] = 2;
                ++d_mispredictions;
            } else {
                d_table[index] = 0;
            }
            break;
        case 2:
            if (taken) {
                d_table[index] = 3;
            } else {
                d_table[index] = 1;
                ++d_mispredictions;
            }
            break;
        case 3:
            if (!taken) {
                d_table[index] = 2;
                ++d_mispredictions;
            }
            break;
    }
}

// -----------------------------------------------------------------------------
//                      GShare PUBLIC FUNCTIONS
// -----------------------------------------------------------------------------

// CREATORS
GShare::GShare(int size, std::ifstream& traceFile)
: Predictor(size, traceFile)
, d_table(size, 0)
, d_globalRegister(0)
, d_grMask(0x00000000000000ff)
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
    }
}

// MODIFIERS
void GShare::predict()
{
    uint64_t addr;
    int taken;
    int xOr;
    int index;
    int min = 10000000;
    int max = 0;
    while (d_traceFile >> addr >> taken) {
        index = addr & d_bit_masks[d_mask];
        std::cout << index << std::endl;

        if (min > index) {
            min =  index;
        }

        if (max < index) {
            max = index;
        }

        // sort global history
        d_globalRegister >>= 1;
        d_globalRegister |= taken;

        // XOR index with global history
        xOr = index ^ ((d_globalRegister & d_grMask) << (d_mask + 1));
        updateCountTable(xOr, taken);

        ++d_totalPredictions;
    }
    std::cout << "min: " << min << std::endl;
    std::cout << "max: " << max << std::endl;
}