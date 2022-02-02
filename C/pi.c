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

#include <math.h>

#define distance(x1, y1, x2, y2) sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2))
#define leg(l, h) sqrt(h * h - l * l)

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
