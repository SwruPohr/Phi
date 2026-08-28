//
// Created by Swarup on 2026-05-29.
//

#ifndef EPSILON_H
#define EPSILON_H
#include <stdint.h>
#include <stdio.h>
#include <string.h>

typedef struct {
    uint16_t sign: 1;
    uint16_t exponent: 5;
    uint16_t mantissa: 10;
} float16_t;

typedef struct {
    uint32_t sign: 1;
    uint32_t exponent: 8;
    uint32_t mantissa: 23;
} float32_t;

typedef struct {
    uint64_t sign : 1;
    uint64_t exponent : 11;
    uint64_t mantissa : 52;
} float64_t;

// Function to convert a float to float16_t
static inline float16_t floatToFloat16(float num) {
    float16_t result;
    uint16_t rawBits;
    memcpy(&rawBits, &num, sizeof(num));

    // Extract the components
    result.sign = (rawBits >> 15) & 0x1;
    result.exponent = (rawBits >> 10) & 0x1F;  // 5 bits for exponent
    result.mantissa = rawBits & 0x3FF;         // 10 bits for mantissa

    return result;
}
// Function to convert a float to float32_t (normal IEEE 754 single precision)
static inline float32_t floatToFloat32(float num) {
    float32_t result;
    uint32_t rawBits;
    memcpy(&rawBits, &num, sizeof(num));

    // Extract the components
    result.sign = (rawBits >> 31) & 0x1;
    result.exponent = (rawBits >> 23) & 0xFF;  // 8 bits for exponent
    result.mantissa = rawBits & 0x7FFFFF;      // 23 bits for mantissa

    return result;
}


// Function to convert a float to float64_t
static inline float64_t floatToFloat64(float num) {
    float64_t result;
    uint64_t rawBits;
    memcpy(&rawBits, &num, sizeof(num));

    // Extract the components
    result.sign = (rawBits >> 63) & 0x1;
    result.exponent = (rawBits >> 52) & 0x7FF;  // 11 bits for exponent
    result.mantissa = rawBits & 0xFFFFFFFFFFFFF;  // 52 bits for mantissa

    return result;
}

// Function to convert float16_t back to float
static inline float float16ToFloat(float16_t f) {
    uint32_t rawBits = 0;
    rawBits |= (f.sign << 31);
    rawBits |= (f.exponent << 23);
    rawBits |= (f.mantissa);

    float num;
    memcpy(&num, &rawBits, sizeof(num));
    return num;
}

// Function to convert float32_t back to float
static inline float float32ToFloat(float32_t f) {
    uint32_t rawBits = 0;
    rawBits |= (f.sign << 31);
    rawBits |= (f.exponent << 23);
    rawBits |= (f.mantissa);

    float num;
    memcpy(&num, &rawBits, sizeof(num));
    return num;
}

// Function to convert float64_t back to float
static inline float float64ToFloat(float64_t f) {
    uint64_t rawBits = 0;
    rawBits |= (f.sign << 63);
    rawBits |= (f.exponent << 52);
    rawBits |= (f.mantissa);

    float num;
    memcpy(&num, &rawBits, sizeof(num));
    return num;
}

// Function to print the components of the float types
static inline void printFloat16(float16_t f) {
    printf("float16: Sign: %u, Exponent: %u, Mantissa: %u\n", f.sign, f.exponent, f.mantissa);
}

static inline void printFloat32(float32_t f) {
    printf("float32: Sign: %u, Exponent: %u, Mantissa: %u\n", f.sign, f.exponent, f.mantissa);
}

static inline void printFloat64(float64_t f) {
    printf("float64: Sign: %llu, Exponent: %llu, Mantissa: %llu\n", f.sign, f.exponent, f.mantissa);
}
#endif //EPSILON_H
