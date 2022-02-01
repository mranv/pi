/*
 * Approximate the number pi using polygons
 *
 * Procedure:
 * Sweep the first quarter of the circumference.
 * Iterate over Y axis and calculate the corresponding X using the Pythagorean theorem.
 * Calculate and accumulate the distance between the current point and the previous point.
 *
 * circumference = quarter * 4
 * pi = circumference / diameter
 *
 * Vikman Fernandez-Castro
 * February 9, 2018
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

#define NAME            "pi"
#define VERSION         "v1.1"
#define DEF_DIAMETER    100000

#define distance(x1, y1, x2, y2) sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2))
#define leg(l, h) sqrt(h * h - l * l)

static double calculate_pi(double diameter);
static void help() __attribute__((noreturn));

int main(int argc, char ** argv) {
    long diameter = DEF_DIAMETER;
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

double calculate_pi(double diameter) {
    double radius = diameter / 2;
    double quarter = 0;
    double x;
    double y = 1;
    double prev_x = radius;
    double prev_y = 0;

    // First point: (radius, 0)
    // Sweep first quarter

    while (y <= radius) {
        x = leg(y, radius);
        quarter += distance(x, y, prev_x, prev_y);
        prev_x = x;
        prev_y = y++;
    }

    // pi = circumference / diameter
    return quarter * 2 / radius;
}

void help() {
    printf("PI calculator - %s\n", VERSION);
    printf("\n");
    printf("Usage: %s [ diameter ]\n", NAME);
    printf("    diameter    Diameter of the circumference. Default: %d\n", DEF_DIAMETER);
    printf("The larger the diameter, the better the accuracy.\n");
    exit(EXIT_SUCCESS);
}
