#ifndef CHP_PROJECT_GRAPH_HPP
#define CHP_PROJECT_GRAPH_HPP

#include <string>
#include <vector>

using namespace std;

typedef struct {
    int i;  // index
    int v1; // Vertex 1 (from)
    int v2; // Vertex 2 (to)
    int weight;
} Edge;

string edgeToString(Edge e);

class Graph {
  private:
    int V;
    int E;
    vector<vector<Edge>> adj_list;

  public:
    Graph(int n);

    /* Getter & Setters */
    int size() const;
    int getNumEdges() const;

    /* Functionality */
    vector<Edge> getEdges(int vertex) const;
    void addEdge(int v1, int v2, int weight);
    string toString() const;
};

#endif // CHP_PROJECT_GRAPH_HPP
