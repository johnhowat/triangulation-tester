#include <iterator>
#include <vector>
#include "Graph.h"

VertexIterator::VertexIterator(std::vector<Vertex*>::iterator _container_iterator) : container_iterator(_container_iterator) {}
VertexIterator::VertexIterator() {}
VertexIterator::VertexIterator(const VertexIterator& i) : container_iterator(i.container_iterator) {}
const VertexIterator& VertexIterator::operator=(const VertexIterator& i) { container_iterator = i.container_iterator; return(i); }
VertexIterator& VertexIterator::operator++() { ++container_iterator; return(*this); }
VertexIterator VertexIterator::operator++(int) { VertexIterator temp(*this); ++(*this); return(temp); }
bool VertexIterator::operator==(const VertexIterator& rhs) const { return(container_iterator == rhs.container_iterator); }
bool VertexIterator::operator!=(const VertexIterator& rhs) const { return(container_iterator != rhs.container_iterator); }
Vertex* VertexIterator::operator*() const { return(*container_iterator); }

VertexVertexIterator::VertexVertexIterator(Vertex* v) : initial(v->leaving), current(v->leaving) {}
VertexVertexIterator::VertexVertexIterator() : initial(nullptr), current(nullptr) {}
VertexVertexIterator::VertexVertexIterator(const VertexVertexIterator& i) : initial(i.initial), current(i.current) {}
const VertexVertexIterator& VertexVertexIterator::operator=(const VertexVertexIterator& i) { initial = i.initial; current = i.current;  return(i);}
VertexVertexIterator& VertexVertexIterator::operator++() { if(initial != nullptr) { if(current->twin->next == initial) { current = nullptr; initial = nullptr; } else { current = current->twin->next; } } return(*this); }
VertexVertexIterator VertexVertexIterator::operator++(int) { VertexVertexIterator temp(*this); ++(*this); return(temp); }
bool VertexVertexIterator::operator==(const VertexVertexIterator& rhs) const { return((initial == rhs.initial) && (current == rhs.current)); }
bool VertexVertexIterator::operator!=(const VertexVertexIterator& rhs) const { return((initial != rhs.initial) || (current != rhs.current)); }
Vertex* VertexVertexIterator::operator*() const { return(current == nullptr ? nullptr : current->twin->origin); }

VertexEdgeIterator::VertexEdgeIterator(Vertex* v) : initial(v->leaving), current(v->leaving) {}
VertexEdgeIterator::VertexEdgeIterator() : initial(nullptr), current(nullptr) {}
VertexEdgeIterator::VertexEdgeIterator(const VertexEdgeIterator& i) : initial(i.initial), current(i.current) {}
const VertexEdgeIterator& VertexEdgeIterator::operator=(const VertexEdgeIterator& i) { initial = i.initial; current = i.current; return(i); }
VertexEdgeIterator& VertexEdgeIterator::operator++() { if(initial != nullptr) { if(current->twin->next == initial) { current = nullptr; initial = nullptr; } else { current = current->twin->next; } } return(*this); }
VertexEdgeIterator VertexEdgeIterator::operator++(int) { VertexEdgeIterator temp(*this); ++(*this); return(temp); }
bool VertexEdgeIterator::operator==(const VertexEdgeIterator& rhs) const { return((initial == rhs.initial) && (current == rhs.current)); }
bool VertexEdgeIterator::operator!=(const VertexEdgeIterator& rhs) const { return((initial != rhs.initial) || (current != rhs.current)); }
Edge* VertexEdgeIterator::operator*() const { return(current == nullptr ? nullptr : current->edge); }

VertexFaceIterator::VertexFaceIterator(Vertex* v) : initial(v->leaving), current(v->leaving) {}
VertexFaceIterator::VertexFaceIterator() : initial(nullptr), current(nullptr) {}
VertexFaceIterator::VertexFaceIterator(const VertexFaceIterator& i) : initial(i.initial), current(i.current) {}
const VertexFaceIterator& VertexFaceIterator::operator=(const VertexFaceIterator& i) { initial = i.initial; current = i.current; return(i); }
VertexFaceIterator& VertexFaceIterator::operator++() { if(initial != nullptr) { current = current->twin->next; while(current->face == nullptr) { current = current->twin->next; } if(current == initial) { current = nullptr; initial = nullptr; } } return(*this); }
VertexFaceIterator VertexFaceIterator::operator++(int) { VertexFaceIterator temp(*this); ++(*this); return(temp); }
bool VertexFaceIterator::operator==(const VertexFaceIterator& rhs) const { return((initial == rhs.initial) && (current == rhs.current)); }
bool VertexFaceIterator::operator!=(const VertexFaceIterator& rhs) const { return((initial != rhs.initial) || (current != rhs.current)); }
Face* VertexFaceIterator::operator*() const { return(current == nullptr ? nullptr : current->face); }

