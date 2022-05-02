bin/cat : cat.c
	cc cat.c -o cat

cat-vtest : test/cat-vtest.c
	cc test/cat-vtest.c -o test/cat-vtest

.PHONY : cat-vtest-run

cat-vtest-run : cat vtest
	./test/vtest | ./cat -v
