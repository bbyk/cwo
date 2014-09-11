/*
 ============================================================================
 Name        : code.c
 Author      : Boris Byk
 Version     :
 Copyright   : It is free
 Description : https://www.hackerrank.com/challenges/is-fibo
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

#define MAX_VAL 10000000000L
#define PRIME 499

typedef struct __node NODE;
struct __node {
	unsigned long v;
	NODE *next;
};

NODE *ht[PRIME];

bool is_in_ht(unsigned long key) {
	int hash_code = key % PRIME;
	NODE *head = ht[hash_code];
	if (!head)
		return false;
	while(head) {
		if (head->v == key)
			return true;
		head = head->next;
	}

	return false;
}

void add_to_ht(unsigned long key) {
	int hash_code = key % PRIME;
	NODE *head = ht[hash_code];

	NODE *newNode = malloc(sizeof(NODE));
	newNode->v = key;
	newNode->next = head;

	ht[hash_code] = newNode;
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

	unsigned long fb0 = 0;
	unsigned long fb1 = 1;

	add_to_ht(fb0);
	add_to_ht(fb1);

	// we don't need to cache fibonacci number bigger than MAX_VAL
	while (fb1 < MAX_VAL) {
		unsigned long tmp = fb0 + fb1;
		fb0 = fb1;
		fb1 = tmp;

		add_to_ht(fb1);
	}

	int T;
	fscanf(input, "%d", &T);

	while(T--) {
		unsigned long N;
		fscanf(input, "%lu", &N);

		if (is_in_ht(N))
			printf("IsFibo\n");
		else
			printf("IsNotFibo\n");
	}

	return EXIT_SUCCESS;
}
