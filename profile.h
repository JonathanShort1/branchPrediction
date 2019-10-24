#ifndef PROFILE_H
#define PROFILE_H

#include <vector>
#include <map>

#include "predictor.h"

class Profile: public Predictor {
    private:
        // DATA
        std::vector<int>            d_easyTable;
        std::vector<int>            d_hardTable;
        uint64_t                    d_globalRegister;
        uint64_t                    d_mask;
        uint64_t                    d_grMask;
        std::ifstream&              d_csv;
        std::map<uint64_t, int>     d_map;

        // MODIFIERS
        void updateCountTable(std::vector<int>& table,
                              const int index,
                              const int taken);
        void buildMap();

    public:
        // CREATORS
        Profile(int size, std::ifstream& traceFile, std::ifstream& csv);
        ~Profile();

        // MODIFIERS
        void predict();
};

// -----------------------------------------------------------------------------
//                      Profile PUBLIC FUNCTIONS
// -----------------------------------------------------------------------------

inline
Profile::~Profile()
{
}

#endif