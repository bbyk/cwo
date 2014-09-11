#include <stdio.h>
#include <stdlib.h>

typedef struct __node node;
struct __node {
	unsigned long v;
    unsigned long occ;
    node* next;
};

typedef struct __ht {
    node **arr;
    size_t cap;
} ht;

typedef struct _fc {
    unsigned long long *v;
    size_t len;
} fc;

ht* new_ht(size_t cap) {
    ht* r = malloc(sizeof(ht));
    r->cap = 1;
    while(r->cap < cap)
        r->cap<<=1;
    r->arr = calloc(r->cap, sizeof(node));
    return r;
}

size_t hash(ht* ht, unsigned long h) {
    h ^= (h >> 20) ^ (h >> 12);
    h ^= (h >> 7) ^ (h >> 4);
    return h % ht->cap;
}

void add(ht* ht, unsigned long value) {
    size_t index = hash(ht, value);
    node* head = ht->arr[index];
    node* n = head;
    while(n) {
        if (value == n->v) {
            n->occ++;
            return;
        }

        n = n->next;
    }

    node* newN = malloc(sizeof(node));
    newN->v = value;
    newN->occ = 1;
    newN->next = head;
    ht->arr[index] = newN;
}

void destruct(ht* ht) {
    for (size_t i = 0; i < ht->cap; i++) {
        node* n = ht->arr[i];
        if (!n)
            continue;
        while(n) {
            node* k = n;
            n = n->next;
            free(k);
        }
    }

    free(ht->arr);
    free(ht);
}

int main(int argc, char *argv[]) {

	FILE* input;

	if (argc > 1) {
		input = fopen(argv[1], "r");
		if (NULL == input)
			return EXIT_FAILURE;
	} else {
		input = stdin;
	}

    size_t t;
    fscanf(input, "%zu", &t);
    while(t--) {
        size_t n;
        unsigned long ni;
        fscanf(input, "%zu", &n);

        ht *ht = new_ht(n);
        while(n--) {
            fscanf(input, "%lu", &ni);
            add(ht, ni);
        }

        unsigned long sum = 0;
        for (size_t i = 0; i < ht->cap; i++) {
            node* nd = ht->arr[i];
            while(nd) {
                if (nd->occ > 1) {
                    sum += nd->occ * (nd->occ - 1);
                }
                nd = nd->next;
            }
        }

        printf("%lu\n", sum);
        destruct(ht);
    }
}
