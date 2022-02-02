/*
 * Approximate the number pi using polygons
 *
 * Vikman Fernandez-Castro
 * February 2, 2022
 */

#ifndef PI_H
#define PI_H

#define PI_NAME             "pi"
#define PI_VERSION          "v1.1"
#define PI_DEFAULT_RADIUS   100000000

double pi_compute(long radius, long nproc);
double pi_arc(long radius, long y_min, long y_max);

#endif
