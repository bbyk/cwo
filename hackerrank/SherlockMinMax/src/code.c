#include <stdio.h>
#include <stdlib.h>

#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

int bin_search(unsigned *A, size_t N, unsigned needle) {
    int l = 0, r = N - 1;
    //printf("%zu %u\n", l, r);
    while(r >= l) {
        size_t m = l + (r - l) / 2;
        //printf("%zu %u\n", m, needle);
        if (needle > A[m]) {
            l = m + 1;
        } else if (needle < A[m]) {
            r = m - 1;
        } else {
            return m;
        }
    }

    return ~l;
}

int main(int argc, char* argv[]) {

	FILE* input;

	if (argc > 1) {
		input = fopen(argv[1], "r");
		if (NULL == input)
			return EXIT_FAILURE;
	} else {
		input = stdin;
	}

    size_t N;
    fscanf(input, "%zu", &N);

    unsigned *A = malloc(sizeof(unsigned) * N);
    for (size_t i=0; i<N; i++) {
        fscanf(input, "%u", A + i);
    }

    size_t P,Q;
    fscanf(input, "%zu %zu", &P, &Q);
    if (P == Q) {
        printf("%zu", P);
        return -P;
    }

    // insert sort cause we only have 100 elements
    for (int i=1; i<N; i++) {
        for (int j=i; j>0; j--) {
            if (A[j] >= A[j - 1]) {
                break;
            }
            unsigned tmp = A[j];
            A[j] = A[j - 1];
            A[j - 1] = tmp;
        }
    }

    int Pi = bin_search(A, N, P);
    int Qi = bin_search(A, N, Q);

    unsigned max;
    size_t R, RC;

    if (Qi >= 0) {
        max = 0;
        R = Q;
    } else {
        Qi = ~Qi;
        if (Qi >= N) {
        	max = Q - A[--Qi];
        	R = Q;
        } else {
        	max = MIN(Q - A[Qi - 1], A[Qi] - Q);
        	R = Q;
        }
    }

    int aPi = Pi < 0 ? ~Pi : Pi;
    aPi = MAX(0, aPi - 1);

    unsigned delta;
    for (int i = Qi; i > aPi; i--) {
        delta = (A[i] - A[i - 1]) >> 1;
        RC = A[i - 1] + delta;

        if (RC > Q || RC < P)
        	continue;
        if (delta >= max) {
            max = delta;
            R = RC;
        }
    }

    if (Pi >= 0) {
    	delta = 0;
    	RC = P;
    } else {
    	Pi = ~Pi;
    	if (0 == Pi) {
    		delta = A[Pi] - P;
    		RC = P;
    	} else {
    		delta = MIN(P - A[Pi - 1], A[Pi] - P);
    		RC = P;
    	}
    }

    if (delta >= max) {
    	max = delta;
    	R = RC;
    }

    printf("%zu", R);

    free(A);

    return 0;
}
