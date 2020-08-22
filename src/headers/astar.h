#include "queue.h"
#ifndef _ASTAR
#define _ASTAR
typedef struct {
	int x;
	int y;
} pos;

typedef struct {
	int w;
	int h;
} dim;
//Structure "node".
//"pos" is completely optional.
typedef struct node {
	pos pos;
	char blocked;
	struct node * breadcrumb;
	long hscore;
	long gscore;
	long fscore;
	struct node **connected_nodes;
	unsigned num_nodes;
	unsigned qid;
} node;
//As you'd expect, tells if you if pos is within the rectangle 0,0 dim.x,dim.y
char in_bounds(pos pos, dim dim);

//Assuming a 2d grid of dimensions x,y this will generate the node with the proper neighbors
//(Would need some editing if you wanted, say, portals, or pacman logic, etc.)
void gen_node(node** node_map, pos _pos, dim _dim, int h, int g, int f);

//This generates a whole map of nodes using gen_node.
node** allocate_node_map(dim _dim);

//allocate_node_map allocates 3 levels of pointers. One per-node(The list of connected nodes),
//one per-layer(a pointer for every x position of the 2d grid), and finally the pointer to those pointers.
//This de-allocates all that.
void deallocate_node_map(node** node_map, dim _dim);

//For generating the scores between nodes
unsigned get_hscore(node* node1, node* node2);

unsigned get_hscore(node* node1, node* node2);

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
void astar(node *startnode, node *endnode);

#endif