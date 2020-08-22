#include "queue.h"

void sift_down(_UL index, queue _queue, _UL queue_len ,void (*sw)(queue, _UL, _UL, void*), void *sw_a, _UL (*comp)(queue, _UL, _UL, void*), void *c_a) {
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
queue_element pop(queue _queue, _UL queue_len, void (*sw)(queue, _UL, _UL, void*), void *sw_a, _UL (*comp)(queue, _UL, _UL, void*), void *c_a) {
	queue_element best_element = _queue[0];
	_queue[0] = _queue[queue_len - 1];
	sift_down(0, _queue, queue_len - 1,sw,sw_a,comp,c_a);
	return best_element;
}
void heapify(queue _queue, _UL queue_len, void (*sw)(queue,_UL, _UL, void*), void *sw_a, _UL (*comp)(queue, _UL, _UL, void*), void *c_a) {
	for (int i = (queue_len - 2)/2; i >= 0; i-- ) sift_down(i,_queue,queue_len,sw, sw_a,comp, c_a);
}
void sift_up(_UL init_index, queue _queue, void (*sw)(queue, _UL, _UL, void*),void *sw_a, _UL (*comp)(queue, _UL, _UL, void*), void *c_a) {
	for (_UL index = init_index; index > 0; index = (index-1)/2) {
		if (comp(_queue, (index - 1)/2,index, c_a) == index) sw(_queue,(index - 1)/2,index, sw_a);		
	}
}
void push(queue _queue, queue_element item, _UL index, void (*sw)(queue, _UL, _UL, void*),void *sw_a, _UL (*comp)(queue, _UL, _UL, void*), void *c_a) {
	_queue[index] = item;
	sift_up(index,_queue, sw,sw_a,comp,c_a);
}


/*
I made this for the a* algorithm, but I worked to keep it agnostic.
This meant I had to have a lot of things which are certainly not required for a simple implementation.

You pass the "sw" function, which, taking as parameters the queue, two indexes, and a void ptr(I'll get to that),
it switches queue[index1] and queue[index2].

Now, I could do that within the function, but having it be passed makes the most sense considering that you may want it to report what's being moved where in a custom way, as is in my a* implementation.

"comp" is similar, where you may want it to prioritize minimizing or maximizing.
The void c_a and sw_a are arguments it will pass to void*, so that you might call push() and pass something over to the comparing function or the switching function, without it ever going into global scope.

-

I would love for things to be simpler, where you have a little bit of setup and then just push or pop with a void*, but that would require an internal state.
And I abhor internal states ;_;.
*/