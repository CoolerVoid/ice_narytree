#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

// set DEBUG ON
#define ICETREE_BUGVIEW 1
#define ICETREE_DEBUG(x, s...) do { \
 if (!ICETREE_BUGVIEW) { break; } \
 time_t t = time(NULL); \
 char *d = ctime(&t); \
 fprintf(stderr, "\n---Ice Tree DEBUG-START ---\n\n %.*s %s[%d] %s(): \n", \
 (int)strlen(d) - 1, d, __FILE__, \
 __LINE__, __FUNCTION__); \
 fprintf(stderr, x, ## s); \
 fprintf(stderr,"\n\n---Ice Tree DEBUG-END ---\n"); \
} while (0);

// colors macro
#define RED "\033[22;31m"
#define YELLOW "\033[01;33m"
#define CYAN "\033[22;36m"
#define GREEN "\033[22;32m"
#define LAST "\033[0m"


#define XFREE_ICETREE(x) icetree_xfree((void **)x);

struct node {
    int position;
    void *data;
    struct node *next;
    struct node *child;
};

typedef struct node node;

// for mem use
void icetree_xfree(void **ptr); 
volatile void *icetree_burn_mem(volatile void *, int , size_t );
void *icetree_xmalloc_fatal(size_t ); 
void *icetree_xmalloc (size_t ); 
void traversal_and_destroy(node *,void (*lambda)(void *argvs));

// tree functions
node * new_node(int,void *);
node * append_sibling(node *, int,void *);
node * append_child(node *, int, void *);
node * search_in_tree_per_position(node *, int);
node * insert_child_before(node *,int , int, void *); 
node * insert_sibling_before(node *,int , int, void *);
void interate_traversal_tree(node *,void (*lambda)(void *argvs));
void traversal_tree_dbg(node *);
bool remove_node_childs_by_position(node *, int ,void (*lambda)(void *argvs));
