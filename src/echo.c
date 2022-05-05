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

	else {
		unsigned short interpret = 0;
		for (int count = 0;; count++) {

			if (str[count] == '\0') break;

			if (interpret) {

				switch (str[count]) {

					case '0': putchar('\0'); break;
					case 'a': putchar('\a'); break;
					case 'b': putchar('\b'); break;
					case 't': putchar('\t'); break;
					case 'n': putchar('\n'); break;
					case 'v': putchar('\v'); break;
					case 'f': putchar('\f'); break;
					case 'r': putchar('\r'); break;
					default: printf("\\%c", str[count]);
				}
				
				interpret = 0;
				continue;
			}

			if (str[count] == '\\') interpret = 1;
			else {
				interpret = 0;
				putchar(str[count]);
			}
		}
	}

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
