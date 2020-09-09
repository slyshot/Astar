#ifndef _QUEUE
#define _QUEUE


typedef void* queue_element;
typedef queue_element* queue;
typedef unsigned long _UL;

typedef _UL (*_compare)(queue , _UL, _UL, void*);
typedef void (*_switch)(queue , _UL, _UL, void*);

void sift_down(_UL index, queue _queue, _UL queue_len, _switch sw, void *t_args, _compare comp, void *c_arg);

queue_element pop(queue _queue, _UL queue_len, _switch sw, void *t_arg, _compare comp, void *c_arg);

void heapify(queue _queue, _UL queue_len, void (*sw)(queue,_UL, _UL, void*), void *t_arg, _compare comp, void *c_arg);

void sift_up_once(_UL index, queue _queue, _switch sw,void *t_arg, _compare comp, void *c_arg);

void sift_up(_UL index, queue _queue, _switch sw,void *t_arg, _compare comp, void *c_arg);

void push(queue _queue, _UL queue_len, queue_element item, _switch sw,void *sw_arg, _compare comp, void *c_arg);

#endif