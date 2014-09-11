/*
 ============================================================================
 Name        : string-similarity.c
 Author      : Boris Byk
 Version     :
 Copyright   : It is free
 Description : String Similarity in C: https://www.hackerrank.com/challenges/string-similarity
 ============================================================================
 */

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

void fail( const char *message );

typedef struct node_struct node;
#define INFINITY INT_MAX
node *node_create( int start, int len );
void node_dispose( node *v );
void node_set_len( node *v, int len );
int node_len( node *v );
node *node_children( node *v );
node *node_next( node *v );
int node_start( node *v );
void node_add_child( node *parent, node *child );
int node_is_leaf( node *v );
node *node_create_leaf( int i );
int node_add_leaf( node *parent, int i );
node *node_split( node *v, int loc );
void node_set_link( node *v, node *link );
node *node_link( node *v );
node *node_parent( node *v );
int node_end( node *v, int max );

typedef struct path_struct path;
path *path_create( int start, int len );
void path_prepend( path *p, int len );
void path_dispose( path *p );
int path_start( path *p );
int path_len( path *p );
char path_first( path *p, char *str );
path *path_next( path *p );


// for storing gamma (walking across the tree)
struct path_struct
{
    int start;
    int len;
};
/**
 * Create a path
 * @param start the start index into str
 * @param len the length of this path
 * @return the complete path
 */
path *path_create( int start, int len )
{
    path *p = calloc( 1, sizeof(path) );
    if ( p == NULL )
        fail("failed to create path\n");
    else
    {
        p->start = start;
        p->len = len;
    }
    return p;
}
/**
 * Add one path to the front of another
 * @param p the current path
 * @param len the length of the prefix
 */
void path_prepend( path *p, int len )
{
    p->start -= len;
    p->len += len;
}
/**
 * Get the first char in the path
 * @param p the path in question
 * @param str the string it refers to
 * @return the first char
 */
char path_first( path *p, char *str )
{
    return str[p->start];
}
/**
 * Dispose of a path cleanly
 * @param p the path to dispose
 */
void path_dispose( path *p )
{
    free( p );
}
/**
 * Access the start field
 * @param p the path in question
 * @return the path start index in str
 */
int path_start( path *p )
{
    return p->start;
}
/**
 * Access the start field
 * @param p the path in question
 * @return the path length
 */
int path_len( path *p )
{
    return p->len;
}


/*
 * Copyright 2013 Desmond Schmidt
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include <stdlib.h>

/**
 * Represent the node structure of a tree but don't build it here
 */
struct node_struct
{
    // index into string: edge leading INTO node
    int start;
    // length of match or INFINITY
    int len;
    // pointer to next sibling
    node *next;
    // pointer to first child
    node *children;
    // suffix link
    node *link;
    // parent of node : needed to implement splits
    node *parent;
};
/**
 * Create a node safely
 * @return the finished node or fail
 */
node *node_create( int start, int len )
{
    node *n = calloc( 1, sizeof(node) );
    if ( n == NULL )
        fail( "couldn't create new node\n" );
    else
    {
        n->start = start;
        n->len = len;
    }
    return n;
}
/**
 * Create a leaf starting at a given offset
 * @param i the offset into the string
 * @return the finished leaf or NULL on failure
 */
node *node_create_leaf( int i )
{
    node *leaf = calloc( 1, sizeof(node) );
    if ( leaf != NULL )
    {
        leaf->start = i;
        leaf->len = INFINITY;
    }
    else
        fail("tree: failed to create leaf\n");
    return leaf;
}
/**
 * Dispose of a node recursively, and thus the entire tree
 * @param v the node to dispose and its children.
 */
void node_dispose( node *v )
{
    node *child = v->children;
    while ( child != NULL )
    {
        node *next = child->next;
        node_dispose( child );
        child = next;
    }
    free( v );
}
/**
 * Add an initially single-char leaf to the tree
 * @param parent the node to hang it off
 * @param i start-index in str of the leaf
 */
