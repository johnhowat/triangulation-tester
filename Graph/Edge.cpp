#include <cmath>
#include "Graph.h"

Edge::Edge(HalfEdge* _half_edge) : half_edge(_half_edge) {}

Vertex* Edge::u() const {
	return(half_edge->origin);
}

Vertex* Edge::v() const {
	return(half_edge->twin->origin);
}

double Edge::length() const {
	double dx = u()->x() - v()->x();
	double dy = u()->y() - v()->y();
	return(sqrt(dx*dx + dy*dy));
}

EdgeVertexIterator Edge::vertices_begin() {
	return(EdgeVertexIterator(this));
}

EdgeVertexIterator Edge::vertices_end() {
	return(EdgeVertexIterator());
}

EdgeEdgeIterator Edge::edges_begin() {
	return(EdgeEdgeIterator(this));
}

EdgeEdgeIterator Edge::edges_end() {
	return(EdgeEdgeIterator());
}

EdgeFaceIterator Edge::faces_begin() {
	return(EdgeFaceIterator(this));
}

EdgeFaceIterator Edge::faces_end() {
	return(EdgeFaceIterator());
}

std::ostream& operator<<(std::ostream& stream, Edge& e) {
	stream << *(e.u()) << "-" << *(e.v());
	return(stream);
}
