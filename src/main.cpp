#include <iostream>
#include <unistd.h>
#include <string>
#include <sstream>

#include "predictor.h"
#include "always_taken.h"
#include "twobit.h"
#include "gshare.h"
#include "profile.h"

using namespace std;

int predict(const char *filename, const char *csv_file, int predictor, int size)
{
    ifstream infile(filename);
    switch (predictor) {
        case 1:
            {
                AlwaysTaken at(size, infile);
                at.predict();
                at.printResults();
                break;
            }
        case 2:
            {
                TwoBitPredictor tbp(size, infile);
                tbp.predict();
                tbp.printResults();
                break;
            }
        case 3:
            {
                GShare gshare(size, infile);
                gshare.predict();
                gshare.printResults();
                break;
            }
        case 4:
            {
                ifstream csv(csv_file);
                Profile pro(size, infile, csv);
                pro.predict();
                pro.printResults();
                break;
            }
        default:
            cout << "Invalid predictor choice (use -h for help)" << endl;
            return 1;
    }
    return 0;
}

int main(int argc, char *argv[])
{
    stringstream ss;
    ss << "-h\n\t print options and usage" << endl;
    ss << "-p\n\t select the predictor to use, defaults to 1"  << endl;
    ss << "\t(1 = always taken, 2 = 2-bit predictor, 3 = gshare, 4 = profiled)"  << endl;
    ss << "-s\n\t select size of predictor table, defalts to 1024" << endl;
    ss << "-t\n\t trace file to use" << endl;

    stringstream usage;
    usage << "Uasge (must supply all options): ./main.out -p 2 -s 512 -t <path/to/trace/file>" << endl;
    usage << "Usage: ./main.out -h (for help)" << endl;
    
    int tflag = 0;
    int sflag = 0;
    int pflag = 0;

    char *filename = NULL;
    char *csv = NULL;
    int predictor = 1;
    int size = 1024;

    opterr = 0;
    int c;
    while ((c = getopt (argc, argv, "hp:s:t:c:")) != -1) {
        switch (c)
        {
            case 'h':
                cout << ss.str();
                cout << usage.str();
                return 0;
            case 'p':
                pflag = 1;
                predictor = atoi(optarg);
                break;
            case 's':
                sflag = 1;
                size =  atoi(optarg);
                break;
            case 't':
                tflag = 1;
                filename = optarg;
                break;
            case 'c':
                csv = optarg;
                break;
            case ':':
            case '?':
            default:
                cout << "Invalid option or missing arguments: '-"
                    << static_cast<char>(c) << endl;
                cout << usage.str();
                return 1;
        }
    }

    if (tflag && sflag && pflag) {
        return predict(filename, csv, predictor, size);
    } else {
        cout << usage.str();
    }
    return 0;
}