int node_add_leaf( node *parent, int i )
{
    int res = 0;
    node *leaf = node_create_leaf( i );
    if ( leaf != NULL )
    {
        node_add_child( parent, leaf );
        res = 1;
    }
    return res;
}
/**
 * Add a child node (can't fail)
 * @param parent the node to add the child to
 * @param child the child to add
 */
void node_add_child( node *parent, node *child )
{
    if ( parent->children == NULL )
        parent->children = child;
    else
    {
        node *temp = parent->children;
        while ( temp->next != NULL )
            temp = temp->next;
        temp->next = child;
    }
    child->parent = parent;
}
/**
 * Is this node the last one in this branch of the tree?
 * @param v the node to test
 * @return 1 if it is else 0
 */
int node_is_leaf( node *v )
{
    return v->children == NULL;
}
/**
 * Split this node's edge by creating a new node in the middle. Remember
 * to preserve the "once a leaf always a leaf" property or f will be wrong.
 * @param v the node in question
 * @param loc the place on the edge after which to split it
 * @return the new internal node
 */
node *node_split( node *v, int loc )
{
    // create front edge leading to internal node u
    int u_len = loc-v->start+1;
    node *u = node_create( v->start, u_len );
    // now shorten the following node v
    if ( !node_is_leaf(v) )
        v->len -= u_len;
    v->start = loc+1;
    // replace v with u in the children of v->parent
    node *child = v->parent->children;
    node *prev = child;
    while ( child != NULL && child != v )
    {
        prev = child;
        child = child->next;
    }
    if ( child == prev )
        v->parent->children = u;
    else
        prev->next = u;
    u->next = child->next;
    v->next = NULL;
    // reset parents
    u->parent = v->parent;
    v->parent = u;
    u->children = v;
    return u;
}
/**
 * Set the node's suffix link
 * @param v the node in question
 * @param link the node sv
 */
void node_set_link( node *v, node *link )
{
    v->link = link;
}
void node_set_len( node *v, int len )
{
    v->len = len;
}
node *node_parent( node *v )
{
    return v->parent;
}
/**
 * Get the suffix link
 * @param v the node to get the link of
 * @return the node sv
 */
node *node_link( node *v )
{
    return v->link;
}
//accessors
int node_len( node *v )
{
    return v->len;
}
int node_start( node *v )
{
    return v->start;
}
node *node_next( node *v )
{
    return v->next;
}
node *node_children( node *v )
{
    return v->children;
}
int node_end( node *v, int max )
{
    if ( node_len(v) == INFINITY )
        return max;
    else
        return v->start+v->len-1;
}

void fail( const char *message )
{
    fprintf(stderr,"%s",message);
    exit( 0 );
}


#define TEST_STRING "the quick brown fox jumps over the lazy dog."
typedef struct pos_struct pos;
// describes a character-position in the tree
struct pos_struct
{
    node *v;
    int loc;
};
// required globals that could be instance vars in an object
// the actual string we are building a tree of
char *str = TEST_STRING;
// length of str
int slen;
// end of current leaves
int e = 0;
// the root of the tree
static node *root=NULL;
// the first leaf with the longest suffix
static node *f=NULL;
// the last created internal node
static node *current=NULL;
// the last position of str[j..i-1] used in the extension algorithm
static pos last;
// location of last suffix str[j..i] inserted by an extension
static pos old_beta;
// the last value of j in the previous extension
static int old_j = 0;
/**
 * Find a child of an internal node starting with a character
 * @param v the internal node
 * @param c the char to look for
 * @return the child node
 */
static node *find_child( node *v, char c )
{
    v = node_children(v);
    while ( v != NULL && str[node_start(v)] != c )
       v = node_next(v);
    return v;
}
#ifdef DEBUG
#include "debug"
#endif
/**
 * Create a position safely
 * @return the finished pos or fail
 */
static pos *pos_create()
{
    pos *p = calloc( 1, sizeof(pos) );
    if ( p == NULL )
        fail( "couldn't create new pos\n" );
    return p;
}
/**
 * Walk down the tree from the given node following the given path
 * @param v the node to start from its children
 * @param p the path to walk down and then free
 * @return a position corresponding to end
 */
