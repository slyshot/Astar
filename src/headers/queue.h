#ifndef _QUEUE
#define _QUEUE
// typedef struct {
// 	int priority;
// 	void *data;
// } queue_element;
typedef void* queue_element;
typedef queue_element* queue;
typedef unsigned long _UL;

void sift_down(_UL index, queue _queue, _UL queue_len ,void (*transform)(queue, _UL, _UL, void*), void *t_args, _UL (*comparator)(queue , _UL, _UL, void*), void *c_arg);
// void sift_down(_UL index, queue _queue, _UL queue_len , _UL (*comparator)(queue , _UL, _UL, void*), void *c_arg);
queue_element pop(queue _queue, _UL queue_len, void (*transform)(queue, _UL, _UL, void*), void *t_arg, _UL (*comparator)(queue , _UL, _UL, void*), void *c_arg);

// queue_element pop(queue _queue, _UL queue_len, _UL (*comparator)(queue , _UL, _UL, void*), void *c_arg);
void heapify(queue _queue, _UL queue_len, void (*transform)(queue,_UL, _UL, void*), void *t_arg, _UL (*comparator)(queue , _UL, _UL, void*), void *c_arg);

// void heapify(queue _queue, _UL queue_len, _UL (*comparator)(queue , _UL, _UL, void*), void *c_arg);

void sift_up_once(_UL index, queue _queue, void (*transform)(queue, _UL, _UL, void*),void *t_arg, _UL (*comparator)(queue , _UL, _UL, void*), void *c_arg);

void sift_up(_UL init_index, queue _queue, void (*transform)(queue, _UL, _UL, void*),void *t_arg, _UL (*comparator)(queue , _UL, _UL, void*), void *c_arg);
// _UL sift_up(_UL init_index, queue _queue, _UL (*comparator)(queue , _UL, _UL, void*), void *c_arg);
//Returns how far up in the tree it got
void push(queue _queue, queue_element item, _UL queue_len, void (*transform)(queue, _UL, _UL, void*),void *t_arg, _UL (*comparator)(queue , _UL, _UL, void*), void *c_arg);
// _UL push(queue _queue, queue_element item, _UL queue_len, _UL (*comparator)(queue , _UL, _UL));

_UL comparator(queue _queue, _UL index1, _UL index2, void*);

#endif