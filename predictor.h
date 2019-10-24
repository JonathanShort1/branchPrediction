#ifndef PREDICTOR_H
#define PREDICTOR_H

#include <fstream>
#include <set>

class Predictor {
    protected:
        // DATA
        int             d_totalPredictions;
        int             d_mispredictions;
        int             d_size;
        std::ifstream&  d_traceFile;
        std::set<int>   d_buckets_used;

        uint64_t d_bit_masks[7] = {
            0x00000000000001ff, // 512 entries
            0x00000000000003ff, // 1024 entries
            0x00000000000007ff, // 2048 entries
            0x0000000000000fff, // 4096 entries
            0x0000000000001fff, // 8192 entries
            0x0000000000003fff, // 16385 entries
            0x000000000007ffff  // 19 bit address
        };

    public:
        // CREATORS
        Predictor(int size, std::ifstream& traceFile);
        ~Predictor();

        // ACCESSORS
        void printResults();

        // MODIFIERS
        virtual void predict() = 0;
};

#endif