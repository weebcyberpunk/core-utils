#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
#define WC_BYTES      0x1
#define WC_CHARS      0x2
#define WC_LINES      0x4
#define WC_FILES_FROM 0x8
#define WC_LEN        0x10
#define WC_WORDS      0x20
#define VERSION "0.0.0"

/*
 * author GG weebcyberpunk@gmail.com
 * version 0.0.0
 * since May 11, 2022
 */

unsigned short opt;

int wc(char *filename) {

	return(errno);
}

int filesfrom(char *arg) {

	return(errno);
}

int main(int argv, char *argc[]) {

	// eval args
	for (int count = 0; count < argv; count++) {
		
		// most args a simple strcmp is sufficient, except for
		// --files0-from so that's compared alone

		if (!strcmp(argc[count], "-c") || !strcmp(argc[count], "--bytes"))
			opt = opt | WC_BYTES;

		else if (!strcmp(argc[count], "-m") || !strcmp(argc[count], "--chars"))
			opt = opt | WC_CHARS;

		else if (!strcmp(argc[count], "-l") || !strcmp(argc[count], "--lines"))
			opt = opt | WC_LINES;

		else if (!strcmp(argc[count], "-L") || !strcmp(argc[count], "--max-line-length"))
			opt = opt | WC_LEN;

		else if (!strcmp(argc[count], "-w") || !strcmp(argc[count], "--words"))
			opt = opt | WC_WORDS;

		else if (!strcmp(argc[count], "--help"))
			printf("Usage is similar to GNU's version.\n");

		else if (!strcmp(argc[count], "--version"))
			printf(VERSION);

		else {
			// if less text than the arg we just assume it's a file
			unsigned long argsize = strlen(argc[count]);
			if (argsize < 14) {
				wc(argc[count]);
				continue;
			}

			// see if the arg is the arg
			unsigned short have_ff = 1;
			for(int c = 0; c < argsize; c++) {
				if (argc[count][c] != "files0-from="[c]) {
					have_ff = 0;
					break;
				}
			}

			if (!have_ff)
				wc(argc[count]);

			else
				filesfrom(argc[count]);
		}
	}

	return(errno);
}
