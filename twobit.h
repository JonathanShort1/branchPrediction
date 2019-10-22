#ifndef TWO_BIT_H
#define TWO_BIT_H

#include <vector>

#include "predictor.h"

class TwoBitPredictor: public Predictor {
    private:
        // DATA
        std::vector<int>    d_table;
        int                 d_mask;

        uint64_t bit_masks[4] = {
            0x00000000000001ff, // 512 entries
            0x00000000000002ff, // 1024 entries
            0x00000000000003ff, // 2048 entries
            0x00000000000004ff, // 4096 entries
        };

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
