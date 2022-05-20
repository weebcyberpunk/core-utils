.PHONY : all cat-vtest-run echo-run

all : bin/cat bin/echo bin/wc

bin/cat : src/cat.c
	cc src/cat.c -o bin/cat

bin/echo : src/echo.c
	cc src/echo.c -o bin/echo

bin/wc : src/wc.c
	cc src/wc.c -o bin/wc

cat-vtest : test/cat-vtest.c
	cc test/cat-vtest.c -o test/cat-vtest

cat-vtest-run : bin/cat test/vtest
	./test/vtest | ./bin/cat -v

echo-run : bin/echo
	./bin/echo -e 'Lorem\n Ipsum'
	./bin/echo -n 'Lorem Ipsum'
	./bin/echo 'Lorem Ipsum'
	./bin/echo 'Lorem Ipsum'
