#include <stdio.h>
#include <stdlib.h>

#define MAX(a, b) (((a) < (b)) ? (b) : (a))
#define MIN(a, b) (((a) < (b)) ? (a) : (b))

typedef struct __range {
    unsigned a, b;
    unsigned long k;
} range;

int main(int argc, char* argv[]) {

	FILE* input;

	if (argc > 1) {
		input = fopen(argv[1], "r");
		if (NULL == input)
			return EXIT_FAILURE;
	} else {
		input = stdin;
	}

    size_t N, M;
    fscanf(input, "%zu %zu", &N, &M);

    range* r = malloc(sizeof(range) * M);
    range* pi;
    unsigned *ra_hist = calloc(N, sizeof(unsigned));
    unsigned *rb_hist = calloc(N, sizeof(unsigned));
    range** ra = malloc(sizeof(range *) * M);
    range** rb = malloc(sizeof(range *) * M);

    for(size_t i = 0; i<M; i++) {
        pi = r + i;
        fscanf(input, "%u %u %lu", &pi->a, &pi->b, &pi->k);
        ra_hist[pi->a - 1]++;
        rb_hist[pi->b - 1]++;
    }

    unsigned total_a = 0, total_b = 0;
    for (size_t i=0; i<N; i++) {
        unsigned ia = ra_hist[i];
        unsigned ib = rb_hist[i];
        ra_hist[i] = total_a;
        rb_hist[i] = total_b;
        total_a += ia;
        total_b += ib;
    }

    for(size_t i = 0; i<M; i++) {
        pi = r + i;
        ra[ra_hist[pi->a - 1]++] = pi;
        rb[rb_hist[pi->b - 1]++] = pi;
    }

    unsigned long max = 0L;
    unsigned long sum = 0L;
    unsigned b = 0;
    size_t rai = 0, rbi = 0;
    range *pi_a = ra[rai];
    range *pi_b = ra[rbi];

    while(1) {

        if (pi_a && (b == pi_a->a)) {
            sum += pi_a->k;
            rai++;
        }

        if (b == pi_b->b + 1) {
            sum -= pi_b->k;
            rbi++;
            if (M == rbi)
            	break;
        }

        pi_a = rai < M ? ra[rai] : NULL;
        pi_b = rb[rbi];

        unsigned old_b = b;
        b = MIN(pi_a ? pi_a->a : pi_b->b + 1, pi_b->b + 1);
        if (b != old_b) {
            max = MAX(max, sum);
        }
    }

    printf("%lu", max);

    free(ra);
    free(rb);
    free(ra_hist);
    free(rb_hist);
    free(r);
}
