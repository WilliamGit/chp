#include "graph.hpp"

#include <iostream>
#include <list>
#include <queue>
#include <string>

using namespace std;

const int INF = std::numeric_limits<int>::max();

int sum1(const list<Edge> path) {
    int sum = 0;
    for (Edge e : path)
        sum += e.weight;
    return sum;
}

int sum2(const list<Edge> path, const int M) {
    int sum = 0;
    for (Edge e : path)
        sum += (M - e.weight);
    return sum;
}

int betaIneq(const list<Edge> path, const int M) { return max(sum1(path), sum2(path, M)); }

struct QueueEntry {
    int v; // Vertex index
    int f; // f(v) = g(v) + h(v)
};

auto QueueCompare = [](const QueueEntry e1, const QueueEntry e2) {
    return (e1.f > e2.f); // min heap
};

// #TODO: return reference ?
list<Edge> constructPath(const Graph* graph, vector<int> prev, const int v_start,
                         const int v_target) {
    list<Edge> path;
    int current = v_target;
    while (current != v_start) {
        int previous = prev[current];
        if (previous == -1)
            return path;
        vector<Edge> edges = graph->getEdges(previous);
        for (int i = 0; i < edges.size(); i++) {
            if (edges[i].v2 == current) {
                path.push_back(edges[i]);
                break;
            }
        }
        current = prev[current];
    }
    path.reverse();
    return path;
}

// #TODO: return reference ?
list<Edge> searchAStar(const Graph* graph, const int M, const int v_start, const int v_target) {
    // open <-- priority queue ordered by f(v) = g(v) + h(v)
    priority_queue<QueueEntry, vector<QueueEntry>, decltype(QueueCompare)> frontier(QueueCompare);
    int V = graph->size();

    vector<int> g_score(V);
    for (int i = 0; i < V; i++)
        g_score[i] = INF;
    g_score[v_start] = 0;

    vector<int> h(V);
    for (int i = 0; i < V; i++)
        h[i] = 0;    // #TODO: Heuristic function
    h[v_target] = 0; // h(T) always 0

    vector<int> f_score(V);
    for (int i = 0; i < V; i++)
        f_score[i] = INF;
    f_score[v_start] = g_score[v_start] + h[v_start];

    vector<Edge*> prev(V);
    for (int i = 0; i < V; i++)
        prev[i] = -1; // NULL

    frontier.push({v_start, f_score[v_start]});
    while (!frontier.empty()) {
        int current = frontier.top().v;

        if (current == v_target)
            return constructPath(graph, prev, v_start, v_target);

        frontier.pop();

        vector<Edge> edges = graph->getEdges(current);
        for (int i = 0; i < edges.size(); i++) {
            int neighbour = edges[i].v2;

            // Secret Formula
            // int d_score = edges[i].weight + abs((M / 2) - edges[i].weight);
            // int new_score = g_score[current] + d_score;

            int new_score = g_score[current] + edges[i].weight;

            if (new_score < g_score[neighbour]) {
                // This path is better. Record it!
                prev[neighbour] = current;
                g_score[neighbour] = new_score;
                f_score[neighbour] = new_score + h[neighbour];
                frontier.push({neighbour, f_score[neighbour]});
            }
        }
    }

    list<Edge> path;
    return path;
}

void printAnswer(const list<Edge> path, const int M) {
    if (path.empty()) {
        cout << "NO" << endl;
        return;
    }

    for (Edge e : path)
        cout << e.i + 1 << endl;
    cout << betaIneq(path, M) << endl;
}

void printDebug(const list<Edge> path, const int V, const int E, const int M) {
    if (path.empty()) {
        cout << "NO" << endl;
        return;
    }

    std::cout << "----------" << std::endl;
    std::cout << "V: " << V << std::endl;
    std::cout << "E: " << E << std::endl;
    std::cout << "M: " << M << std::endl;
    std::cout << "----------" << std::endl;
    for (Edge e : path) {
        std::cout << edgeToString(e) << std::endl;
    }
    std::cout << "----------" << std::endl;
    std::cout << "S1: " << sum1(path) << std::endl;
    std::cout << "S2: " << sum2(path, M) << std::endl;
    std::cout << "B:  " << betaIneq(path, M) << std::endl;
}

int main() {

    int V;
    int E;
    int M;

    std::cin >> V >> E >> M;

    Graph G = Graph(V);

    int v1, v2, weight;
    while (std::cin >> v1 >> v2 >> weight) {
        G.addEdge(v1 - 1, v2 - 1, weight);
    }

    list<Edge> path = searchAStar(&G, M, 0, V - 1);

    // printAnswer(path, M);

    printDebug(path, V, E, M);
}