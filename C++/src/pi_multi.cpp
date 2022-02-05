/*
 * Vikman Fernandez-Castro
 * February 5, 2022
 */

#include <ostream>
#include <cstring>
#include "pi.hpp"

using namespace std;

template <> PiMulti::Pi(long precision) {
    mpfr_init2(_value, precision);
    _precision = mpfr_get_str_ndigits(10, precision);
}

template <> PiMulti::~Pi() {
    mpfr_clear(_value);
    mpfr_free_cache();
}

template <> void PiMulti::compute() {
    mpfr_const_pi(_value, MPFR_RNDD);
}

template <> ostream & PiMulti::print(ostream & os) const {
    char * buf;
    mpfr_asprintf(&buf, "%Re", _value);

    char * exp = strstr(buf, "e+00");

    if (exp != NULL) {
        *exp = '\0';
    }

    os << buf;
    mpfr_free_str(buf);

    return os;
}
