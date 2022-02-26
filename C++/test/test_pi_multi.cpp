/*
 * Vikman Fernandez-Castro
 * February 26, 2022
 */

#include <gtest/gtest.h>
#include "../include/pi.hpp"
#include <ostream>

using std::ostringstream;

TEST(PiMulti, Precision) {
    PiMulti pi(10000);
    EXPECT_EQ(pi.precision(), 3012);
}

TEST(PiMulti, Value) {
    PiMulti pi(128);
    ostringstream buf;

    pi.compute();
    buf << pi;

    EXPECT_EQ(buf.str(), "3.141592653589793238462643383279502884195");
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
