#include "astar.h"
#include "stdlib.h"
#include "stdio.h"

int main(int argc, char const *argv[]) {
	//A little test case.
	dim size = (dim){10,10};
	node** map = allocate_node_map(size);
	int blocked[][2] = {{0,1},{1,1},{2,1},{3,1},{5,0},{4,2}};
	node * startnode = &map[0][0]; 
	node * endnode = &map[9][9]; 
	for (int i = 0; i < sizeof(blocked)/sizeof(int[2]); i++) {
		map[blocked[i][0]][blocked[i][1]].blocked = 1;
	}
	astar(startnode,endnode);
	node* cur_breadcrumb = startnode;
	while (cur_breadcrumb != NULL) {
		printf("%d,%d\n",cur_breadcrumb->pos.x,cur_breadcrumb->pos.y);
		cur_breadcrumb = cur_breadcrumb->breadcrumb;
	}

	deallocate_node_map(map, size);
	return 0;
}