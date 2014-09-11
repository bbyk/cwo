#include <stdio.h>
#include <stdlib.h>

#define MAX 100
#define MAX_S 12

typedef struct __pair {
    int key;
    char value[MAX_S];
} PAIR;

int ht[MAX];

int main(int argc, const char * argv[]) {
	FILE* input;

	if (argc > 1) {
		input = fopen(argv[1], "r");
		if (NULL == input)
			return EXIT_FAILURE;
	} else {
		input = stdin;
	}

    int n;

    fscanf(input, "%d", &n);

    PAIR** unsorted = malloc(n * sizeof(PAIR));
    PAIR** sorted = malloc(n * sizeof(PAIR));

    for (int i = 0; i < n; i++) {
        int fh = n >> 1;
        PAIR *p = malloc(sizeof(PAIR));
        fscanf(input, "%d %11s", &p->key, p->value);
        if (i < fh) {
            p->value[0] = '-';
            p->value[1] = 0;
        }
        unsorted[i] = p;
        ht[p->key]++;
    }

    for (int i = 0; i < MAX; i++) {
        if (i)
            ht[i] += ht[i - 1];
    }

    for (int i = n - 1; i >= 0; i--) {
        int sorted_pos = ht[unsorted[i]->key] - 1;
        sorted[sorted_pos] = unsorted[i];
        ht[unsorted[i]->key]--;
    }

    for (int i = 0; i < n; i++) {
        printf("%s ", sorted[i]->value);
    }

    return 0;
}