EdgeIterator::EdgeIterator(std::vector<Edge*>::iterator _container_iterator) : container_iterator(_container_iterator) {}
EdgeIterator::EdgeIterator() {}
EdgeIterator::EdgeIterator(const EdgeIterator& i) : container_iterator(i.container_iterator) {}
const EdgeIterator& EdgeIterator::operator=(const EdgeIterator& i) { container_iterator = i.container_iterator; return(i); }
EdgeIterator& EdgeIterator::operator++() { ++container_iterator; return(*this); }
EdgeIterator EdgeIterator::operator++(int) { EdgeIterator temp(*this); ++(*this); return(temp); }
bool EdgeIterator::operator==(const EdgeIterator& rhs) const { return(container_iterator == rhs.container_iterator); }
bool EdgeIterator::operator!=(const EdgeIterator& rhs) const { return(container_iterator != rhs.container_iterator); }
Edge* EdgeIterator::operator*() const { return(*container_iterator); }

EdgeVertexIterator::EdgeVertexIterator(Edge* e) : initial(e->half_edge), current(e->half_edge) {}
EdgeVertexIterator::EdgeVertexIterator() : initial(nullptr), current(nullptr) {}
EdgeVertexIterator::EdgeVertexIterator(const EdgeVertexIterator& i) : initial(i.initial), current(i.current) {}
const EdgeVertexIterator& EdgeVertexIterator::operator=(const EdgeVertexIterator& i) { initial = i.initial; current = i.current;  return(i);}
EdgeVertexIterator& EdgeVertexIterator::operator++() { if(initial != nullptr) { if(current->twin == initial) { current = nullptr; initial = nullptr; } else { current = current->twin; }} return(*this); }
EdgeVertexIterator EdgeVertexIterator::operator++(int) { EdgeVertexIterator temp(*this); ++(*this); return(temp); }
bool EdgeVertexIterator::operator==(const EdgeVertexIterator& rhs) const { return((initial == rhs.initial) && (current == rhs.current)); }
bool EdgeVertexIterator::operator!=(const EdgeVertexIterator& rhs) const { return((initial != rhs.initial) || (current != rhs.current)); }
Vertex* EdgeVertexIterator::operator*() const { return(current == nullptr ? nullptr : current->origin); }

EdgeEdgeIterator::EdgeEdgeIterator(Edge* e) : initial(e->half_edge), current(e->half_edge->next) {}
EdgeEdgeIterator::EdgeEdgeIterator() : initial(nullptr), current(nullptr) {}
EdgeEdgeIterator::EdgeEdgeIterator(const EdgeEdgeIterator& i) : initial(i.initial), current(i.current) {}
const EdgeEdgeIterator& EdgeEdgeIterator::operator=(const EdgeEdgeIterator& i) { initial = i.initial; current = i.current; return(i); }
EdgeEdgeIterator& EdgeEdgeIterator::operator++() { if(initial != nullptr) { if(current->next == initial) { if(initial->twin->face == nullptr) { current = nullptr; initial = nullptr; } else { current = initial->twin->next; } } else if (current->next == initial->twin) { current = nullptr; initial = nullptr; }  else { current = current->next; } } return(*this);}
EdgeEdgeIterator EdgeEdgeIterator::operator++(int) { EdgeEdgeIterator temp(*this); ++(*this); return(temp); }
bool EdgeEdgeIterator::operator==(const EdgeEdgeIterator& rhs) const { return((initial == rhs.initial) && (current == rhs.current)); }
bool EdgeEdgeIterator::operator!=(const EdgeEdgeIterator& rhs) const { return((initial != rhs.initial) || (current != rhs.current)); }
Edge* EdgeEdgeIterator::operator*() const { return(current == nullptr ? nullptr : current->edge); }

EdgeFaceIterator::EdgeFaceIterator(Edge* e) : initial(e->half_edge), current(e->half_edge) { if(current->face == nullptr) { current = current->twin; initial = initial->twin; } }
EdgeFaceIterator::EdgeFaceIterator() : initial(nullptr), current(nullptr) {}
EdgeFaceIterator::EdgeFaceIterator(const EdgeFaceIterator& i) : initial(i.initial), current(i.current) {}
const EdgeFaceIterator& EdgeFaceIterator::operator=(const EdgeFaceIterator& i) { initial = i.initial; current = i.current; return(i); }
EdgeFaceIterator& EdgeFaceIterator::operator++() { if(initial != nullptr) { if(current->twin == initial || current->twin->face == nullptr) { current = nullptr; initial = nullptr; } else { current = current->twin; } } return(*this); }
EdgeFaceIterator EdgeFaceIterator::operator++(int) { EdgeFaceIterator temp(*this); ++(*this); return(temp); }
bool EdgeFaceIterator::operator==(const EdgeFaceIterator& rhs) const { return((initial == rhs.initial) && (current == rhs.current)); }
bool EdgeFaceIterator::operator!=(const EdgeFaceIterator& rhs) const { return((initial != rhs.initial) || (current != rhs.current)); }
Face* EdgeFaceIterator::operator*() const { return(current == nullptr ? nullptr : current->face); }

