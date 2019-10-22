#ifndef PREDICTOR_H
#define PREDICTOR_H

#include <fstream>

class Predictor {
    protected:
        int             d_totalPredictions;
        int             d_mispredictions;
        int             d_size;
        std::ifstream&  d_traceFile;

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