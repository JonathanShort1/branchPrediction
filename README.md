# branchPrediction
C++ Simulation of branch prediction, using pin to verify correctness

# How to compile:
    * `cd branchPrediction`
    * `make`

# How to run
    * `./main.out -p <predictor> -s <size> -t <path/to/tracefile>
    * -p can be the value 1,2,3 or 4.
        - 1 = Always taken predictor
        - 2 = Two-bit predictor
        - 3 = GShare predictor
        - 4 = Profiled predictor
    * -s can be 512, 1024, 2048, 4096, 8192, 16384
    * -t: must be a valid trace file
    * All arguments must be supplied even if not used 
    * Arguments are assumed valid and the simulator will likely crash otherwise
    * This is because the focus of the assignment is on the experiment and not software development
