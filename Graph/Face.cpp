#include "Graph.h"

Face::Face() {}

double Face::perimeter() const {
	double sum = 0.0;
	HalfEdge* current = half_edge;
	do {
		sum += current->edge->length();
		current = current->next;
	} while(current != half_edge);
	return(sum);
}

FaceVertexIterator Face::vertices_begin() {
	return(FaceVertexIterator(this));
}

FaceVertexIterator Face::vertices_end() {
	return(FaceVertexIterator());
}

FaceEdgeIterator Face::edges_begin() {
	return(FaceEdgeIterator(this));
}

FaceEdgeIterator Face::edges_end() {
	return(FaceEdgeIterator());
}

FaceFaceIterator Face::faces_begin() {
	return(FaceFaceIterator(this));
}

FaceFaceIterator Face::faces_end() {
	return(FaceFaceIterator());
}

std::ostream& operator<<(std::ostream& stream, Face& f) {
	FaceVertexIterator i = f.vertices_begin();
	stream << **i;
	for(++i; i != f.vertices_end(); ++i) {
		stream << "-" << **i;
	}
	return(stream);
}
