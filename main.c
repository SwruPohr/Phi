#include <stdio.h>
#include <stdlib.h>

#include "phi.h"

int main(void) {
    const int toConvert = 10;

    Phi p = phi_init_with_malloc();
    phi_setup(p, toConvert);
    phi_next(p);

    printf("%d", dq_get_last(p.dq));
    free(p.dq.data);
    return 0;
}