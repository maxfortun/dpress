#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <stddef.h>

typedef unsigned char _graph_node_id_value;
typedef unsigned char _graph_node_id_index;

typedef struct _graph_node_id {
	_graph_node_id_value value;
	_graph_node_id_index index;
} _graph_node_id;

typedef struct _graph_edge {
	_graph_node_id source_node_id;
	_graph_node_id target_node_id;
} _graph_edge;

typedef size_t _graph_size_t;

// spool node allows for edges to be wound
typedef struct _graph_node {
	_graph_node_id id;
	_graph_size_t edges_size;
	_graph_edge *edges;
} _graph_node;

typedef struct _graph {
	_graph_size_t nodes_size;
	_graph_node *nodes;
} _graph;

void _graph_init(_graph *graph);
void _graph_destroy(_graph *graph);
void _graph_add_edge(_graph *graph, _graph_edge *edge);

typedef void _graph_traversal_state;

void _graph_bft(_graph *graph, void (*func)(_graph *graph, _graph_node *node, _graph_edge *source_edge, _graph_edge *target_edge, _graph_traversal_state *state), _graph_traversal_state *state);
void _graph_dft(_graph *graph, void (*func)(_graph *graph, _graph_node *node, _graph_edge *source_edge, _graph_edge *target_edge, _graph_traversal_state *state), _graph_traversal_state *state);


/* 2 graphs needed */
/* 1 graph to store connections */
/* 1 graph to store the tree of words */

#endif 
