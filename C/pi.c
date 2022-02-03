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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "pi.h"

typedef struct {
    long radius;
    long y_min;
    long y_max;
    mpfr_t arc;
} pi_arg_t;

void pi_arc(long radius, long y_min, long y_max, mpfr_t arc) {
    mpfr_t radius_sqr;
    mpfr_t x;
    mpfr_t y;
    mpfr_t t;
    mpfr_t prev_x;
    mpfr_t prev_y;

    mpfr_init2(radius_sqr, PI_PRECISION);
    mpfr_init2(x, PI_PRECISION);
    mpfr_init2(y, PI_PRECISION);
    mpfr_init2(t, PI_PRECISION);
    mpfr_init2(prev_x, PI_PRECISION);
    mpfr_init2(prev_y, PI_PRECISION);

    mpfr_set_si(radius_sqr, radius, MPFR_RNDD);
    mpfr_sqr(radius_sqr, radius_sqr, MPFR_RNDD);
    mpfr_set_si(arc, 0, MPFR_RNDD);
    mpfr_set_si(prev_y, y_min, MPFR_RNDD);

    // prev_x = leg(y_min, radius) = sqrt(radius^2 - y_min^2)
    mpfr_sqr(t, prev_y, MPFR_RNDD);
    mpfr_sub(t, radius_sqr, t, MPFR_RNDD);
    mpfr_sqrt(prev_x, t, MPFR_RNDD);

    // for (y = y_min + 1; y < y_max + 1; y++)
    for (mpfr_set_si(y, y_min + 1, MPFR_RNDD); mpfr_cmp_si(y, y_max + 1) < 0; mpfr_add_si(y, y, 1, MPFR_RNDD)) {
        // x = leg(y, radius) = sqrt(radius^2 - y^2)
        mpfr_sqr(t, y, MPFR_RNDD);
        mpfr_sub(t, radius_sqr, t, MPFR_RNDD);
        mpfr_sqrt(x, t, MPFR_RNDD);

        // arc += distance(x, y, prev_x, prev_y)
        mpfr_sub(prev_x, x, prev_x, MPFR_RNDD);
        mpfr_sub(prev_y, y, prev_y, MPFR_RNDD);
        mpfr_hypot(t, prev_x, prev_y, MPFR_RNDD);
        mpfr_add(arc, arc, t, MPFR_RNDD);

        mpfr_set(prev_x, x, MPFR_RNDD);
        mpfr_set(prev_y, y, MPFR_RNDD);
    }

    mpfr_clear(radius_sqr);
    mpfr_clear(x);
    mpfr_clear(y);
    mpfr_clear(t);
    mpfr_clear(prev_x);
    mpfr_clear(prev_y);
}

static void * pi_thread_run(pi_arg_t * arg) {
    pi_arc(arg->radius, arg->y_min, arg->y_max, arg->arc);
    return NULL;
}

void pi_compute(long radius, long nproc) {
    mpfr_t quarter;
    mpfr_t pi;

    if (radius % nproc != 0) {
        fprintf(stderr, "ERROR: radius %ld is not divisible per %ld threads.\n", radius, nproc);
        abort();
    }

    mpfr_init2(quarter, PI_PRECISION);
    mpfr_init2(pi, PI_PRECISION);

    pthread_t * threads = malloc(sizeof(pthread_t) * nproc);
    pi_arg_t * args = malloc(sizeof(pi_arg_t) * nproc);

    // First point: (radius, 0)
    // Sweep first quarter

    for (int i = 0; i < nproc; i++) {
        args[i].radius = radius;
        args[i].y_min = radius / nproc * i;
        args[i].y_max = radius / nproc * (i + 1);
        mpfr_init2(args[i].arc, PI_PRECISION);

        int r = pthread_create(&threads[i], NULL, (void * (*)(void *))pi_thread_run, &args[i]);

        if (r != 0) {
            fprintf(stderr, "ERROR: Cannot run thread: %s.\n", strerror(r));
            abort();
        }
    }

    mpfr_set_si(quarter, 0, MPFR_RNDD);

    for (int i = 0; i < nproc; i++) {
        int r = pthread_join(threads[i], NULL);

        if (r != 0) {
            fprintf(stderr, "ERROR: Cannot join thread: %s.\n", strerror(r));
            abort();
        }

        mpfr_add(quarter, quarter, args[i].arc, MPFR_RNDD);
        mpfr_clear(args[i].arc);
    }

    free(threads);
    free(args);

    // pi = quarter * 2 / radius
    mpfr_mul_si(quarter, quarter, 2, MPFR_RNDD);
    mpfr_div_si(pi, quarter, radius, MPFR_RNDD);

    mpfr_out_str(stdout, 10, 0, pi, MPFR_RNDD);
    printf("\n");

    mpfr_clear(quarter);
    mpfr_clear(pi);
}
