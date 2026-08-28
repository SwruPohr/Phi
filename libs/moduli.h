//
// Created by Swarup on 2026-05-29.
//

#ifndef MODULI_H
#define MODULI_H

#include <math.h>

static inline short custom_abs(short a) {
    if (a < 0 ) return -a;
    return a;
}

// Round up (ceil)
static inline short up(double a) {
    if (a != 0) return (short)ceil(a);
    if (a == 0) return 0;
}

// Round down (floor)
static inline short down(double a) {
    if (a != 0) return (short)floor(a);
    if (a == 0) return 0;
}

// Round towards infinity
static inline short inf(double a) {
    if (a > 0) return up(a);
    if (a < 0) return down(a);
    if (a == 0) return 0;
}

// Round towards zero (truncate)
static inline short zero(double a) {
    if (a > 0) return down(a);
    if (a < 0) return up(a);
    if (a == 0) return 0;
}

// Round towards nearest up for 0.5 case
static inline short nearest_up(double a) {
    if (a != 0) return (short)round(a);
    if (a == 0) return 0;
}

// Round towards nearest down for 0.5 case
static inline short nearest_down(double a) {
    if (a != 0) return (short)round(a - 0.5);
    if (a == 0) return 0;
}

// Round towards nearest infinity for 0.5 case
// negatives round down for 0.5
// positives round up for 0.5
static inline short nearest_inf(double a) {
    if (a < 0 ) return nearest_down(a);
    if (a > 0 ) return nearest_up(a);
    if (a == 0) return 0;
}

// Round towards nearest zero for 0.5 case
static inline short nearest_zero(double a) {
    if (a < 0 ) return nearest_up(a);
    if (a > 0 ) return nearest_down(a);
    if (a == 0) return 0;
}


// General modulus using a rounding function
static inline short modulus(short (*custom_round)(double), short a, short b) {
    //if (b == 0) exit(1);
    if (a == 0) return 0;
    return a - b * custom_round((double)a / b);
}

// Euclidean modulus (just floor)
static inline short mod_euclidean(short a, short b) {
    //if (b == 0) exit(1);
    if (a == 0) return 0;
    short s = custom_abs(b);
    return a - s * down(a / s);
}


#endif //MODULI_H
