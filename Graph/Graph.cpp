#include <algorithm>
#include <fstream>
#include <pngwriter.h>
#include <string>
#include "Graph.h"

Graph::Graph() {}

Graph::Graph(const std::string& filename) {
	std::ifstream filestream(filename, std::ifstream::in);
	from_ifstream(filestream);
}

Graph::Graph(std::ifstream& filestream) {
	if(filestream.good()) {
		from_ifstream(filestream);
	}
}

void Graph::from_ifstream(std::ifstream& filestream) {
	Face* f = new Face();
	faces.push_back(f);

	HalfEdge* prev_left = nullptr;
	HalfEdge* prev_right = nullptr;
	HalfEdge* first_left = nullptr;
	HalfEdge* first_right = nullptr;
	Vertex* first_vertex = nullptr;
	
	double x,y;
	while(filestream >> x >> y) {
		Vertex* v = new Vertex(x,y);
		vertices.push_back(v);
		if(first_vertex == nullptr) { first_vertex = v; }

		HalfEdge* left = new HalfEdge();
		HalfEdge* right = new HalfEdge();
		half_edges.push_back(left);
		half_edges.push_back(right);
		Edge* edge = new Edge(left);
		left->edge = edge;
		right->edge = edge;
		edges.push_back(edge);
		if(first_left == nullptr) { first_left = left; }
		if(first_right == nullptr) { first_right = right; }

		left->face = f;
		left->origin = v;
		left->twin = right;
		right->next = prev_right;
		right->twin = left;
		right->face = nullptr;
		v->leaving = left;

		if(prev_left != nullptr) { prev_left->next = left; }
		if(prev_right != nullptr) { prev_right->origin = v; }
		prev_left = left;
		prev_right = right;
	}
	filestream.close();

	prev_left->next = first_left;
	first_right->next = prev_right;
	prev_right->origin = first_vertex;
	f->half_edge = first_left;
}

Graph::~Graph() {
	for(Vertex* v : vertices) {
		delete v;
	}
	for(HalfEdge* e : half_edges) {
		delete e;
	}
	for(Edge* e : edges) {
		delete e;
	}
	for(Face* f : faces) {
		delete f;
	}
}

bool Graph::is_legal_edge(Vertex* u, Vertex* v) const {
	std::size_t i,j;
	
	for(i = 0; i < edges.size(); i++) {
		if(intersects(u, v, edges[i]->u(), edges[i]->v())) {
			return(false); 
		}
	}

	bool test = false;
	double x = (u->x() + v->x()) / 2.0;
	double y = (u->y() + v->y()) / 2.0;

	for(i = 0, j = vertices.size()-1; i < vertices.size(); j = i++) {
		if(
			((vertices[i]->y() > y) != (vertices[j]->y() > y)) &&
			(x < (vertices[j]->x() - vertices[i]->x()) * (y - vertices[i]->y()) / (vertices[j]->y() - vertices[i]->y()) + vertices[i]->x())
		) {
			test = !test;
		}
	}

	return(test);
}

Edge* Graph::add_edge(Vertex* u, Vertex* v) {
	if(u->is_adjacent(v)) { return(nullptr); }

	Face* f = new Face();
	faces.push_back(f);
	
	HalfEdge* left = new HalfEdge();
	HalfEdge* right = new HalfEdge();
	half_edges.push_back(left);
	half_edges.push_back(right);
	Edge* edge = new Edge(left);
	left->edge = edge;
	right->edge = edge;
	edges.push_back(edge);

	Face* reference = reference_face(u,v);
	HalfEdge* previous_u = previous_half_edge(u, reference);
	HalfEdge* previous_v = previous_half_edge(v, reference);
	
	f->half_edge = left;
	reference->half_edge = right;

	left->face = f;
	left->next = previous_v->next;
	left->origin = u;
	left->twin = right;
	
	right->face = reference;
	right->next = previous_u->next;
	right->origin = v;
	right->twin = left;

	previous_u->next = left;
	previous_v->next = right;
	
	HalfEdge* current_edge = left->next;
	while(current_edge != left) {
		current_edge->face = f;
		current_edge = current_edge->next;
	}

	return(edge); 
}

void Graph::remove_edge(Vertex* u, Vertex *v) {
	remove_edge(u->get_edge_to(v));
}

void Graph::remove_edge(Edge* e) {
	Face* face = e->half_edge->face;
	Face* twin_face = e->half_edge->twin->face;
	
	HalfEdge* previous = e->half_edge->previous_half_edge();
	HalfEdge* twin_previous = e->half_edge->twin->previous_half_edge();
	HalfEdge* next = e->half_edge->next;
	HalfEdge* twin_next = e->half_edge->twin->next;
	
	previous->next = twin_next;
	twin_previous->next = next;
	twin_face->half_edge = next;

	HalfEdge* current = next;
	while(current != twin_next) {
		current->face = twin_face;
		current = current->next;
	} 

	faces.erase(std::remove(faces.begin(), faces.end(), face));
	half_edges.erase(std::remove(half_edges.begin(), half_edges.end(), e->half_edge));
	half_edges.erase(std::remove(half_edges.begin(), half_edges.end(), e->half_edge->twin));
	edges.erase(std::remove(edges.begin(), edges.end(), e));
	
	delete face;
	delete e->half_edge->twin;
	delete e->half_edge;
	delete e;
}