static pos *walk_down( node *v, path *p )
{
    pos *q=NULL;
    int start = path_start( p );
    int len = path_len( p );
    v = find_child( v, str[start] );
    while ( len > 0 )
    {
        if ( len <= node_len(v) )
        {
            q = pos_create();
            q->loc = node_start(v)+len-1;
            q->v = v;
            break;
        }
        else
        {
            start += node_len(v);
            len -= node_len(v);
            v = find_child( v, str[start] );
        }
    }
    path_dispose( p );
    return q;
}
/**
 * Find a location of the suffix in the tree.
 * @param j the extension number counting from 0
 * @param i the current phase - 1
 * @return the position (combined node and edge-offset)
 */
static pos *find_beta( int j, int i )
{
    pos *p;
    if ( old_j > 0 && old_j == j )
    {
        p = pos_create();
        p->loc = old_beta.loc;
        p->v = old_beta.v;
    }
    else if ( j>i )  // empty string
    {
        p = pos_create();
        p->loc = 0;
        p->v = root;
    }
    else if ( j==0 )    // entire string
    {
        p = pos_create();
        p->loc = i;
        p->v = f;
    }
    else // walk across tree
    {
        node *v = last.v;
        int len = last.loc-node_start(last.v)+1;
        path *q = path_create( node_start(v), len );
        v = node_parent( v );
        while ( v != root && node_link(v)==NULL )
        {
            path_prepend( q, node_len(v) );
            v = node_parent( v );
        }
        if ( v != root )
        {
            v = node_link( v );
            p = walk_down( v, q );
        }
        else
        {
            path_dispose( q );
            p = walk_down( root, path_create(j,i-j+1) );
        }
    }
    last = *p;
    return p;
}
/**
 * Does the position continue with the given character?
 * @param p a position in the tree.
 * @param c the character to test for in the next position
 * @return 1 if it does else 0
 */
static int continues( pos *p, char c )
{
    if ( node_end(p->v,e) > p->loc )
        return str[p->loc+1] == c;
    else
        return find_child(p->v,c) != NULL;
}
/**
 * If current is set set its link to point to the next node, then clear it
 * @param v the link to point current to
 */
static void update_current_link( node *v )
{
    if ( current != NULL )
    {
        node_set_link( current, v );
#ifdef DEBUG
        verify_link( current );
#endif
        current = NULL;
    }
}
/**
 * Are we at the end of this edge?
 * @param p the position to test
 * @return 1 if it is, else 0
 */
static int pos_at_edge_end( pos *p )
{
    return p->loc==node_end(p->v,e);
}
/**
 * Record the position where the latest suffix was inserted
 * @param p the position of j..i-1.
 * @param i the desired index of the extra char
 */
static void update_old_beta( pos *p, int i )
{
    if ( node_end(p->v,e) > p->loc )
    {
        old_beta.v = p->v;
        old_beta.loc = p->loc+1;
    }
    else
    {
        node *u = find_child( p->v, str[i] );
        old_beta.v = u;
        old_beta.loc = node_start( u );
    }
}
/**
 * Extend the implicit suffix tree by adding one suffix of the current prefix
 * @param j the offset into str of the suffix's start
 * @param i the offset into str at the end of the current prefix
 * @return 1 if the phase continues else 0
 */
