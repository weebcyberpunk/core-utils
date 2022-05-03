#include<stdio.h>
#include<errno.h>
#include<string.h>
#define OUTPUT_NEWLINE 1
#define INTERPRET_BACKSLASHS 2
#define VERSION "0.0.0"

/*
 * author GG weebcyberpunk@gmail.com
 * version 0.0.0
 * since May 02, 2022
 */
int echo(char *str, unsigned short args) {

	if (!(args & INTERPRET_BACKSLASHS))
		printf("%s", str);
	// todo: if -e

	return(errno);
}

int main(int argv, char *argc[]) {

	unsigned short args = OUTPUT_NEWLINE;
	for (int count = 1; count < argv; count++) {

		if (!strcmp(argc[count], "-n"))
			args = args & ~(OUTPUT_NEWLINE);
		else if (!strcmp(argc[count], "-e"))
			args = args | INTERPRET_BACKSLASHS;
		else if (!strcmp(argc[count], "-E"))
			args = args & ~(INTERPRET_BACKSLASHS);
		else echo(argc[count], args);

	}

	if (args & OUTPUT_NEWLINE) printf("\n");

	return(errno);
}
