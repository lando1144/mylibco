#include <iostream>
#include <time.h>
#include "ctx.h"

coctx_t *ctx_func = NULL;
coctx_t ctx_main;

int run_count = 0;

struct para {
    int val1;
    int val2;
};



void* func(void * args) {
    para *p = (para*)args;
    int i = run_count;
    while (i--) {
        //std::cout << "func  " << i << " parameter" << p->val1 << p->val2 << std::endl;
        co_swap(ctx_func, &ctx_main);
    }
    return NULL;
}


int main() {
    std::cin >> run_count;
    para p1;
    p1.val1 = 1;
    p1.val2 = 2;
    ctx_func = co_init(func, 8 * 1024, (void *)&p1);
    clock_t start, ends;
    start = clock();
    int i = run_count;
    while (i--) {
        co_swap(&ctx_main, ctx_func);
        //std::cout << "main func" << std::endl;
    }
    ends = clock();
    std::cout << "Running Time: " << (ends - start)/ CLOCKS_PER_SEC << " s" << std::endl;
    return 0;
}
