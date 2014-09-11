/*
 ============================================================================
 Name        : utopian-tree.c
 Author      : Boris Byk
 Version     :
 Copyright   : It is free
 Description : https://www.hackerrank.com/challenges/utopian-tree
 ============================================================================
 */

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

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
	int cache[60];
	cache[0] = 1;
	for (int i = 1; i < 60; i++) {
		if (i & 0x1)
			cache[i] = cache[i - 1] << 1;
		else
			cache[i] = cache[i - 1] + 1;
	}

	for (int i = 0; i < T; i++) {
		int readb;
		if ((readb = getline(&line.p, &line.len, input)) == -1) {
			free(line.p);
			return EXIT_FAILURE;
		}

		int N = atoi(line.p);
		printf("%d\n", cache[N]);
	}

	if (stdin != input)
		fclose(input);
	free(line.p);

	return EXIT_SUCCESS;
}
