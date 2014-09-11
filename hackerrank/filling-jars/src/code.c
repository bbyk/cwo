/*
 ============================================================================
 Name        : code.c
 Author      : Boris Byk
 Version     :
 Copyright   : It is free
 Description : https://www.hackerrank.com/challenges/filling-jars
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


int main(int argc, const char* argv[]) {
	FILE* input;

	if (argc > 1) {
		input = fopen(argv[1], "r");
		if (NULL == input)
			return EXIT_FAILURE;
	} else {
		input = stdin;
	}


	int N, M;
	fscanf(input, "%d %d", &N, &M);

	unsigned long sum = 0;

	while (M--) {
		unsigned long a, b, k;

		fscanf(input, "%lu %lu %lu", &a, &b, &k);

		sum += (b - a + 1) * k;
	}

	printf("%lu\n", sum / N);

	return EXIT_SUCCESS;
}
