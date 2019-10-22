#include "always_taken.h"

// CREATORS
AlwaysTaken::AlwaysTaken(int size, std::ifstream& traceFile)
: Predictor(size, traceFile)
{

}

// MODIFIERS
void AlwaysTaken::predict()
{
    uint64_t addr;
    int taken;
    while (d_traceFile >> addr >> taken) {
        if (!taken) {
            ++d_mispredictions;
        }
        ++d_totalPredictions;
    }
}