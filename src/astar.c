#include "astar.h"
#include "stdlib.h"


_UL comparator(queue _queue, _UL index1, _UL index2, void* nothing) {
	return ((node*)_queue[index1])->a_data.fscore < ((node*)_queue[index2])->a_data.fscore ? index1 : index2;
}
void transform(queue _queue, _UL index1, _UL index2, void* nothing) {
	queue_element temp = _queue[index2];
	_queue[index2] = _queue[index1];
	_queue[index1] = temp;
	((node*)_queue[index1])->a_data.qid = index1;
	((node*)_queue[index2])->a_data.qid = index2;
}
void astar(node *end_node, node *start_node, long (hscore)(node*, node*), long (gscore)(node*, node*)) {
	unsigned pqueue_max_len = 10;
	unsigned pqueue_len = 0;
	queue pqueue = calloc(sizeof(node*),pqueue_max_len);
	node * cur_node = start_node;
	astar_data * cdata = &cur_node->a_data;
	cdata->hscore = hscore(cur_node, end_node);
	cdata->fscore = cdata->gscore+cdata->hscore;
	cdata->breadcrumb = NULL;
	cdata->blocked = 1;
	push(pqueue, cur_node, pqueue_len++, transform,NULL,comparator, NULL);

	node * neighbor;
	while (pqueue_len > 0 && cur_node != end_node) {
		cur_node = pop(pqueue, pqueue_len--, transform, NULL, comparator, NULL);
		astar_data * cdata = &cur_node->a_data;
		for (unsigned i = 0; i < cur_node->a_data.num_nodes; i++) {
			neighbor = cur_node->a_data.connected_nodes[i];
			astar_data *ndata = &neighbor->a_data;
			if (neighbor->a_data.blocked) continue;
			int tenative_gscore = cur_node->a_data.gscore + gscore(cur_node,neighbor);
			if (ndata->gscore == 0) {
				ndata->hscore = hscore(neighbor, end_node);
				ndata->gscore = tenative_gscore;
				ndata->fscore = ndata->gscore+ndata->hscore;
				ndata->breadcrumb = cur_node;
				push(pqueue, neighbor, pqueue_len++, transform, NULL, comparator, NULL);
			} else if (tenative_gscore < ndata->gscore) {
				ndata->gscore = tenative_gscore;
				ndata->fscore = ndata->gscore+ndata->hscore;
				ndata->breadcrumb = cur_node;
				sift_up(ndata->qid, pqueue, transform, NULL, comparator, NULL);
			}
			if (pqueue_len >= pqueue_max_len) {
				pqueue_max_len *= 2;
				pqueue = realloc(pqueue,sizeof(node*)*pqueue_max_len);
			}
		}
		cdata->blocked = 1;
	}
	free(pqueue);
}