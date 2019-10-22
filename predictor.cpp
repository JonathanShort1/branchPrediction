#include "predictor.h"

#include <iostream>

// -----------------------------------------------------------------------------
//                      Predictor PUBLIC FUNCTIONS
// -----------------------------------------------------------------------------

// CREATORS
Predictor::Predictor(int size, std::ifstream& traceFile)
: d_totalPredictions(0)
, d_mispredictions(0)
, d_size(size)
, d_traceFile(traceFile)
{
}

Predictor::~Predictor()
{
}

// ACCESSORS
void Predictor::printResults()
{
    std::cout
        << "Total predictions: " << d_totalPredictions << std::endl
        << "Number of mispredictions: " << d_mispredictions << std::endl;
}


