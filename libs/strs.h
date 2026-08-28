//
// Created by Swarup on 2026-05-29.
//

#ifndef STRS_H
#define STRS_H


#include <stdio.h>
#include <stdlib.h>

static inline int isWhitespace(char c) { return ((c) == ' ' || ((c) >= '\t' && (c) <= '\r')); }

// buffer len not respected
static inline int get_until_whitespace (char **st, size_t *len, size_t *cap) {
    if (st == NULL) return 1;
    int c;
    size_t l = 0;
    char *str = *st;

    while ((c = getchar()) != EOF) {
        if (l + 1 >= *cap) {
            size_t newC = (*cap == 0) ? 16 : *cap * 2;
            char *tmp = realloc((void*)*str, newC);
            if (!tmp) return 2; // if realloc failed we do not free str.
            str = tmp;
            *cap = newC;
        }

        str[l++] = (char)c;

        if (isWhitespace(c)) break;
    }

    if (l > 0) {
        str[l] = '\0';
        *len = l;
        return 0;
    }
    if (c == EOF) return 3;
    return 4;
}

// buffer len not respected

static inline int void_until_delim (char delim) {
    int c;

    while ((c = getchar()) != EOF) {
        if (c == delim) break;
    }

    if (c == EOF) return 1;
    return 2;
}

static inline int get_until_delim (char **st, size_t *len, size_t *cap, char delim) {
    int c;
    size_t l = 0;
    char *str = *st;

    while ((c = getchar()) != EOF) {
        if (l + 1 >= *cap) {
            size_t newC = (*cap == 0) ? 16 : *cap * 2;
            char *tmp = realloc((void*)*str, newC);
            if (!tmp) return 2; // if realloc failed we do not free str.
            str = tmp;
            *cap = newC;
        }

        str[l++] = (char)c;

        if (c == delim) break;
    }
    if (l > 0) {
        str[l] = '\0';
        *len = l;
        return 0;
    }

    if (c == EOF) return 1;
    return 2;
}

static inline int int_from_string(char *str, int *n) {
    char *p = str;
    int sign = 1;
    int num = 0;
    int found = 0;

    // whitespace
    while (isWhitespace(*p)) p++;

    // sign
    if (*p == '-') {
        sign = -1;
        p++;
    } else if (*p == '+') {
        p++;
    }

    // digits
    while (*p >= '0' && *p <= '9') {
        num = (num * 10) + (*p - '0');
        p++;
        found = 1;
    }

    // set value
    if (found) *n = num * sign;

    // return found
    return !found;
}

// buffer len not respected
static inline int get_int_until_delim(int *n, char delim) {
    int c;
    int sign = 1;
    int num = 0;
    int found_digit = 0;
    int found_sign = 0;

    while ((c = getchar()) != EOF) {
        if (c == delim) break;

        if (c == '-' && !found_digit && !found_sign) {
            sign = -1;
            found_sign = 1;
        } else if (c == '+' && !found_digit && !found_sign) {
            found_sign = 1;
        } else if (c >= '0' && c <= '9') {
            num = (num * 10) + (c - '0');
            found_digit = 1;
        } else return 3;
    }

    if (found_digit) {
        *n = num * sign;
        return 0;
    }

    return (c == EOF) ? 1 : 2;
}

static inline int get_whitespace_as_int(int *n) {
    int c;
    int sign = 1;
    int num = 0;
    int found_digit = 0;
    int found_sign = 0;

    while ((c = getchar()) != EOF) {
        if (isWhitespace(c)) break;

        if (c == '-' && !found_digit && !found_sign) {
            sign = -1;
            found_sign = 1;
        } else if (c == '+' && !found_digit && !found_sign) {
            found_sign = 1;
        } else if (c >= '0' && c <= '9') {
            num = (num * 10) + (c - '0');
            found_digit = 1;
        } else return 3;
    }

    if (found_digit) {
        *n = num * sign;
        return 0;
    }

    return (c == EOF) ? 1 : 2;
}

static inline int ex() {
    int t; // test cases
    int n, k; // box count
    int a_prev, a_curr;


    size_t len = 0;
    size_t cap = 4096;
    char *str = malloc(sizeof(char) * cap);


    get_until_whitespace(&str, &len, &cap);
    int_from_string(str, &t);

    while (t--) {
        get_until_whitespace(&str, &len, &cap);
        int_from_string(str, &n);
        get_until_whitespace(&str, &len, &cap);
        int_from_string(str, &k);
        if (k >= 2) {
            printf("YES\n");
            void_until_delim('\n');
            goto cont;
        }

        a_prev = 0;
        for (int i = 0; i < n; i++) {
            get_until_whitespace(&str, &len, &cap);
            int_from_string(str, &a_curr);
            if (i > 0 && a_curr < a_prev) {
                if (i < n - 1) void_until_delim('\n');
                printf("NO\n");
                goto cont;
            }
            a_prev = a_curr;
        }

        printf("YES\n");
        cont: continue;
    }

    free(str);
    return 0;
}
#endif //STRS_H
