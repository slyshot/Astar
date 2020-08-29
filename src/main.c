#include "astar.h"
#include "stdlib.h"
#include "stdio.h"
//This is a 2d-grid implementation.
typedef struct {
	int x;
	int y;
} pos;

typedef struct {
	int w;
	int h;
} dim;

char in_bounds(pos pos, dim dim) {
	return pos.x >= 0 && pos.x < dim.w && pos.y >= 0 && pos.y < dim.h;
}

//This 'initializes' a node, connecting it to adjacent nodes which are within bounds
void gen_node(node** node_map, pos _pos, dim _dim, int h, int g, int f) {
	node **connected_nodes = malloc(sizeof(node*)*8);
	//these are all of the positions adjacent to 0,0
	pos adj[8] = {	{.x = -1,.y = -1},
					{.x = 0, .y = -1},
					{.x = 1, .y = -1},
					{.x = -1,.y = 0},
					{.x = 1, .y = 0},
					{.x = -1,.y = 1},
					{.x = 0, .y = 1},
					{.x = 1, .y = 1},
				};
	unsigned num_nodes = 0;
	for (int i = 0; i < 8; i++) {
		if (in_bounds((pos){.x = (_pos.x + adj[i].x),.y = (_pos.y + adj[i].y)}, _dim)) {
			connected_nodes[num_nodes++] = &node_map[_pos.x + adj[i].x][_pos.y + adj[i].y];
		}
	}
	pos* position = malloc(sizeof(pos));
	position->x = _pos.x;
	position->y = _pos.y;
	node_map[_pos.x][_pos.y] = (node){	.data = position, \
										.a_data.hscore = h, \
										.a_data.gscore = g, \
										.a_data.fscore = f, \
										.a_data.connected_nodes = connected_nodes, \
										.a_data.num_nodes = num_nodes, \
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
			free(node_map[x][y].data);
			free(node_map[x][y].a_data.connected_nodes);
		}
		free(node_map[x]);
	}
	free(node_map);
}

long get_hscore(node* node1, node* node2) {
	pos pos1, pos2;
	pos1 = *(pos*)node1->data;
	pos2 = *(pos*)node2->data;
	int xdiff = (pos1.x - pos2.x);
	xdiff *= xdiff < 0 ? -1 : 1;
	int ydiff = (pos1.y - pos2.y);
	ydiff *= ydiff < 0 ? -1 : 1;
	int greater, lesser;
	xdiff > ydiff ? (greater = xdiff, lesser = ydiff) : (greater = ydiff, lesser=xdiff);
	return (lesser)*14 + (greater - lesser)*10;
}
long get_gscore(node* node1, node* node2) {
	return get_hscore(node1,node2);
}




int main(int argc, char const *argv[]) {
	//A little test case.
	dim size = (dim){100,100};
	node** map = allocate_node_map(size);
	int blocked[][2] = {{0,1},{1,1},{2,1},{3,1},{5,0},{4,2}};
	node * startnode = &map[0][0]; 
	node * endnode = &map[9][9]; 
	for (unsigned long i = 0; i < sizeof(blocked)/sizeof(int[2]); i++) {
		map[blocked[i][0]][blocked[i][1]].a_data.blocked = 1;
	}
	astar(startnode,endnode,get_hscore,get_gscore);
	node* cur_breadcrumb = startnode;
	while (cur_breadcrumb != NULL) {
		printf("%d,%d\n",(*(pos*)cur_breadcrumb->data).x,(*(pos*)cur_breadcrumb->data).y);
		cur_breadcrumb = cur_breadcrumb->a_data.breadcrumb;
	}

	deallocate_node_map(map, size);
	return 0;
}