#include "predictor.h"

#include <iostream>
#include <iomanip>

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
        << "Number of mispredictions: " << d_mispredictions << std::endl
        << "Misprediction rate: " << std::fixed << std::setprecision(2)
        << 100 * (static_cast<double>(d_mispredictions) / static_cast<double>(d_totalPredictions))
        << "%" << std::endl
        << "Percentage of buckets_used: "
        << 100 * (static_cast<double>(d_buckets_used.size()) / static_cast<double>(d_size)) << "%"
        << std::endl;
}


