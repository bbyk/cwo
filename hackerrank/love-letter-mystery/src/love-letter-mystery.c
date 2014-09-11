/*
 ============================================================================
 Name        : love-letter-mystery.c
 Author      : Boris Byk
 Version     :
 Copyright   : It is free
 Description : https://www.hackerrank.com/challenges/the-love-letter-mystery
 ============================================================================
 */

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#define ABS(x)           (((x) < 0) ? -(x) : (x))

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

typedef struct __sLINE {
	char* p;
	size_t len;
} LINE;

int main(int argc, const char* argv[]) {
	FILE* input;

	if (argc > 1) {
		input = fopen(argv[1], "r");
		if (NULL == input)
			return EXIT_FAILURE;
	} else {
		input = stdin;
	}

	LINE line;
	line.p = NULL;
	line.len = 0;

	if (getline(&line.p, &line.len, input) == -1) {
		if (line.p != NULL)
			free(line.p);
		return EXIT_FAILURE;
	}

	int T = atoi(line.p);

	while(T-- > 0) {
		int readb;
		if ((readb = getline(&line.p, &line.len, input)) == -1) {
			free(line.p);
			return EXIT_FAILURE;
		}

		if ('\n' == line.p[readb - 1])
			readb--;

		int count = 0;
		int mid = (readb - 1) / 2;
		for (int i=0; i<=mid; i++) {
			int l = line.p[i];
			int r = line.p[readb - 1 - i];
			if (l != r) {
				count += ABS(r - l);
			}
		}

		printf("%d\n", count);
	}

	if (stdin != input)
		fclose(input);
	free(line.p);

	return EXIT_SUCCESS;
}
