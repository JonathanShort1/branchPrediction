#ifndef TWO_BIT_H
#define TWO_BIT_H

#include <vector>

#include "predictor.h"

class TwoBitPredictor: public Predictor {
    private:
        // DATA
        std::vector<int>    d_table;
        int                 d_mask;

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
