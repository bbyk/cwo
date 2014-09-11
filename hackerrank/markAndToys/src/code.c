#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

void swap(int *arr, int i, int j) {
	int tmp = arr[i];
	arr[i] = arr[j];
	arr[j] = tmp;
}

int partition(int *  arr, int pivot, int n) {
	if (pivot > 0) {
		swap(arr, 0, pivot);
		pivot = 0;
	}

    for (int i = 1; i < n; i++) {
       if (arr[i] < arr[pivot]) {
           if (i - 1 > pivot) {
        	   swap(arr, i, pivot + 1);
           }

           // swap
           swap(arr, pivot + 1, pivot);
           pivot++;
       }
    }

    return pivot;
}

void quick_sort(int* arr, int n) {
	if (n < 2)
		return;

	int pivot = rand() % n;
	pivot = partition(arr, pivot, n);

	quick_sort(arr, pivot);
	quick_sort(arr + pivot + 1, n - pivot - 1);
}

int main(int argc, const char * argv[]) {
	/* initialize random seed */
	srand(time(NULL));

	FILE* input;

	if (argc > 1) {
		input = fopen(argv[1], "r");
		if (NULL == input)
			return EXIT_FAILURE;
	} else {
		input = stdin;
	}

	int n, k, i;
	fscanf(input, "%d %d", &n, &k);
	int *prices = (int *)malloc(sizeof(int)*n);
	for(i=0; i<n; i++) {
		fscanf(input, "%d", &prices[i]);
	}

	quick_sort(prices, n);

	int answer = 0, sum = 0;

	for (i = 0; i < n; i++) {
		sum += prices[i];

		if (sum > k) {
			break;
		}

		answer++;
	}


	printf("%d\n", answer);

	return EXIT_SUCCESS;
}
