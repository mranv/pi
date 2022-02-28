/*
 * Vikman Fernandez-Castro
 * February 5, 2022
 */

#include <unistd.h>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <climits>
#include "options.hpp"

using namespace std;

static const Options::Mode DEFAULT_MODE = Options::Multi;
static const long DEFAULT_PRECISION = 10000;

static const char HELP_STR[] = R"(Pi calculator - v1.1

Usage: pi [ -h ] [ -m <method> ] [ -p <precision> ]
    -h              Show this help.
    -m <method>     Calculation method: double|multi. Default: multi.
    -p <precision>  Precision in bits. Default for multi: 10000)";

Options::Options(int argc, char * const argv[]) {
    const char VAL_DOUBLE[] = "double";
    const char VAL_MULTI[] = "multi";
    int c;
    char * end;

    _mode = DEFAULT_MODE;
    _precision = DEFAULT_PRECISION;

    opterr = 0;

    while ((c = getopt(argc, argv, "hm:p:")) != -1) {
        switch (c) {
        case 'h':
            cout << HELP_STR << endl;
            exit(0);

        case 'm':
            if (strstr(VAL_DOUBLE, optarg) == VAL_DOUBLE) {
                _mode = Double;
            } else if (strstr(VAL_MULTI, optarg) == VAL_MULTI) {
                _mode = Multi;
            } else {
                cerr << "ERROR: Invalid value for option -m.\n";
                exit(EXIT_FAILURE);
            }

            break;

        case 'p':
            _precision = strtol(optarg, &end, 10);

            if (*end != '\0' || _precision < 1 || _precision >= 9223372036854775552) {
                cerr << "ERROR: Invalid value for option -p.\n";
                exit(EXIT_FAILURE);
            }

            break;

        default:
            cerr << "ERROR: Invalid option -" << (char)optopt << ".\n";
            exit(EXIT_FAILURE);
        }
    }

    if (_mode == Double && _precision != DEFAULT_PRECISION) {
        cerr << "WARNING: Precision parameter will be ignored in double mode.\n";
    }
}
