#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

const unsigned PRIME = 1000000007;

unsigned min(unsigned a, unsigned b) {
    return a < b ? a : b;
}

typedef struct __node node;

// a delegate we use for polymorphism
typedef unsigned count_cb(node *, unsigned l);

struct __node {
    node *l, *r;
    count_cb *call;
    unsigned min_size;
    bool fix_size;
};

node *parse_node(char const **caret);

unsigned one_letter_re(node *np, const unsigned l) {
    return l > 1 ? 0 : 1;
}

unsigned or_re(node *np /* node pointer */, const unsigned l) {
    unsigned long sum = 0;
    sum = (sum + np->l->call(np->l, l)) % PRIME;
    sum = (sum + np->r->call(np->l, l)) % PRIME;
    return (unsigned) sum;
}

unsigned and_re(node *np, const unsigned l) {
    unsigned min_size = np->l->min_size + np->r->min_size;

    if (min_size > l)
        return 0;
    else if (l == min_size) {
        return 1;
    } else if (np->l->fix_size && np->r->fix_size) {
        return 0;
    } else {
        unsigned long sum = 0;
        sum = (sum + (np->r->min_size ? l / np->r->min_size : 0) * np->l->call(np->l, l - np->r->min_size)) % PRIME;
        sum = (sum + (np->l->min_size ? l / np->l->min_size : 0) * np->r->call(np->r, l - np->l->min_size)) % PRIME;
        return (unsigned) sum;
    }
}

unsigned multi_re(node *np, const unsigned l) {
    return np->l->min_size == 1 ? 1 : np->l->min_size * l;
}

node *parse(const char *line, unsigned const *l) {
    const char *c = line;
    while (*c != ' ')
        c++;
    sscanf(c, "%u", l);

    return parse_node(&line);
}

/**
* post-order traversal to free the memory.
*/
void delete_node(node *pn) {
    if (pn->l)
        delete_node(pn->l);
    if (pn->r)
        delete_node(pn->r);
    free(pn);
}

/**
* Uses reader pattern - a token is read moves caret after the token.
*/
node *parse_node(char const **caret) {
    node *rt = NULL;
    char c = **caret;

    if ('a' == c || 'b' == c) {
        rt = malloc(sizeof(node));
        rt->call = &one_letter_re;
        rt->min_size = 1;
        rt->r = rt->l = NULL;
        rt->fix_size = true;
        (*caret)++;
    } else if ('(' == c) {
        rt = malloc(sizeof(node));
        (*caret)++; // move beyond '('
        rt->l = parse_node(caret);
        c = **caret;
        if ('|' == c) {
            rt->call = &or_re;
            (*caret)++;
            rt->r = parse_node(caret);
            rt->min_size = min(rt->l->min_size, rt->r->min_size);
            rt->fix_size = rt->l->fix_size & rt->r->fix_size;
        } else if ('*' == c) {
            rt->call = &multi_re;
            rt->min_size = 0;
            rt->fix_size = false;
            (*caret)++;
            rt->r = NULL;
        } else {
            rt->call = &and_re;
            rt->r = parse_node(caret);
            rt->min_size = rt->l->min_size + rt->r->min_size;
            rt->fix_size = rt->l->fix_size & rt->r->fix_size;
        }

        // for the closing ')'
        (*caret)++;
    }
    return rt;
}

int main(int argc, const char *argv[]) {
    FILE *fp;
    if (argc > 1) {
        fp = fopen(argv[1], "r");
    } else {
        fp = stdin;
    }

    char *line = NULL;
    size_t len = 0;
    unsigned T;

    getline(&line, &len, fp);
    sscanf(line, "%u", &T);

    while (T--) {
        getline(&line, &len, fp);
        unsigned L;
        node *pn = parse(line, &L);

        printf("%u\n", pn->call(pn, L));

        delete_node(pn);
    }

    free(line);
    if (fp != stdin)
        fclose(fp);

    return 0;
}