/*
 * Vikman Fernandez-Castro
 * February 5, 2022
 */

#include <cstdlib>
#include <unistd.h>
#include <iostream>
#include <memory>
#include <chrono>
#include "pi.hpp"
#include "options.hpp"

using namespace std;
using namespace std::chrono;

static void print_out(const unique_ptr<PiBase> & pi, double time_ms) {
    if (isatty(STDOUT_FILENO)) {
        cout << "Pi = " << *pi << endl;
        cout << "Precision = " << pi->precision() << " digits\n";
        cout << "Time = " << time_ms << " ms\n";
    } else {
        cout << "{\"pi\":\"" << *pi << "\",\"precision\":" << pi->precision() << ",\"time_ms\":" << time_ms << "}";
    }
}

int main(int argc, char ** argv) {
    unique_ptr<PiBase> pi;
    Options options(argc, argv);

    switch (options.mode()) {
    case Options::Double:
        pi = make_unique<PiDouble>(0);
        break;
    case Options::Multi:
        pi = make_unique<PiMulti>(options.precision());
    }

    auto begin = steady_clock::now();
    pi->compute();
    auto time_ms = duration<double, milli>(steady_clock::now() - begin).count();

    print_out(pi, time_ms);

    return EXIT_SUCCESS;
}
