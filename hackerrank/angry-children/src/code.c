/*
 ============================================================================
 Name        : code.c
 Author      : Boris Byk
 Version     :
 Copyright   : It is free
 Description : https://www.hackerrank.com/challenges/angry-children
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

#define MAX 100000

long data[MAX];

typedef struct __bucket {
	long data[MAX];
	int size;
} bucket;

bucket buckets[16];

int main(int argc, const char* argv[]) {
	FILE* input;

	if (argc > 1) {
		input = fopen(argv[1], "r");
		if (NULL == input)
			return EXIT_FAILURE;
	} else {
		input = stdin;
	}

	int N, K;
	fscanf(input, "%d %d", &N, &K);

	for (int i = 0; i < N; i++) {
		fscanf(input, "%d", data + i);
	}

	// radix sort
	int num_of_4s = sizeof(int) * 2; // 2 four bits in a byte
	for (int  i = 0; i < num_of_4s; i++) {
		int offset = i * 4;
		long mask = 0xfL << offset;

		for (int j = 0; j < N; j++) {
			int bucket_index = (data[j] & mask) >> offset;
			bucket *b = &buckets[bucket_index];
			b->data[b->size++] = data[j];
		}

		int data_at = 0;
		for (int j = 0; j < 16; j++) {
			bucket *b = &buckets[j];
			for (int k = 0; k < b->size; k++) {
				data[data_at++] = b->data[k];
			}
			b->size = 0;
		}
	}

	long min = data[N - 1] - data[0];
	for (int i = 0; i <= N - K; i++) {
		min = MIN(min, data[i + K - 1] - data[i]);
	}

	printf("%l", min);

	return EXIT_SUCCESS;
}
