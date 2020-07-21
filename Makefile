a.out : test.cpp coctx_swap.S ctx.cpp
	g++ test.cpp coctx_swap.S ctx.cpp -g

clean :
	rm -rf a.out
