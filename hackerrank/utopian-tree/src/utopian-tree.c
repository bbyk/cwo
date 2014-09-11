/*
 ============================================================================
 Name        : Gem Stones.c
 Author      : Boris Byk
 Version     :
 Copyright   : It is free
 Description : https://www.hackerrank.com/challenges/gem-stones
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

	int N = atoi(line.p);
	int intersection[26];
	int current[26];

	for (int i = 0; i < N; i++) {
		int readb;
		if ((readb = getline(&line.p, &line.len, input)) == -1) {
			free(line.p);
			return EXIT_FAILURE;
		}

		memset(current, 0, sizeof(current));
		for (int j = 0; j < readb-1; j ++){
			int hash = line.p[j] - 'a';
			current[hash] = 1;
		}

		if (0 == i)
			memcpy(intersection, current, sizeof(current));
		else {
			for (int j=0; j<26; j++) {
				if (intersection[j] > 0 && intersection[j] != current[j])
					intersection[j] = 0;
			}
		}
	}

	int unique = 0;
	for (int i=0; i < 26; i++) {
		if (intersection[i] > 0)
			unique++;
	}

	printf("%d\n", unique);

	if (stdin != input)
		fclose(input);
	free(line.p);

	return EXIT_SUCCESS;
}
