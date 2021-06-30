# A*

##### *(Vers. 0.4)*

## What?

[A*](https://en.wikipedia.org/wiki/A*_search_algorithm) is a popular pathfinding algorithm, often used in games and the like. This is my implementation of it.

It has a pretty great O(x) computational time, (Though not so great memory-wise, and I can't promise my implementation is very efficient *yet*).

Its' use is with node networks, so while it'll work on a 2d grid, it can do much more.


## Why?

Well, it's a really simple procedure for what it's trying to get done, so I personally believe it'd be a shame if you don't try your hand at it.
I have a few times, but all my other attempts have relied on a 2d grid. That may mean fewer clock cycles, but at the expense of many use cases.

And some of those, I've been thinking of as a side-project.

For instance, I'd like to fit it to a web-crawler (Although, admittedly that might devolve into djikstra or a binary search if I can't get a good heuristic) to find the closest link between two people on facebook, or two pages on Wikipedia.

And if I'm going to have such a good time doing this, why not share it with the greater community?

## How?

### Use

#### The queue

The queue is moderately complicated in construction, so as to allow many use-cases.

All it does is move void ptrs around in a priority-queue pattern. You give it the function to do the smallest unit of movement( Called `sw`, would normally switch two pointers), and the function for comparing two ptrs(called `comp`).

It may seem strange to input `sw` and `comp` when you could have a preset way to compare or switch pointers, but again, the user may want to do it one or another way(And having a preset comparison or switch assumes a structure rather than void ptrs). In A*, I found it useful to do other things when two pointers were switched, to keep track of their position in the priority queue.

`sw_a` and `c_a` are void ptrs that get passed along to the switch function and comparator function respectively. That's mostly so that if you *do* want to do something unusual with `sw` or `comp`, you can do that without messing with global variables.

#### Example

You could pass pointers that look like:
`struct {int priority, int data}`
(And lets assume that's typedef'd to `q_node`)
to the queue functions, starting with some allocated memory as "queue", and 0 as queue_len(increasing when you add elements).
In this case, your comp function would look like:

```C
_UL comp(queue q, _UL index1, _UL index2, void* c_a) {
	q_node node1 = (q_node)q[index1];
	q_node node2 = (q_node)q[index2];
	return node1.priority > node2.priority ? index1 : index2
}
```

And your switch function:

```C
_UL sw(queue q, _UL index1, _UL index2, void* sw_a) {
	void* temp = q[index1];
	q[index1] = q[index2];
	q[index2] = temp;
}
```
#### Astar

##### *(Until version 1.0, this is subject to change.)*

`astar` is a function that takes a starting node, an ending node, a gscore function, and an hscore function.

It returns nothing. Instead, the pointer `endnode.breadcrumb` will be another node(or NULL if the a* failed to get a path). Keep on dereferencing breacrumbs until you're back to the startnode, and that'll walk you through the optimal path.

The gscore and hscore functions, as expected, take two nodes and returns the hscore and gscore btween them.

the `node`s look like this:

```C
typedef struct node {
	void* data;
	astar_data a_data;
} node;
```

"data" would, in most cases, be position. In my use-case, I'm thinking of it being links.
Just whatever you want to associate the node with other than fscore, gscore, etc.
`a_data` is all for astar(It's defined in `astar.h` if you want to look at it), and for the most part can be zeroed out(So initializing with calloc is recommended).

There are a couple exceptions, though:

a_data is where you connect a node to other nodes. `node.a_data.connected_nodes` should be a list of node pointers, and `node.a_data.num_nodes` the length of that list.

If you want any node to be entirely blocked off as a 'wall', you can initialize
`node.blocked` to 1.


#### Wrapping it up

Say, you want to store ints in a max-heap way, and your struct for doing that looks like:

```C
typedef struct {
	int priority;
	int data;
} node_data
```
Calls to a priority queue will use the comp and switch function from earlier.
Since no special arguments are being passed, there's no need for `comp_a` or `sw_a`.

So `queue_element pop(queue _queue, _UL queue_len, _switch sw, void *sw_arg, _compare comp, void *c_arg);`
becomes `queue_element pop_max(queue _queue, _UL queue_len);`, which calls pop with your given comp, sw, and NULL as sw_arg and c_arg.

Writing wrappers like this for your use-case will clearly make the code much less messy.
