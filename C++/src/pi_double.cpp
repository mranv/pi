/*
 * Vikman Fernandez-Castro
 * February 5, 2022
 */

#include <ostream>
#include <iomanip>
#include <cmath>
#include "pi.hpp"

using namespace std;

template <> PiDouble::Pi(long precision __attribute__((unused))) : _precision(16) {
}

template <> PiDouble::~Pi() {
}

template <> void PiDouble::compute() {
    _value = acos(-1);
}

template <> ostream & PiDouble::print(ostream & os) const {
    return os << std::setprecision(16) << _value;
}
