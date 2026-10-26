#ifndef CHP_PROJECT_GRAPH_HPP
#define CHP_PROJECT_GRAPH_HPP

#include <string>
#include <vector>

using namespace std;

typedef struct {
    int64_t i;  // index
    int64_t v1; // Vertex 1 (from)
    int64_t v2; // Vertex 2 (to)
    int64_t weight;
} Edge;

string edgeToString(Edge e);

class Graph {
  private:
    int64_t V;
    int64_t E;
    vector<vector<Edge>> adj_list;

  public:
    Graph(int64_t n);

    /* Getter & Setters */
    int64_t size() const;
    int64_t getNumEdges() const;

    /* Functionality */
    const vector<Edge>& getEdges(int64_t vertex) const;
    void addEdge(int64_t v1, int64_t v2, int64_t weight);
    string toString() const;
};

#endif // CHP_PROJECT_GRAPH_HPP
