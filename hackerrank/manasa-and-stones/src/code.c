/*
 ============================================================================
 Name        : code.c
 Author      : Boris Byk
 Version     :
 Copyright   : It is free
 Description : https://www.hackerrank.com/challenges/manasa-and-stones
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

void lastStones(int n, int a, int b) {
	if (1 == n) {
		printf("0\n");
		return;
    }

	int num_of_edges = n - 1;

	if (a == b) {
		printf("%d\n", a * num_of_edges);
		return;
	}

	if (a > b) {
		int tmp = a;
		a = b;
		b = tmp;
	}

	for (int i = 0; i <= num_of_edges; i++) {
		int sum = (num_of_edges - i) * a + i * b;

		printf("%d ", sum);
	}

	printf("\n");
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
		int n, a, b;

		fscanf(input, "%d", &n);

		fscanf(input, "%d", &a);

		fscanf(input, "%d", &b);

		lastStones(n, a, b);
	}

	return EXIT_SUCCESS;
}
