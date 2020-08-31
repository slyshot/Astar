#include "queue.h"

void sift_down(_UL index, queue _queue, _UL queue_len ,_switch sw, void *sw_a, _compare comp, void *c_a) {
	_UL cur_index = index;
	while (1) {
		_UL child1 = cur_index*2 + 1;
		if (child1 >= queue_len) break;
		_UL child2 = child1 + 1;
		_UL best_child_index = child2 < queue_len ? comp(_queue,child1,child2,c_a) : child1;
		if (comp(_queue, best_child_index, cur_index,c_a) == cur_index) break;
		sw(_queue,best_child_index,cur_index,sw_a);
		cur_index = best_child_index;
	}
}
queue_element pop(queue _queue, _UL queue_len, _switch sw, void *sw_a, _compare comp, void *c_a) {
	queue_element best_element = _queue[0];
	_queue[0] = _queue[queue_len - 1];
	sift_down(0, _queue, queue_len - 1,sw,sw_a,comp,c_a);
	return best_element;
}
void heapify(queue _queue, _UL queue_len, void (*sw)(queue,_UL, _UL, void*), void *sw_a, _compare comp, void *c_a) {
	for (int i = (queue_len - 2)/2; i >= 0; i-- ) sift_down(i,_queue,queue_len,sw, sw_a,comp, c_a);
}
void sift_up(_UL init_index, queue _queue, _switch sw,void *sw_a, _compare comp, void *c_a) {
	for (_UL index = init_index; index > 0; index = (index-1)/2) {
		if (comp(_queue, (index - 1)/2,index, c_a) == index) sw(_queue,(index - 1)/2,index, sw_a);		
	}
}
void push(queue _queue, _UL index, queue_element item, _switch sw,void *sw_a, _compare comp, void *c_a) {
	_queue[index] = item;
	sift_up(index,_queue, sw,sw_a,comp,c_a);
}
