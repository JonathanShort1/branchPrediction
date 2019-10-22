#include "twobit.h"

// CREATORS
TwoBitPredictor::TwoBitPredictor(int size, std::ifstream& traceFile)
: Predictor(size, traceFile)
{

}

// MODIFIERS
void TwoBitPredictor::predict()
{
    unsigned long long addr;
    int taken;
    while (d_traceFile >> addr >> taken) {
        if (!taken) {
            ++d_mispredictions;
        }
        ++d_totalPredictions;
    }
}