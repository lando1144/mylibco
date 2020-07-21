#include <string.h>
#include "ctx.h"

int co_make(coctx_t *ctx, coctx_pfn_t pfn, const void *s, const void *s1)
{
	char *sp = ctx->ss_sp + ctx->ss_size;
	sp = (char *)((unsigned long)sp & -16LL);
	memset(ctx->regs, 0x0, sizeof(ctx->regs));
	void **ret_addr = (void **)(sp);
	*ret_addr = (void *)pfn;
    ctx->regs[kRSP] = sp - 8; // 函数调用时，栈中首先会压入8个字节的返回地址
	ctx->regs[kRETAddr] = (char *)pfn;
	ctx->regs[kRDI] = (char *)s;
	ctx->regs[kRSI] = (char *)s1;
	return 0;
}


extern "C"
{
	extern void coctx_swap(coctx_t *, coctx_t*) asm("coctx_swap");
};

void co_swap(coctx_t *cur, coctx_t *next)
{
	coctx_swap(cur, next);
}


coctx_t *co_init(coctx_pfn_t pfn, int stack_size, void *arg1, void *arg2)
{
    coctx_t *ctx = (coctx_t *)malloc(sizeof(coctx_t));
	memset(ctx, 0, sizeof(coctx_t));
	ctx->ss_size = stack_size;
	ctx->ss_sp = (char *)malloc(stack_size);
    co_make(ctx, pfn, arg1, arg2);
	return ctx;
}

