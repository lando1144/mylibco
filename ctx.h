#ifndef __CTX_H__
#define __CTXH__

#include <stdlib.h>


enum {
  kRDI = 7,
  kRSI = 8,
  kRETAddr = 9,
  kRSP = 13,
};

// 64 bit
// low | regs[0]: r15 |
//    | regs[1]: r14 |
//    | regs[2]: r13 |
//    | regs[3]: r12 |
//    | regs[4]: r9  |
//    | regs[5]: r8  |
//    | regs[6]: rbp |
//    | regs[7]: rdi |
//    | regs[8]: rsi |
//    | regs[9]: ret |  //ret func addr
//    | regs[10]: rdx |
//    | regs[11]: rcx |
//    | regs[12]: rbx |
// hig | regs[13]: rsp |

struct coctx_t
{
// #if defined(__i386__)
// 	void *regs[8];
// #else
	void *regs[14];
//#endif
	size_t ss_size;
	char *ss_sp;

};
typedef void* (*coctx_pfn_t)(void* s);


int co_make(coctx_t *ctx, coctx_pfn_t pfn, const void *s, const void *s1);

coctx_t * co_init(coctx_pfn_t pfn, int stack_size = 8 * 1024, void *arg1 = NULL, void *arg2 = NULL);

void co_swap(coctx_t *cur, coctx_t *next);

#endif

