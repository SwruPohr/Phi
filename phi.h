//
// Created by Swarup on 2026-05-07.
//

#ifndef PHI_H
#define PHI_H
#include <stdint.h>

#include "deque.h"

typedef struct {
    int dI;
    Deque dq;
}Phi;

#define phi_init_with_malloc() { \
    1, \
    dq_init_with_malloc(10) \
    }

#define phi_setup(p, n) do { \
    dq_zero(p.dq); \
    dq_anchor(p.dq, 1); \
    dq_append(p.dq, n); \
    } while (0);

#define phi_next(p) do { \
    dq_add(p.dq, (p.dI-1), 1); \
    } while (0);

#define phi_next_n(p, n) do { \
    dq_add(p.dq, p.dI-1, n); \
} while (0);

#define phi_simplify(p) do { \
    if (dq_size(p.dq) == 1 && dq_get_first(p.dq) < 2) break; \
    int changed = 1; \
    while (changed) { \
        if (dq_get_last(p.dq) > 1) { \
            dq_append(p.dq,0); \
            dq_append(p.dq,0); \
        } \
        if (dq_get_first(p.dq)
    }
#endif //PHI_H