static int extension( int j, int i )
{
    int res = 1;
    pos *p = find_beta( j, i-1 );
    // rule 1 (once a leaf always a leaf)
    if ( node_is_leaf(p->v) && pos_at_edge_end(p) )
        res = 1;
    // rule 2
    else if ( !continues(p,str[i]) )
    {
        //printf("applying rule 2 at j=%d for phase %d\n",j,i);
        node *leaf = node_create_leaf( i );
        if ( p->v==root || pos_at_edge_end(p) )
        {
            node_add_child( p->v, leaf );
            update_current_link( p->v );
        }
        else
        {
            node *u = node_split( p->v, p->loc );
            update_current_link( u );
            if ( i-j==1 )
            {
                node_set_link( u, root );
#ifdef DEBUG
                verify_link( current );
#endif
            }
            else
                current = u;
            node_add_child( u, leaf );
        }
        update_old_beta( p, i );
    }
    // rule 3
    else
    {
        //printf("applying rule 3 at j=%d for phase %d\n",j,i);
        update_current_link( p->v );
        update_old_beta( p, i );
        res = 0;
    }
    free( p );
    return res;
}
/**
 * Process the prefix of str ending in the given offset
 * @param i the inclusive end-offset of the prefix
 */
static void phase( int i )
{
    int j;
    current = NULL;
    for ( j=old_j;j<=i;j++ )
        if ( !extension(j,i) )
            break;
    // remember number of last extension for next phase
    old_j = (j>i)?i:j;
    // update all leaf ends
    e++;
    //print_tree( root );
}
/**
 * Set the length of each leaf to e recursively
 * @param v the node in question
 */
static void set_e( node *v )
{
    if ( node_is_leaf(v) )
    {
        node_set_len( v, e-node_start(v)+1 );
    }
    node *u = node_children( v );
    while ( u != NULL )
    {
        set_e( u );
        u = node_next( u );
    }
}
/**
 * Build a tree using a given string
 * @param txt the text to build it from
 * @return the finished tree's root
 */
node *build_tree( char *txt )
{
    // init globals
    e = 0;
    root=NULL;
    f=NULL;
    current=NULL;
    memset( &last, 0, sizeof(pos) );
    memset( &old_beta, 0, sizeof(pos) );
    old_j = 0;
    str = txt;
    slen = strlen(txt);
    // actually build the tree
    root = node_create( 0, 0 );
    if ( root != NULL )
    {
        f = node_create_leaf( 0 );
        if ( f != NULL )
        {
            int i;
            node_add_child( root, f );
            for ( i=1; i<=slen; i++ )
                phase(i);
            set_e( root );
        }
    }
    return root;
}


typedef struct __sLINE {
	char* p;
	size_t len;
} LINE;

int node_num_children(node* sibling) {
	int result = 0;

	while(sibling != NULL) {
		if (node_is_leaf(sibling)) {
			result++;
		} else {
			result += node_num_children(node_children(sibling));
		}

		sibling = node_next(sibling);
	}

	return result;
}

long calc_similars(const char* line) {
	root = build_tree( line );
	int total = 0, multiple = 0, pplus = 0;
	if ( root != NULL )
	{
		node *u = node_children(root);
		const char *p = line;
		node *next_u = NULL;

		while(*p) {
			next_u = NULL;
			while(u != NULL) {
				int nstart = node_start(u);

				if (line[nstart] == *p) {
					int end = node_end(u,e);
					pplus = end - nstart + (line[end] == 0 ? 0 : 1);
					next_u = node_children(u);
				} else if (node_is_leaf(u)){
					multiple++;
				} else {
					multiple += node_num_children(node_children(u));
				}
				u = node_next(u);
			}

			total += (p - line) * multiple;
			p += pplus;
			u = next_u;
			multiple = 0;
		}

		total += (p - line);

		node_dispose( root );
	}
	return total;
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

	int T;
	LINE line;
	line.p = NULL;
	line.len = 0;

	if (getline(&line.p, &line.len, input) == -1) {
		if (line.p != NULL)
			free(line.p);
		return EXIT_FAILURE;
	}
	T = atoi(line.p);
	for (int i = 0; i < T; i++) {
		int readb;
		if ((readb = getline(&line.p, &line.len, input)) == -1) {
			free(line.p);
			return EXIT_FAILURE;
		}

		if (line.p[readb - 1] == '\n')
			line.p[readb - 1] = '\0';
		printf("%li\n", calc_similars(line.p));
	}

	if (stdin != input)
		fclose(input);
	free(line.p);

	return EXIT_SUCCESS;
}
