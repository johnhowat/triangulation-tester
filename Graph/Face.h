#ifndef __FACE_H__
#define __FACE_H__

#include <iostream>
#include "Graph.h"

class Face {
	friend class Graph;
	friend class Vertex;
	friend class HalfEdge;
	friend class Edge;
	friend class VertexIterator; friend class VertexVertexIterator; friend class VertexEdgeIterator; friend class VertexFaceIterator;
	friend class EdgeIterator; friend class EdgeVertexIterator; friend class EdgeEdgeIterator; friend class EdgeFaceIterator;
	friend class FaceIterator; friend class FaceVertexIterator; friend class FaceEdgeIterator; friend class FaceFaceIterator;

	HalfEdge* half_edge;

	public:
		double perimeter() const;
		FaceVertexIterator vertices_begin();
		FaceVertexIterator vertices_end();
		FaceEdgeIterator edges_begin();
		FaceEdgeIterator edges_end();
		FaceFaceIterator faces_begin();
		FaceFaceIterator faces_end();

	private:
		Face();
};

std::ostream& operator<<(std::ostream& stream, Face& face);

#endif
