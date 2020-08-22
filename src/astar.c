#include "astar.h"
#include "stdlib.h"
char in_bounds(pos pos, dim dim) {
	return pos.x >= 0 && pos.x < dim.w && pos.y >= 0 && pos.y < dim.h;
}
void gen_node(node** node_map, pos _pos, dim _dim, int h, int g, int f) {
	node **connected_nodes = malloc(sizeof(node*)*8);
	//This all of the positions adjacent to 0,0
	pos adj[8] = {{.x = 0,.y = -1},{.x = 0,.y = 1},{.x = -1,.y = 0},{.x = 1,.y = 0},{.x = -1,.y = -1},{.x = 1,.y = -1},{.x = -1,.y = 1},{.x = 1,.y = 1}};
	unsigned num_nodes = 0;
	for (int i = 0; i < 8; i++) {
		if (in_bounds((pos){.x = (_pos.x + adj[i].x),.y = (_pos.y + adj[i].y)}, _dim)) {
			connected_nodes[num_nodes++] = &node_map[_pos.x + adj[i].x][_pos.y + adj[i].y];
		}
	}
	node_map[_pos.x][_pos.y] = (node){	.pos = _pos, \
										.hscore = h, \
										.gscore = g, \
										.fscore = f, \
										.connected_nodes = (node**)connected_nodes, \
										.num_nodes = num_nodes, \
									};
}

node** allocate_node_map(dim _dim) {
	node** node_map = malloc(sizeof(node*)*_dim.w);
	for (int x = 0; x < _dim.w; x++) {
		node_map[x] = malloc(sizeof(node)*_dim.h);
	}
	for (int y = 0; y < _dim.h; y++) {
		for (int x = 0; x < _dim.w; x++) {
				gen_node(node_map, (pos){x,y},_dim,0,0,0);
		}
	}
	return node_map;
}

void deallocate_node_map(node** node_map, dim _dim) {
	for (int x = 0; x < _dim.w; x++) {
		for (int y = 0; y < _dim.h; y++) {
			free(node_map[x][y].connected_nodes);
		}
		free(node_map[x]);
	}
	free(node_map);
}

unsigned get_hscore(node* node1, node* node2) {
	pos pos1, pos2;
	pos1 = node1->pos;
	pos2 = node2->pos;
	int xdiff = (pos1.x - pos2.x);
	xdiff *= xdiff < 0 ? -1 : 1;
	int ydiff = (pos1.y - pos2.y);
	ydiff *= ydiff < 0 ? -1 : 1;
	int greater, lesser;
	xdiff > ydiff ? (greater = xdiff, lesser = ydiff) : (greater = ydiff, lesser=xdiff);
	return (lesser)*14 + (greater - lesser)*10;
}
unsigned get_gscore(node* node1, node* node2) {
	return get_hscore(node1,node2);
}

_UL comparator(queue _queue, _UL index1, _UL index2, void* nothing) {
	return ((node*)_queue[index1])->fscore < ((node*)_queue[index2])->fscore ? index1 : index2;
}
void transform(queue _queue, _UL index1, _UL index2, void* nothing) {
	queue_element temp = _queue[index2];
	_queue[index2] = _queue[index1];
	_queue[index1] = temp;
	((node*)_queue[index1])->qid = index1;
	((node*)_queue[index2])->qid = index2;
}
typedef queue_element queue_node;

void astar(node *end_node, node *start_node) {
	unsigned pqueue_max_len = 10;
	unsigned pqueue_len = 0;
	queue pqueue = calloc(sizeof(node*),pqueue_max_len);
	node * cur_node = start_node;
	cur_node->hscore = get_hscore(cur_node, end_node);
	cur_node->fscore = cur_node->gscore+cur_node->hscore;
	cur_node->breadcrumb = NULL;
	cur_node->blocked = 1;
	push(pqueue, cur_node, pqueue_len++, transform,NULL,comparator, NULL);

	node * neighbor;
	while (pqueue_len > 0 && cur_node != end_node) {
		cur_node = pop(pqueue, pqueue_len--, transform, NULL, comparator, NULL);
		for (unsigned i = 0; i < cur_node->num_nodes; i++) {
			neighbor = cur_node->connected_nodes[i];
			if (neighbor->blocked) continue;
			int tenative_gscore = cur_node->gscore + get_gscore(cur_node,neighbor);
			if (neighbor->gscore == 0) {
				neighbor->hscore = get_hscore(neighbor, end_node);
				neighbor->gscore = tenative_gscore;
				neighbor->fscore = neighbor->gscore+neighbor->hscore;
				neighbor->breadcrumb = cur_node;
				push(pqueue, neighbor, pqueue_len++, transform, NULL, comparator, NULL);
			} else if (tenative_gscore < neighbor->gscore) {
				neighbor->gscore = tenative_gscore;
				neighbor->fscore = neighbor->gscore+neighbor->hscore;
				neighbor->breadcrumb = cur_node;
				sift_up(neighbor->qid, pqueue, transform, NULL, comparator, NULL);
			}
			if (pqueue_len >= pqueue_max_len) {
				pqueue_max_len *= 2;
				pqueue = realloc(pqueue,sizeof(node*)*pqueue_max_len);
			}
		}
		cur_node->blocked = 1;
	}
	free(pqueue);
}