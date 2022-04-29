#include<stdio.h>
#include<stdlib.h>

/*
 * author GG weebcyberpunk@gmail.com
 * version 1.0.0
 * since Apr 29, 2022
 */

/*
 * This program will dump all 127 ascii characters alongside with their number.
 * Use it to test cat by piping it's output to cat's input.
 */
int main() {

	for (int c = 0; c <= 127; c++)
		printf("%i - %c\n", c, c);

	return(0);
}
