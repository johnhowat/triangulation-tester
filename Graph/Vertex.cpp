#include "Graph.h"

Vertex::Vertex(double _x_coordinate, double _y_coordinate) : x_coordinate(_x_coordinate), y_coordinate(_y_coordinate) {}

double Vertex::x() const {
	return(x_coordinate);
}

double Vertex::y() const {
	return(y_coordinate);
}

bool Vertex::is_adjacent(Vertex* v) const {
	return(get_edge_to(v) != nullptr);
}

Edge* Vertex::get_edge_to(Vertex* v) const {
	if(leaving != nullptr) {
		if(leaving->twin->origin == v) {
			return(leaving->edge);
		} else {
			HalfEdge* e = this->leaving->twin->next;
			while(e != leaving) {
				if(e->twin->origin == v) {
					return(e->edge);
				} else {
					e = e->twin->next;
				}
			}
		}
	}
	return(nullptr);
}

VertexVertexIterator Vertex::vertices_begin() {
	return(VertexVertexIterator(this));
}

VertexVertexIterator Vertex::vertices_end() {
	return(VertexVertexIterator());
}

VertexEdgeIterator Vertex::edges_begin() {
	return(VertexEdgeIterator(this));
}

VertexEdgeIterator Vertex::edges_end() {
	return(VertexEdgeIterator());
}

VertexFaceIterator Vertex::faces_begin() {
	return(VertexFaceIterator(this));
}

VertexFaceIterator Vertex::faces_end() {
	return(VertexFaceIterator());
}

std::ostream& operator<<(std::ostream& stream, Vertex& v) {
	stream << "(" << v.x() << "," << v.y() << ")";
	return stream;
}
