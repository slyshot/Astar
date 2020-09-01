#include "queue.h"
#ifndef _ASTAR
#define _ASTAR

//qid might seem like a strange one, but what it marks where in the priority queue that particular node is.
typedef struct astar_data {
	char blocked:1;
	char discovered:1;
	struct node * breadcrumb;
	long hscore;
	long gscore;
	long fscore;
	struct node **connected_nodes;
	unsigned num_nodes;
	unsigned qid;
} astar_data;

typedef struct node {
	void* data;
	astar_data a_data;
} node;


//Inputs the startnode and the endnode. After finishing (If successful), the nodes will have breadcrumbs to the startnode.
//If unsuccessful, the endnode(Having never been accessed) will have no change in breacrumb than when it was initialized(If done with calloc, NULL).
void astar(node *end_node, node *start_node, long (hscore)(node*, node*), long (gscore)(node*, node*));
#endif