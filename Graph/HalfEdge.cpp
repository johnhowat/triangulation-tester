#include "Graph.h"

HalfEdge::HalfEdge() {}

HalfEdge* HalfEdge::previous_half_edge() const {
	HalfEdge* current = twin->next->twin;
	while(current->next != this) {
		current = current->next->twin;
	}
	return(current);
}
