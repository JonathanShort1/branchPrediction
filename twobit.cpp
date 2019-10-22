#include "twobit.h"
#include <iostream>

// -----------------------------------------------------------------------------
//                      TwoBitPredictor PUBLIC FUNCTIONS
// -----------------------------------------------------------------------------

// CREATORS
TwoBitPredictor::TwoBitPredictor(int size, std::ifstream& traceFile)
: Predictor(size, traceFile)
, d_table(size, 0)
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
    }
}

// MODIFIERS
void TwoBitPredictor::predict()
{
    uint64_t addr;
    int taken;
    while (d_traceFile >> addr >> taken) {
        int index = addr & bit_masks[d_mask];
        std::cout << index << std::endl;
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
        ++d_totalPredictions;
    }
}