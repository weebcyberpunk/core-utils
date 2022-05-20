#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
#define WC_DEF        0x25
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
unsigned long runs;

unsigned long total_byte_c;
unsigned long total_char_c;
unsigned long total_line_c;
unsigned long total_max_line;
unsigned long total_word_c;

// WC {{{
int wc(char *filename) {

	if (!opt) opt = WC_DEF;
	FILE *fp;

	if (!strcmp(filename, "-"))
		fp = stdin;

	else
		fp = fopen(filename, "r");
	
	if (fp == NULL) {
		fprintf(stderr, "Cannot open file: %s", filename);
		errno = 1;
		return(errno);
	}

	//
	// main loop
	//

	unsigned long byte_c = 0;
	unsigned long char_c = 0;
	unsigned long line_c = 0;
	unsigned long max_line = 0;
	unsigned long word_c = 0;

	// assist vars
	unsigned long max_line_count = 0;

	char c;
	char last_c = ' '; // needed for word count
	for (;;) {

		c = getc(fp);

		// max line count
		max_line_count++;
		if ((c == '\n') || (c == EOF)) {

			if (max_line_count > max_line) 
				max_line = max_line_count;

			max_line_count = 0;
		}

		// \n count
		if (c == '\n')
			line_c++;

		// word count, also needs to be before break
		if ((c > 32) && (c != 127)) {

			if ((last_c == ' ') || ((last_c > 9) && (last_c < 13)))
				word_c++;
		}

		if (c == EOF) {

			if ((last_c > 32) && (c != 127))
				word_c++;

			break;
		}

		// TODO make it actually diferentiate chars and bytes
		byte_c++;
		char_c++;

		last_c = c;
	}

	total_byte_c += byte_c;
	total_char_c += char_c;
	total_line_c += line_c;
	total_max_line += max_line;
	total_word_c += word_c;

	if (opt & WC_LINES)
		printf("%lu ", line_c);

	if (opt & WC_WORDS)
		printf("%lu ", word_c);

	if (opt & WC_CHARS)
		printf("%lu ", char_c);

	if (opt & WC_BYTES)
		printf("%lu ", byte_c);

	if (opt & WC_LEN)
		printf("%lu ", max_line);

	if (fp != stdin)
		printf("- %s", filename);

	putchar('\n');

	return(errno);
}
// }}}

// FILESFROM {{{
int filesfrom(char *arg) {

	return(errno);
}
// }}}

// MAIN {{{
int main(int argv, char *argc[]) {

	opt = 0;
	runs = 0;

	// eval args
	for (int count = 1; count < argv; count++) {
		
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
			unsigned short is_filesfrom = 1;
			for(int c = 0; c < argsize; c++) {
				if (argc[count][c] != "files0-from="[c]) {
					is_filesfrom = 0;
					break;
				}
			}

			if (is_filesfrom)
				filesfrom(argc[count]);

			else {
				wc(argc[count]);
				runs++;
			}
		}
	}

	return(errno);
}
// }}}
