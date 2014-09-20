#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

const unsigned PRIME = 1000000007;

/* MEMORY POOL DATA/OPERATIONS */

const unsigned MP_CAPACITY = 60 * 1024 * 1024; // 60 MB
const unsigned MAX_PATTERN_LENGTH = 100;

typedef struct __mpool {
    void *head;
    void *cur;
    void *cap;
} mpool;

mpool *mp_new(size_t mp_capacity) {
    mpool *p = malloc(sizeof(mpool));
    p->head = malloc(mp_capacity);
    p->cap = p->head + mp_capacity;
    p->cur = p->head;
    return p;
}

void *mp_alloc(mpool *p, size_t size) {
    if ((p->cur + size) > p->cap)
        return NULL;
    void *r = p->cur;
    p->cur += size;
    return r;
}

void mp_reset(mpool *p) {
    p->cur = p->head;
}

void mp_delete(mpool *p) {
    free(p->head);
    free(p);
}

mpool *pool;

/* END MEMORY POOL DATA/OPERATIONS */

unsigned min(unsigned a, unsigned b) {
    return a < b ? a : b;
}

typedef struct __transition {
    char c;
    unsigned sid;
} transition;

typedef struct __nfa nfa;

typedef struct __state {
    unsigned sid;
    transition trans[3];
    unsigned t_id;
} state;

// a delegate we use for polymorphism
typedef unsigned count_cb(nfa *, unsigned l);

struct __nfa {
    unsigned l_sid;
    unsigned r_sid;
    state states[MAX_PATTERN_LENGTH * 10];
    unsigned st_id;
};

typedef struct __parser_ctx {
    nfa *pnfa;
    unsigned sid_stack[MAX_PATTERN_LENGTH];
    unsigned stack_id;
    char const **caret;
} parser_ctx;

unsigned newState(nfa *pnfa) {
    pnfa->states[pnfa->st_id].t_id = 0;
    pnfa->states[pnfa->st_id].sid = pnfa->st_id;
    return pnfa->st_id++;
}

void parse_node(parser_ctx *);

nfa *regex_to_nfa(const char *line, unsigned *l) {
    const char *c = line;
    while (*c != ' ')
        c++;
    sscanf(c, "%u", l);

    parser_ctx *pctx = mp_alloc(pool, sizeof(parser_ctx));
    pctx->caret = &line;
    pctx->stack_id = 0;
    pctx->pnfa = mp_alloc(pool, sizeof(nfa));
    pctx->pnfa->st_id = 0;

    parse_node(pctx);

    // pop last two items from the stack as initial and acceptance state ids.
    pctx->pnfa->r_sid = pctx->sid_stack[--pctx->stack_id];
    pctx->pnfa->l_sid = pctx->sid_stack[--pctx->stack_id];

    return pctx->pnfa;
}

/**
* Uses reader pattern - a token is read moves caret after the token.
* http://en.wikipedia.org/wiki/Thompson's_construction_algorithm
*/
void parse_node(parser_ctx *pctx) {
    char c = **pctx->caret;
    unsigned l, r;
    state *lstate, *pop_state;

    if ('a' == c || 'b' == c) {
        l = newState(pctx->pnfa);
        r = newState(pctx->pnfa);
        lstate = &pctx->pnfa->states[l];
        lstate->trans[lstate->t_id].c = c;
        lstate->trans[lstate->t_id++].sid = r;
        (*pctx->caret)++;
    } else if ('(' == c) {
        (*pctx->caret)++; // move beyond '('
        parse_node(pctx);
        c = **pctx->caret;
        if ('|' == c) {
            (*pctx->caret)++;
            parse_node(pctx);

            // connect the left state to the popped state on the stack.
            l = newState(pctx->pnfa);
            lstate = &pctx->pnfa->states[l];
            lstate->trans[lstate->t_id].c = 'e';
            lstate->trans[lstate->t_id++].sid = pctx->sid_stack[--pctx->stack_id];

            // connect the popped state to the right state
            r = newState(pctx->pnfa);
            pop_state = &pctx->pnfa->states[pctx->sid_stack[--pctx->stack_id]];
            pop_state->trans[pop_state->t_id].c = 'e';
            pop_state->trans[pop_state->t_id++].sid = r;

            // connect the left state to the popped state on the stack.
            lstate->trans[lstate->t_id].c = 'e';
            lstate->trans[lstate->t_id++].sid = pctx->sid_stack[--pctx->stack_id];

            // connect the popped state to the right state
            pop_state = &pctx->pnfa->states[pctx->sid_stack[--pctx->stack_id]];
            pop_state->trans[pop_state->t_id].c = 'e';
            pop_state->trans[pop_state->t_id++].sid = r;
        } else if ('*' == c) {
            (*pctx->caret)++;
            l = newState(pctx->pnfa);
            lstate = &pctx->pnfa->states[l];
            lstate->trans[lstate->t_id].c = 'e';
            unsigned pop_r = pctx->sid_stack[--pctx->stack_id];
            lstate->trans[lstate->t_id++].sid = pop_r;

            r = newState(pctx->pnfa);

            lstate->trans[lstate->t_id].c = 'e';
            lstate->trans[lstate->t_id++].sid = r;

            pop_state = &pctx->pnfa->states[pctx->sid_stack[--pctx->stack_id]];
            pop_state->trans[pop_state->t_id].c = 'e';
            pop_state->trans[pop_state->t_id++].sid = r;

            pop_state->trans[pop_state->t_id].c = 'e';
            pop_state->trans[pop_state->t_id++].sid = pop_r;
        } else {
            parse_node(pctx);

            // pop left and right state of first pair on the stack
            l = pctx->sid_stack[--pctx->stack_id];
            pop_state = &pctx->pnfa->states[pctx->sid_stack[--pctx->stack_id]];

            // pop left state of the second pair on the stack and connect with an epsilon
            r = pctx->sid_stack[--pctx->stack_id];
            pop_state->trans[pop_state->t_id].c = 'e';
            pop_state->trans[pop_state->t_id++].sid = r;

            // pop real right state of the second pair.
            r = pctx->sid_stack[--pctx->stack_id];
        }

        // for the closing ')'
        (*pctx->caret)++;
    }

    // put new l and r back on the stack
    pctx->sid_stack[pctx->stack_id++] = l;

    pctx->sid_stack[pctx->stack_id++] = r;
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

    pool = mp_new(MP_CAPACITY);

    while (T--) {
        getline(&line, &len, fp);
        unsigned L;
        nfa *pn = regex_to_nfa(line, &L);

//        printf("%u\n", pn->call(pn, L));

        mp_reset(pool);
    }

    mp_delete(pool);

    free(line);
    if (fp != stdin)
        fclose(fp);

    return 0;
}