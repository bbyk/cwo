/*
 ============================================================================
 Name        : code.c
 Author      : Boris Byk
 Version     :
 Copyright   : It is free
 Description : https://www.hackerrank.com/challenges/maximizing-xor
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

typedef struct __sLINE {
	char* p;
	size_t len;
} LINE;

int maxXor(int L, int R) {
   if (L == R)
       return 0;

   int max_xor = 0;
   int imask = 1 << 10;
   int amask = imask - 1;
   imask >>= 1;

   for (int i = R; i >= L; i--)
   {
	   int m = imask;
	   int check = ~i & amask;

	   while(m > 0) {
		   if (check >= L && check <= R) {
			   max_xor = max(max_xor, check ^ i);
		   	   break;
		   }

		   if (m == 1)
			   break;
		   check ^= m;
		   m >>=1;
	   }
   }

   return max_xor;
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

	LINE line;
	line.p = NULL;
	line.len = 0;

	if (getline(&line.p, &line.len, input) == -1) {
		if (line.p != NULL)
			free(line.p);
		return EXIT_FAILURE;
	}

	int L = atoi(line.p);

	if (getline(&line.p, &line.len, input) == -1) {
		if (line.p != NULL)
			free(line.p);
		return EXIT_FAILURE;
	}

	int R = atoi(line.p);

	if (stdin != input)
		fclose(input);
	free(line.p);

	int res = maxXor(L, R);
	printf("%d", res);

	return EXIT_SUCCESS;
}