std::size_t Graph::vertex_count() const {
	return(vertices.size());
}

std::size_t Graph::edge_count() const {
	return(edges.size());
}

std::size_t Graph::face_count() const {
	return(faces.size());
}

VertexIterator Graph::vertices_begin() {
	return(VertexIterator(vertices.begin()));
}

VertexIterator Graph::vertices_end() {
	return(VertexIterator(vertices.end()));
}

EdgeIterator Graph::edges_begin() {
	return(EdgeIterator(edges.begin()));
}

EdgeIterator Graph::edges_end() {
	return(EdgeIterator(edges.end()));
}

FaceIterator Graph::faces_begin() {
	return(FaceIterator(faces.begin()));
}

FaceIterator Graph::faces_end() {
	return(FaceIterator(faces.end()));
}

void Graph::save_image(const std::string& filename) const {
	auto x = std::minmax_element(vertices.begin(),vertices.end(), [](Vertex* lhs, Vertex* rhs) { return(lhs->x() < rhs->x()); });
	auto y = std::minmax_element(vertices.begin(),vertices.end(), [](Vertex* lhs, Vertex* rhs) { return(lhs->y() < rhs->y()); });
	double minx = (*(x.first))->x();
	double maxx = (*(x.second))->x();
	double miny = (*(y.first))->y();
	double maxy = (*(y.second))->y();
	double margin = 25.0;
	double vertex_radius = 3;
	
	pngwriter image((maxx-minx)+2*margin,(maxy-miny)+2*margin,1.0,filename.c_str());
	for(auto i = edges.begin(); i != edges.end(); i++) {
		image.line((*i)->u()->x() - minx + margin, (*i)->u()->y() - miny + margin, (*i)->v()->x()- minx + margin, (*i)->v()->y() - miny + margin, 1.0, 0.0, 0.0);
	}
	for(auto i = vertices.begin(); i != vertices.end(); i++) {
		auto j = i; j++;
		if(j == vertices.end()) { j = vertices.begin(); }
		
		image.line((*i)->x() - minx + margin, (*i)->y() - miny + margin, (*j)->x() - minx + margin, (*j)->y() - miny + margin, 0.0, 0.0, 0.0);
	}
	for(auto i = vertices.begin(); i != vertices.end(); i++) {
		image.filledcircle((*i)->x()- minx + margin, (*i)->y() - miny + margin, vertex_radius, 0.0, 0.0, 0.0);
	}
	
	image.close();
}

bool Graph::intersects(Vertex* a, Vertex* b, Vertex* c, Vertex* d) const {
	orientation d1 = direction(c,d,a);
	orientation d2 = direction(c,d,b);
	orientation d3 = direction(a,b,c);
	orientation d4 = direction(a,b,d);

	return(
		(((d1 == Left && d2 == Right) || (d1 == Right && d2 == Left)) && ((d3 == Left && d4 == Right) || (d3 == Right && d4 == Left)))
			||
		(d1 == Collinear && on_segment(c,d,a)) ||
		(d2 == Collinear && on_segment(c,d,b)) ||
		(d3 == Collinear && on_segment(a,b,c)) ||
		(d4 == Collinear && on_segment(a,b,d))
	);
}

Graph::orientation Graph::direction(Vertex* a, Vertex* b, Vertex* c) const {
	double determinant = (a->x() - c->x()) * (b->y() - c->y()) - (a->y() - c->y()) * (b->x() - c->x());
	if(determinant > 0) {
		return(Left);
	} else if(determinant < 0) {
		return(Right);
	} else {
		return(Collinear);
	}
}

bool Graph::on_segment(Vertex* a, Vertex* b, Vertex* c) const {
	return(
		(a->x() < c->x() || b->x() < c->x()) &&
		(c->x() < a->x() || c->x() < b->x()) &&
		(a->y() < c->y() || b->y() < c->y()) &&
		(c->y() < a->y() || c->y() < b->y())
	);
}

Face* Graph::reference_face(Vertex* v1, Vertex* v2) const {
	if(v1->leaving->face == v2->leaving->face) {
		return(v1->leaving->face);
	}
	HalfEdge* e1 = v1->leaving->twin->next->twin;
	while(e1 != v1->leaving->twin) {
		HalfEdge* e2 = v2->leaving->twin->next->twin;
		while(e2 != v2->leaving->twin) {
			if(e1->face == e2->face) { return(e1->face); }
			e2 = e2->next->twin;
		}
		e1 = e1->next->twin;
	}
	return(v1->leaving->face);
}

HalfEdge* Graph::previous_half_edge(Vertex* v, Face* f) const {
	HalfEdge* twin = v->leaving->twin;
	HalfEdge* e = v->leaving->twin->next->twin;
	while(e != twin) {
		if(e->face == f) { return(e); }
		e = e->next->twin;
	}
	return(e);
}
