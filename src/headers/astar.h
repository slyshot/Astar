#include "queue.h"
#ifndef _ASTAR
#define _ASTAR
//Structure "node".
//"pos" is completely optional.
typedef struct astar_data {
	char blocked;
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


////The comparator is a function which inputs the queue, two indexes of it, and arbitrary data you bring through all of the priority queue functions.
//It returns the index with the lower fscore.
_UL comparator(queue _queue, _UL index1, _UL index2, void* nothing);
/*
If you are to use the astar function I have supplied, this is the way the comparator will look:
_UL comparator(queue _queue, _UL index1, _UL index2, void* nothing) {
	return ((node*)_queue[index1])->fscore < ((node*)_queue[index2])->fscore ? index1 : index2;
}
*/

//Transform switches two elements, to be used like the comparator internally in the queue's.
//This may be used to keep track of indicies so as to be able to sift_up when an fscore gets updated.

void transform(queue _queue, _UL index1, _UL index2, void* map);

//Inputs the startnode and the endnode. After finishing (If successful), the nodes will have breadcrumbs to the startnode.
//If unsuccessful, the endnode(Having never been accessed) will have no breadcrumb.
// void astar(node *startnode, node *endnode);
void astar(node *end_node, node *start_node, long (hscore)(node*, node*), long (gscore)(node*, node*));
#endif