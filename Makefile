cat : cat.c
	cc cat.c -o cat

vtest : test/vtest.c
	cc test/vtest.c -o test/vtest

.PHONY : vtest-run

vtest-run : cat vtest
	./test/vtest | cat -v
