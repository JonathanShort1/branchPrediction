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

// MODIFIERS
void TwoBitPredictor::predict()
{
    uint64_t addr;
    int taken;
    while (d_traceFile >> addr >> taken) {
        int index = addr & d_bit_masks[d_mask];
        d_buckets_used.emplace(index);
        switch(d_table[index]) {
            case 0:
                if (taken) {
                    d_table[index] = 1;
                    ++d_mispredictions;
                }
                break;
            case 1:
                if (taken) {
                    d_table[index] = 3;
                    ++d_mispredictions;
                } else {
                    d_table[index] = 0;
                }
                break;
            case 2:
                if (taken) {
                    d_table[index] = 3;
                } else {
                    d_table[index] = 0;
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