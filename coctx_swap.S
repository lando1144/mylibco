.globl coctx_swap
#if !defined( __APPLE__ )
.type  coctx_swap, @function
#endif
// 在64位，调用函数coctx_swap时，rdi保存参数1，rsi保存参数2，通过rdi和rsi进行切换。rsp指向栈顶，也就是coctx_swap的返回地址（上一函数帧中的下一条指令地址）。

coctx_swap:
	leaq 8(%rsp),%rax //将rsp地址加8个字节（即偏移掉coctx_swap的返回地址所在位置）之后,保存到rax
	leaq 112(%rdi),%rsp //将传入第一个参数即coctx_t所在的地址，加112后，赋值给rsp，即让当前栈地址指向coctx_t中的regs[14]的最尾端（112/8=14），后面每pushq一次rsp -8
	pushq %rax //将之前的rax地址存入栈中（即regs[13]中）
	pushq %rbx //缓存rbx寄存器内容到regs[12]
	pushq %rcx //缓存rcx寄存器内容到regs[11]
	pushq %rdx //缓存rdx寄存器内容到regs[10]
	pushq -8(%rax) //缓存coctx_swap的返回地址到regs[9];
	pushq %rsi //缓存参数2的地址到regs[8];
	pushq %rdi // 以下操作都是类似
	pushq %rbp
	pushq %r8
	pushq %r9
	pushq %r12
	pushq %r13
	pushq %r14
	pushq %r15


	movq %rsi, %rsp //让rsp指向参数2的地址
	popq %r15  //依次用参数2的regs[14]中之前保存的值，填充到各个寄存器
	popq %r14
	popq %r13
	popq %r12
	popq %r9
	popq %r8
	popq %rbp 
	popq %rdi 
	popq %rsi
	popq %rax //当前协程要返回的地址，协程第一次切入时为协程的函数入口（contx_make中定义的）
	popq %rdx
	popq %rcx
	popq %rbx
	popq %rsp //让rsp指向当前切换到的context的栈地址
	pushq %rax //模拟call命令的压栈操作，将co_swap的返回地址压入栈顶（默认情况下）
	xorl %eax, %eax
	ret //弹出栈的内容给寄存器%eip，然后通过eip程序会跳转到是上面压入的 %rax 的对应的地址，即之前保存的co_swap的返回地址
