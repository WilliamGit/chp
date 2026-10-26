#include "graph.hpp"
#include <iostream>
#include <sstream>

string edgeToString(Edge e) {
  std::ostringstream out;
  out << "e" << e.i + 1 << "(" << e.v1 + 1 << ", " << e.v2 + 1 << ", "
      << e.weight << ")";
  return out.str();
}

Graph::Graph(const int64_t n) : V(n), E(0), adj_list(n) {}

int64_t Graph::size() const { return this->V; };

int64_t Graph::getNumEdges() const { return this->E; };

const vector<Edge>& Graph::getEdges(const int64_t vertex) const {
  return this->adj_list[vertex];
}

void Graph::addEdge(const int64_t v1, const int64_t v2, const int64_t weight) {
  this->adj_list[v1].push_back({this->E, v1, v2, weight});
  this->adj_list[v2].push_back({this->E, v2, v1, weight});
  this->E++;
}

string Graph::toString() const {
  std::ostringstream out;
  ;
  out << "G(" << this->V << ", " << this->E << ")" << std::endl;
  out << "--------------------" << std::endl;
  for (int i = 0; i < this->V; i++) {
    out << "v" << i + 1 << ": ";
    for (Edge edge : this->adj_list[i]) {
      out << "v" << edge.v2 + 1 << "|" << edge.weight << ", ";
    }
    out << "\b\b\n";
  }
  return out.str();
}
