#include "graph.hpp"
#include <iostream>
#include <sstream>

string edgeToString(Edge e) {
    std::ostringstream out;
    out << "e" << e.i + 1 << "(" << e.v1 + 1 << ", " << e.v2 + 1<< ", " << e.weight << ")";
    return out.str();
}

Graph::Graph(int n) : V(n), adj_list(n) {
    this->E = 0;
}

int Graph::size() const { return this->V; };

int Graph::getNumEdges() const { return this->E; };

vector<Edge> Graph::getEdges(int vertex) const { return this->adj_list[vertex]; }

void Graph::addEdge(int v1, int v2, int weight) {
    this->adj_list[v1].push_back({this->E, v1, v2, weight});
    this->E++;
}

string Graph::toString() const {
    std::ostringstream out;;
    out << "G(" << this->V << ", " << this->E << ")" << std::endl;
    out << "--------------------" << std::endl;
    for (int i = 0; i < this->V; i++) {
        out << "v" << i + 1<< ": ";
        for (const Edge& edge : this->adj_list[i]) {
            out << "v" << edge.v2 + 1 << "|" << edge.weight << ", ";
        }
        out << "\b\b\n";
    }
    return out.str();
}