FaceIterator::FaceIterator(std::vector<Face*>::iterator _container_iterator) : container_iterator(_container_iterator) {}
FaceIterator::FaceIterator() {}
FaceIterator::FaceIterator(const FaceIterator& i) : container_iterator(i.container_iterator) {}
const FaceIterator& FaceIterator::operator=(const FaceIterator& i) { container_iterator = i.container_iterator; return(i); }
FaceIterator& FaceIterator::operator++() { ++container_iterator; return(*this); }
FaceIterator FaceIterator::operator++(int) { FaceIterator temp(*this); ++(*this); return(temp); }
bool FaceIterator::operator==(const FaceIterator& rhs) const { return(container_iterator == rhs.container_iterator); }
bool FaceIterator::operator!=(const FaceIterator& rhs) const { return(container_iterator != rhs.container_iterator); }
Face* FaceIterator::operator*() const { return(*container_iterator); }

FaceVertexIterator::FaceVertexIterator(Face* f) : initial(f->half_edge), current(f->half_edge) {}
FaceVertexIterator::FaceVertexIterator() : initial(nullptr), current(nullptr) {}
FaceVertexIterator::FaceVertexIterator(const FaceVertexIterator& i) : initial(i.initial), current(i.current) {}
const FaceVertexIterator& FaceVertexIterator::operator=(const FaceVertexIterator& i) { initial = i.initial; current = i.current;  return(i);}
FaceVertexIterator& FaceVertexIterator::operator++() { if(initial != nullptr) { if(current->next == initial) { current = nullptr; initial = nullptr; } else { current = current->next; }} return(*this); }
FaceVertexIterator FaceVertexIterator::operator++(int) { FaceVertexIterator temp(*this); ++(*this); return(temp); }
bool FaceVertexIterator::operator==(const FaceVertexIterator& rhs) const { return((initial == rhs.initial) && (current == rhs.current)); }
bool FaceVertexIterator::operator!=(const FaceVertexIterator& rhs) const { return((initial != rhs.initial) || (current != rhs.current)); }
Vertex* FaceVertexIterator::operator*() const { return(current == nullptr ? nullptr : current->origin); }

FaceEdgeIterator::FaceEdgeIterator(Face* f) : initial(f->half_edge), current(f->half_edge) {}
FaceEdgeIterator::FaceEdgeIterator() : initial(nullptr), current(nullptr) {}
FaceEdgeIterator::FaceEdgeIterator(const FaceEdgeIterator& i) : initial(i.initial), current(i.current) {}
const FaceEdgeIterator& FaceEdgeIterator::operator=(const FaceEdgeIterator& i) { initial = i.initial; current = i.current; return(i); }
FaceEdgeIterator& FaceEdgeIterator::operator++() { if(initial != nullptr) { if(current->next == initial) { current = nullptr; initial = nullptr; } else { current = current->next; } } return(*this); }
FaceEdgeIterator FaceEdgeIterator::operator++(int) { FaceEdgeIterator temp(*this); ++(*this); return(temp); }
bool FaceEdgeIterator::operator==(const FaceEdgeIterator& rhs) const { return((initial == rhs.initial) && (current == rhs.current)); }
bool FaceEdgeIterator::operator!=(const FaceEdgeIterator& rhs) const { return((initial != rhs.initial) || (current != rhs.current)); }
Edge* FaceEdgeIterator::operator*() const { return(current == nullptr ? nullptr : current->edge); }

FaceFaceIterator::FaceFaceIterator(Face* f) : initial(f->half_edge), current(f->half_edge) { if(current->twin->face == nullptr) { initial = nullptr; current = nullptr; } }
FaceFaceIterator::FaceFaceIterator() : initial(nullptr), current(nullptr) {}
FaceFaceIterator::FaceFaceIterator(const FaceFaceIterator& i) : initial(i.initial), current(i.current) {}
const FaceFaceIterator& FaceFaceIterator::operator=(const FaceFaceIterator& i) { initial = i.initial; current = i.current; return(i); }
FaceFaceIterator& FaceFaceIterator::operator++() { if(initial != nullptr) { current = current->next; while(current->twin->face == nullptr) { current = current->next; } if(current == initial) { current = nullptr; initial = nullptr; } } return(*this); }
FaceFaceIterator FaceFaceIterator::operator++(int) { FaceFaceIterator temp(*this); ++(*this); return(temp); }
bool FaceFaceIterator::operator==(const FaceFaceIterator& rhs) const { return((initial == rhs.initial) && (current == rhs.current)); }
bool FaceFaceIterator::operator!=(const FaceFaceIterator& rhs) const { return((initial != rhs.initial) || (current != rhs.current)); }
Face* FaceFaceIterator::operator*() const { return(current == nullptr ? nullptr : current->twin->face); }
