//
// Created by Swarup on 2026-05-29.
//

#ifndef OTHERS_H
#define OTHERS_H

#include <stdint.h>
#include <stdio.h>
#include "../types.h"

static inline uint32_t nonzero_strlen(const char *str) {
	uint32_t len = 0;
	while (str[len]) len++;
	return len;
}

static inline uint32_t true_strlen(const char *str) {
	uint32_t len = 0;
	while (str[len]) len++;
	return len+1;
}

static inline void reverseInPlace(char *str) {
	int start = 0;
	int end = nonzero_strlen(str) - 1;
	while (start < end) {
		char tmp = str[start];
		str[start++] = str[end];
		str[end--] = tmp;
	}
}

static inline void reverseInPlace(char *str, uint32nz_t len) {
	uint32_t start = 0;
	uint32_t end = len - 1;
	while (start < end) {
		char tmp = str[start];
		str[start++] = str[end];
		str[end--] = tmp;
	}
}


static inline void reverseCopy(const char *src, char *dest) {

	int len = nonzero_strlen(src);

	for (int i = 0; i < len; i++) {
		dest[i] = src[(len - 1) - i];
	}
	// may be removed based on situation
	dest[len] = '\0';
}

static inline void reverseCopy(const char *src, char *dest, uint32nz_t len) {

	for (int i = 0; i < len; i++) {
		dest[i] = src[(len - 1) - i];
	}
	// may be removed based on situation
	dest[len] = '\0';
}

static inline void numberToBaseNString(int num, int base, char *out) {


	if (num == 0) {
		out[0] = '0';
		out[1] = '\0';
		return;
	}

	int i = 0;
	while (num > 0) {
		int digit = num % base;
		out[i++] = (digit < 10) ? ('0' + digit) : ('A' + digit - 10);
		num /= base;
	}

	reverseInPlace(out, i);
	out[i] = '\0';
}

static inline int stringToBaseNNumber(const char *str, uint32nz_t len, int base) {
	int result = 0;

	for (int i = 0; i < len; i++) {
		char c = str[i];
		int val;

		if (c >= '0' && c <= '9') {
			val = c - '0';
		} else if (c >= 'A' && c <= 'Z') {
			val = c - 'A' + 10;
		} else {
			return -1; // Invalid character
		}

		if (val >= base) return -1; // Out of range

		result = result * base + val;
	}

	return result;
}


static inline void numberToBase10String(int num, char *out) {
	sprintf(out, "%d", num);  // Converts integer to base-10 string
}



//assume '0' <= character <= '9'
static inline int stringToBase10Number(const char *str, int len) {
	int result = 0;

	for (int i = 0; i < len; i++) {
		result = result * 10 + (str[i] - '0');
	}
	return result;
}

//assume '0' <= character <= '9'
static inline int substringToBase10Number(const char *str, int start, int end) {
	int result = 0;

	for (int i = start; i < end; i++) {
		result = result * 10 + (str[i] - '0');
	}

	return result;
}



#endif //OTHERS_H
