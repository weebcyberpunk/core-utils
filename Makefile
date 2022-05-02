bin/cat : src/cat.c
	cc src/cat.c -o bin/cat

cat-vtest : test/cat-vtest.c
	cc test/cat-vtest.c -o test/cat-vtest

.PHONY : cat-vtest-run

cat-vtest-run : bin/cat test/vtest
	./test/vtest | ./bin/cat -v
