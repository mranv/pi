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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define distance(x1, y1, x2, y2) sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2))
#define leg(l, h) sqrt(h * h - l * l)

typedef struct {
    long radius;
    long y_min;
    long y_max;
    double arc;
} pi_arg_t;

double pi_arc(long radius, long y_min, long y_max) {
    double arc = 0;
    double prev_x = leg(y_min, radius);
    double prev_y = y_min;

    for (double y = y_min + 1; y <= y_max; y++) {
        double x = leg(y, radius);
        arc += distance(x, y, prev_x, prev_y);
        prev_x = x;
        prev_y = y;
    }

    return arc;
}

void * pi_thread_run(pi_arg_t * arg) {
    arg->arc = pi_arc(arg->radius, arg->y_min, arg->y_max);
    return NULL;
}

double pi_compute(long radius, long nproc) {
    if (radius % nproc != 0) {
        fprintf(stderr, "ERROR: radius %ld is not divisible per %ld threads.\n", radius, nproc);
        abort();
    }

    pthread_t * threads = malloc(sizeof(pthread_t) * nproc);
    pi_arg_t * args = malloc(sizeof(pi_arg_t) * nproc);

    // First point: (radius, 0)
    // Sweep first quarter

    for (int i = 0; i < nproc; i++) {
        args[i].radius = radius;
        args[i].y_min = radius / nproc * i;
        args[i].y_max = radius / nproc * (i + 1);
        int r = pthread_create(&threads[i], NULL, (void * (*)(void *))pi_thread_run, &args[i]);

        if (r != 0) {
            fprintf(stderr, "ERROR: Cannot run thread: %s.\n", strerror(r));
            abort();
        }
    }

    double quarter = 0;

    for (int i = 0; i < nproc; i++) {
        int r = pthread_join(threads[i], NULL);

        if (r != 0) {
            fprintf(stderr, "ERROR: Cannot join thread: %s.\n", strerror(r));
            abort();
        }

        quarter += args[i].arc;
    }

    free(threads);
    free(args);

    // pi = circumference / diameter
    return quarter * 2 / radius;
}
