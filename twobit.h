#ifndef TWO_BIT_H
#define TWO_BIT_H

#include <vector>

#include "predictor.h"

class TwoBitPredictor: public Predictor {
    private:
    



    public:
        // CREATORS
        TwoBitPredictor(int size, std::ifstream& traceFile);
        ~TwoBitPredictor();

        // MODIFIERS
        void predict();
};

// -----------------------------------------------------------------------------
//                      TwoBitPredictor PUBLIC FUNCTIONS
// -----------------------------------------------------------------------------

inline
TwoBitPredictor::~TwoBitPredictor()
{
}

#endif
