/*
 ============================================================================
 Name        : code.c
 Author      : Boris Byk
 Version     :
 Copyright   : It is free
 Description : https://www.hackerrank.com/challenges/sherlock-and-queries
 ============================================================================
 */

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#define MIN(a, b) (((a) < (b)) ? (a) : (b))

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

#define PRIME 1000000007L

typedef unsigned long ULONG;
typedef struct __pair {
	ULONG C; // C coef.
	ULONG M; // multiplier
} PAIR;

typedef struct __node NODE;
struct __node {
	int ci; // value;
	NODE *next;
};

ULONG A[100000], B[100000], C[100000];
PAIR* cache[100000];

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

	for (int i=0; i<N; i++)
		fscanf(input, "%lu", A+i);

	for (int i=0; i<M; i++)
		fscanf(input, "%lu", B+i);

	for (int i=0; i<M; i++)
		fscanf(input, "%lu", C+i);

	NODE *set_head = NULL;
	for (int i=0; i<M; i++) {
		int cache_index = B[i] - 1;
		PAIR *p = cache[cache_index];
		if (NULL == p) {
			p = malloc(sizeof(PAIR));
			p->C = C[i];
			p->M = p->C;
			cache[cache_index] = p;
			NODE *new_node = malloc(sizeof(NODE));
			new_node->ci = cache_index;
			new_node->next = set_head;
			set_head = new_node;
		} else { // say B[10] == B[13] = 7, then A[7] = A[7] * C10 * C13
			p->C *= C[i];
			p->C %= PRIME;
			p->M = p->C;
		}
	}

	NODE *pnode = set_head;
	while(pnode) {
		int cache_index = pnode->ci;
		PAIR* p = cache[cache_index];

		int m = 2;
		while (true) {
			cache_index = (pnode->ci + 1) * m - 1;
			if (cache_index >= N)
				break;
			PAIR* mp = cache[cache_index];
			if (NULL == mp) {
				mp = malloc(sizeof(PAIR));
				mp->C = -1;
				mp->M = p->C;
				cache[cache_index] = mp;
			} else {
				mp->M *= p->C;
				mp->M %= PRIME;
			}
			m++;
		}

		pnode = pnode->next;
	}

	for (int i=0; i<N; i++) {
		PAIR *p = cache[i];
		if (p) {
			A[i] *= p->M;
			A[i] %= PRIME;
		}

		printf("%lu ", A[i]);
	}

	return EXIT_SUCCESS;
}
