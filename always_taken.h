#ifndef ALWAYS_TAKEN_H
#define ALWAYS_TAKEN_H

#include "predictor.h"

class AlwaysTaken: public Predictor {
    public:
        // CREATORS
        AlwaysTaken(int size, std::ifstream& traceFile);
        ~AlwaysTaken();
        
        // MODIFIERS
        void predict();
};

// -----------------------------------------------------------------------------
//                      AlwaysTaken PUBLIC FUNCTIONS
// -----------------------------------------------------------------------------

inline
AlwaysTaken::~AlwaysTaken()
{
}

#endif
