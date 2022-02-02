/*
 * Approximate the number pi using polygons
 *
 * Vikman Fernandez-Castro
 * February 2, 2022
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include "pi.h"

static void help() __attribute__((noreturn));

int main(int argc, char ** argv) {
    long diameter = PI_DEF_DIAMETER;
    double pi;
    struct timespec t0, t1;

    if (argc > 1) {
        if (strcmp(argv[1], "--help") == 0) {
            help();
        }

        char * end;
        diameter = strtol(argv[1], &end, 10);

        if (*end || diameter <= 0) {
            fprintf(stderr, "Bad diameter: %s. Expecting positive integer number.\n", argv[1]);
            return EXIT_FAILURE;
        }
    }

    clock_gettime(CLOCK_MONOTONIC, &t0);
    pi = calculate_pi(diameter);
    clock_gettime(CLOCK_MONOTONIC, &t1);

    t1.tv_nsec += 1000000000 - t0.tv_nsec;
    t1.tv_sec += t1.tv_nsec / 1000000000 - t0.tv_sec - 1;
    t1.tv_nsec %= 1000000000;

    printf("Pi (calculated) = %.16f\n", pi);
    printf("Pi (predefined) = %.16f\n", M_PI);
    printf("     difference = %.16f\n", fabs(pi - M_PI));
    fprintf(stderr, "           time = %.10f ms\n", t1.tv_sec * 1000 + t1.tv_nsec / 1e6);

    return EXIT_SUCCESS;
}

void help() {
    printf("PI calculator - %s\n", PI_VERSION);
    printf("\n");
    printf("Usage: %s [ diameter ]\n", PI_NAME);
    printf("    diameter    Diameter of the circumference. Default: %d\n", PI_DEF_DIAMETER);
    printf("The larger the diameter, the better the accuracy.\n");
    exit(EXIT_SUCCESS);
}
