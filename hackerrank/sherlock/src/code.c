/*
 ============================================================================
 Name        : code.c
 Author      : Boris Byk
 Version     :
 Copyright   : It is free
 Description : https://www.hackerrank.com/challenges/sherlock-and-the-beast
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


	int T;
	fscanf(input, "%d", &T);

	while (T--) {
		int N;
		fscanf(input, "%d", &N);

		int three5, five3;

		int residual = N % 3;
		switch (residual) {
		case 0:
			three5 = N / 3;
			five3 = 0;
			break;
		case 1:
			three5 = (N / 3);
			if (three5 < 3) {
				printf("-1\n");
				continue;
			}
			three5 -= 3;
			five3 = 2;
			break;
		case 2:
			three5 = (N / 3);
			if (three5 < 1) {
				printf("-1\n");
				continue;
			}
			three5 -= 1;
			five3 = 1;
			break;
		}

		while (three5--) {
			printf("555");
		}

		while (five3--) {
			printf("33333");
		}

		printf("\n");
	}


	return EXIT_SUCCESS;
}
