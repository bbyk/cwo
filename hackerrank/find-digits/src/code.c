/*
 ============================================================================
 Name        : code.c
 Author      : Boris Byk
 Version     :
 Copyright   : It is free
 Description : https://www.hackerrank.com/challenges/find-digits
 ============================================================================
 */

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#define max(a, b) (((a) > (b)) ? (a) : (b))

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

int findDigits(int N) {
	if (1 == N) {
		return 1;
	}

	int acc = 0;
	int nc = N;
	while (nc > 0) {
		int digit = nc % 10;

		if (digit) {
			if (0 == (N % digit)) {
				acc++;
			}
		}
		nc /= 10;
	}

	return acc;
}

int main(int argc, const char* argv[]) {
	FILE* input;

	if (argc > 1) {
		input = fopen(argv[1], "r");
		if (NULL == input)
			return EXIT_FAILURE;
	} else {
		input = stdin;
	}


	int T;
	fscanf(input, "%d", &T);

	while (T--) {
		int N;

		fscanf(input, "%d", &N);

		int output = findDigits(N);
		printf("%d\n", output);
	}

	return EXIT_SUCCESS;
}
