/*
 * Vikman Fernandez-Castro
 * February 5, 2022
 */

#include "pi.hpp"

using namespace std;

ostream & operator << (ostream & os, const PiBase & pi) {
    return pi.print(os);
}
