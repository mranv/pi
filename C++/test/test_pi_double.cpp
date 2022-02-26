/*
 * Vikman Fernandez-Castro
 * February 26, 2022
 */

#include <gtest/gtest.h>
#include "../include/pi.hpp"
#include <ostream>

using std::ostringstream;

TEST(PiDouble, Precision) {
    PiDouble pi;
    EXPECT_EQ(pi.precision(), 16);
}

TEST(PiDouble, Value) {
    PiDouble pi;
    ostringstream buf;

    pi.compute();
    buf << pi;

    EXPECT_EQ(buf.str(), "3.141592653589793");
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
