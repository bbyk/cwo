/*
 ============================================================================
 Name        : service-lane.c
 Author      : Boris Byk
 Version     :
 Copyright   : It is free
 Description : Service Lane in C: https://www.hackerrank.com/challenges/service-lane
 ============================================================================
 */

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

typedef struct __sLINE {
	char* p;
	size_t len;
} LINE;

typedef struct __sLaneReader {
	int *lane;
	int start;
	int end;
	int threshold;
} LANER;

typedef struct __sLanes {
	int *l2, *l3;
} LANES;

int car_for_range(LANES* lanes, int start, int end) {
	if (lanes->l3[start] >= end)
		return 3;
	if (lanes->l2[start] >= end)
		return 2;

	return 1;
}

void add_to_lane(LANER* r, int index, int item) {
	if (r->start > -1) {
		if (item >= r->threshold) {
			r->end = index;
		} else {
			for (int i = r->start; i <= r->end; i++) {
				r->lane[i] = r->end;
			}
			r->start = -1;
		}
	} else {
		if (item >= r->threshold) {
			r->start = r->end = index;
		}
	}
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
	int N, T;
	sscanf(line.p, "%d %d", &N, &T);

	LANER r2, r3;
	r2.start = -1;
	r2.lane = malloc(N * sizeof(int));
	memset(r2.lane, 0, N * sizeof(int));
	r3.start = -1;
	r3.lane = malloc(N * sizeof(int));
	memset(r3.lane, 0, N * sizeof(int));

	LANES lanes;
	lanes.l2 = r2.lane;
	lanes.l3 = r3.lane;

	r2.threshold = 2;
	r3.threshold = 3;

	int item;

	for (int i=0; i < N; i++)
	{
		fscanf(input, "%d", &item);
		add_to_lane(&r2, i, item);
		add_to_lane(&r3, i, item);
	}

	add_to_lane(&r2, N, 0);
	add_to_lane(&r3, N, 0);

	if (getline(&line.p, &line.len, input) == -1) {
		if (line.p != NULL)
			free(line.p);
		return EXIT_FAILURE;
	}

	for (int i = 0; i < T; i++) {
		int readb;
		if ((readb = getline(&line.p, &line.len, input)) == -1) {
			free(line.p);
			return EXIT_FAILURE;
		}

		int start, end;
		sscanf(line.p, "%d %d", &start, &end);
		printf("%d\n", car_for_range(&lanes, start, end));
	}

	if (stdin != input)
		fclose(input);
	free(line.p);

	return EXIT_SUCCESS;
}
