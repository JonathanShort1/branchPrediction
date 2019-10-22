#ifndef GSHARE_H
#define GSHARE_H

#include <vector>

#include "predictor.h"

class GShare: public Predictor {
    private:
        // DATA
        std::vector<int>    d_table;
        std::vector<int>    d_history;
        uint64_t            d_mask;

        // MODIFIERS
        void updateCountTable(const int index, const int taken);

    public:
        // CREATORS
        GShare(int size, std::ifstream& traceFile);
        ~GShare();

        // MODIFIERS
        void predict();
};

// -----------------------------------------------------------------------------
//                      GShare PUBLIC FUNCTIONS
// -----------------------------------------------------------------------------

inline
GShare::~GShare()
{
}

#endif