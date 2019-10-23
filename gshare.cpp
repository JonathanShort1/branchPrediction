#include "gshare.h"

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
, d_table(4096, 0)
, d_globalRegister(0)
, d_mask(0x00000000000004ff)
, d_grMask(0x00000000000000ff)
{
}

// MODIFIERS
void GShare::predict()
{
    uint64_t addr;
    int taken;
    int xOr;
    int index;
    while (d_traceFile >> addr >> taken) {
        index = addr & d_mask;

        // sort global history
        d_globalRegister >>= 1;
        d_globalRegister |= taken;

        // XOR index with global history
        xOr = index ^ (d_globalRegister & d_grMask);
        updateCountTable(xOr, taken);

        ++d_totalPredictions;
    }
}