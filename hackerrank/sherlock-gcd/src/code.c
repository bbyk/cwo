/*
 ============================================================================
 Name        : code.c
 Author      : Boris Byk
 Version     :
 Copyright   : It is free
 Description : https://www.hackerrank.com/challenges/sherlock-and-gcd
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

int gcd(int v1, int v2) {
	// stein's algorithm
	if (v1 < v2) {
		int tmp = v2;
		v2 = v1;
		v1 = tmp;
	}

	if (v2 == 0)
		return v1;

	if (v2 == 1)
		return 1;

	if ((v1 & 1) && (v2 & 1)) {
		return gcd(v1 - v2, v2);
	} else if (!(v1 & 1) && (v2 & 1)) {
		return gcd(v1 >> 1, v2);
	} else if ((v1 & 1) && !(v2 & 1)) {
		return gcd(v1 , v2 >> 1);
	} else {
		return 2 * gcd(v1 >> 1, v2 >> 1);
	}
	return v1;
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

		int cgdc = 0;

		while(N--) {
			int v;
			fscanf(input, "%d", &v);

			cgdc = gcd(cgdc, v);
		}

	    if (1 == cgdc)
	    	printf("YES\n");
	    else
	    	printf("NO\n");
	}


	return EXIT_SUCCESS;
}
