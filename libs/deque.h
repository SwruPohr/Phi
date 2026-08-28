//
// Created by Webcloud on 2026-05-06.
//

#ifndef DEQUE_H
#define DEQUE_H

#endif //DEQUE_H


typedef struct {
    int *data;
    size_t capacity;
    size_t first; /* 0 to capacity */
    size_t last; /* 0 to capacity - 1 */
} Deque;

#define dq_size(dq) (dq.first == dq.capacity ? 0 : dq.first <= dq.last ? dq.last - dq.first + 1 : dq.capacity - dq.first + dq.last + 1)

#define dq_is_empty(dq) (dq.first == dq.capacity)
#define dq_is_full(dq) ((dq.first == 0 && dq.last == dq.capacity - 1) || dq.first == dq.last + 1)


// APPRENSION


// assume not full
#define dq_enlarge_back(dq) \
    if (dq.first == dq.capacity) {dq.first = dq.last;} \
    else {dq.last = (dq.last == dq.capacity - 1 ? 0 : dq.last + 1);}

#define dq_append(dq, v) {\
    dq_enlarge_back(dq); \
    dq.data[dq.last] = (v); \
    }

#define dq_push_back(dq, v) dq_append(dq, v)

// assume not full
#define dq_enlarge_front(dq) \
    if (dq.first == dq.capacity) {dq.first = dq.last;} \
    else {dq.first = (dq.first == 0 ? dq.capacity - 1 : dq.first - 1);}

#define dq_prepend(dq, v) {\
    dq_enlarge_front(dq); \
    dq.data[dq.first] = (v); \
    }

#define dq_push_front(dq, v) dq_prepend(dq, v)


// assume not empty
#define dq_contract_back(dq) \
    if (dq.first == dq.last) {dq.first == dq.capacity;} \
    else { dq.last = (dq.last == 0 ? dq.capacity : dq.last - 1);}

#define dq_pop_back(dq) {\
    dq.data[dq.last] = 0; \
    dq_contract_back(dq); \
    }

#define dq_contract_front(dq) \
    if (dq.first == dq.last) {dq.first == dq.capacity;} \
    else {dq.last = (dq.last == 0 ? dq.capacity : dq.last - 1);}

#define dq_pop_front(dq) { \
    dq.data[dq.first]= 0; \
    dq_contract_front(dq) \
    }

// GET SET


// dq.first < dq.size < dq.capacity
// i < dq.size < dq.capacity
// TODO: optimize
#define dq_get(dq, i) (dq.data[(dq.first + i) % dq.capacity])
#define dq_set(dq, i, var) { \
    dq.data[(dq.first + i) % dq.capacity] = (var); \
    }

#define dq_get_first(dq) (dq[dq.first])
#define dq_get_last(dq) (dq[dq.last])

#define dq_set_first(dq, var) { \
    dq.data[dq.first] = (var) \
    }

#define dq_set_last(dq, var) { \
    dq.data[dq.last] = (var) \
    }

// i < dq.size < dq.capacity
#define dq_get_unsafe(dq, i) (dq.data[i])
#define dq_set_unsafe(dq, i, var) { \
    dq.data[i] = (var); \
    }

#define dq_set_prev(dq, i) dq_set(dq, i, dq_get(dq, i - 1))
#define dq_set_next(dq, i) dq_set(dq, i, dq_get(dq, i + 1))

#define dq_shift_right(dq, left, right) \
    for (int i = right; i >= left; i--) { \
        dq_set_prev(dq, i); \
    }

#define dq_shift_left(dq, left, right) \
    for (int i = left; i < right; i++) { \
        dq_set_next(dq, i); \
    }

#define dq_insert(dq, i, var) \
    if (2 * i >= dq_size(dq)) { \
        dq_enlarge_back(dq); \
        dq_shift_right(dq, i, dq_size(dq)); \
        dq_set(dq, i, var); \
    } \
    else { \
        dq_enlarge_front(dq); \
        dq_shift_left(dq, 0, i); \
        dq_set(dq, i, var); \
    }

#define dq_delete(dq, i) \
    if (2 * i > dq_size(dq)) { \
        dq_shift_left(dq, i, dq_size(dq)); \
        dq_pop_back(dq); \
    } \
    else { \
        dq_shift_right(dq, 0, i); \
        dq_pop_front(dq); \
    }




// SHOW DOW
#define dq_show(dq) \
    for (int i = 0; i < dq_size(dq); i++) { \
    printf("%d\t", dq_get(dq, i)); \
    }

#define dq_print(dq) \
    for (int i = 0; i < dq.capacity; i++) { \
    printf("%d\t", dq_get_unsafe(dq, i)); \
    }


// initialization
#define dq_zero(dq) \
    for (int i = 0; i < dq.capacity; i++) {\
        dq_set_unsafe(dq, i, 0); \
    }

#define dq_empty(dq) {\
    dq.first = dq.capacity; dq.last = 0; \
    }


#define dq_init_with_malloc(cap) { \
    malloc(sizeof(int) * cap), \
    cap, \
    cap, \
    0 \
    }

#define dq_init(ptr, cap) { \
    ptr, \
    cap, \
    cap, \
    0 \
    }

#define dq_anchor(dq, i) \
    if (dq.first == dq.capacity) {\
        dq.last = (i < dq.capacity) ? i : 0; \
    }


#define dq_transfer_from(dq, dq2) \
    if (dq.first == dq.capacity) {dq2.first == dq.capacity;} \
    else { \
        dq2.first = 0; \
        dq2.last = dq_size(dq) - 1; \
        for (int i = 0; i < dq2.last + 1; i++) {\
            dq_set_unsafe(dq2, i, dq_get(dq, i)); \
        } \
}

#define dq_realloc(dq, new_cap) \
    if (new_cap >= dq_size(dq)) { \
        Deque dq2 = dq_init_with_malloc(new_cap); \
        dq_zero(dq2); \
        dq_transfer_from(dq, dq2); \
        free(dq.data); \
        dq = dq2; \
    }

#define dq_realloc_unsafe(dq, new_cap) { \
        Deque dq2 = dq_init_with_malloc(new_cap); \
        dq_zero(dq2); \
        dq_transfer_from(dq, dq2); \
        free(dq.data); \
        dq = dq2; \
    }

#define dq_fit(dq) { \
        Deque dq2 = dq_init_with_malloc(dq_size(dq)); \
        dq_zero(dq2); \
        dq_transfer_from(dq, dq2); \
        free(dq.data); \
        dq = dq2; \
    }

#define dq_try(dq, fn, ...) { \
    if (dq_is_full(dq)) {dq_realloc_unsafe(dq, dq.capacity * 2);} \
    dq_##fn(dq, ##__VA_ARGS__); \
    }
