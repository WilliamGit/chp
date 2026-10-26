#include "graph.hpp"

#include <iostream>
#include <list>
#include <optional>
#include <queue>
#include <string>

using namespace std;

const int64_t INF = std::numeric_limits<int64_t>::max();

int64_t sum1(const list<Edge>& path) {
    int64_t sum = 0;
    for (Edge e : path)
        sum += e.weight;
    return sum;
}

int64_t sum2(const list<Edge>& path, const int64_t M) {
    int64_t sum = 0;
    for (Edge e : path)
        sum += (M - e.weight);
    return sum;
}

int64_t betaIneq(const list<Edge>& path, const int64_t M) { return max(sum1(path), sum2(path, M)); }

struct QueueEntry {
    int64_t v; // Vertex index
    int64_t f; // f(v) = g(v) + h(v)
};

auto QueueCompare = [](const QueueEntry e1, const QueueEntry e2) {
    return (e1.f > e2.f); // min heap
};

list<Edge> constructPath(const vector<optional<Edge>>& prev, const int64_t v_start, const int64_t v_target) {
    list<Edge> path;
    int64_t current = v_target;
    while (current != v_start) {
        if (!prev[current])
            return {};

        Edge edge = *prev[current];
        path.push_back(edge);
        current = edge.v1;
    }
    path.reverse();
    return path;
}

list<Edge> searchAStar(const Graph& graph, const int64_t M, const int64_t v_start, const int64_t v_target) {
    // open <-- priority queue ordered by f(v) = g(v) + h(v)
    priority_queue<QueueEntry, vector<QueueEntry>, decltype(QueueCompare)> frontier(QueueCompare);
    int64_t V = graph.size();

    vector<int64_t> S1(V);
    for (int64_t i = 0; i < V; i++)
        S1[i] = 0;

    vector<int64_t> S2(V);
    for (int64_t i = 0; i < V; i++)
        S2[i] = 0;

    vector<int64_t> g_score(V);
    for (int64_t i = 0; i < V; i++)
        g_score[i] = INF;
    g_score[v_start] = 0;

    vector<int64_t> h(V);
    for (int64_t i = 0; i < V; i++)
        h[i] = 0;    // #TODO: Heuristic function
    h[v_target] = 0; // h(T) always 0

    vector<int64_t> f_score(V);
    for (int64_t i = 0; i < V; i++)
        f_score[i] = INF;
    f_score[v_start] = g_score[v_start] + h[v_start];

    vector<optional<Edge>> prev(V);

    frontier.push({v_start, f_score[v_start]});
    while (!frontier.empty()) {
        int64_t current = frontier.top().v;

        if (current == v_target)
            return constructPath(prev, v_start, v_target);

        frontier.pop();

        const vector<Edge>& edges = graph.getEdges(current);
        for (Edge edge : edges) {
            const int64_t neighbour = edge.v2;

            // Secret Formula
            // int64_t d_score = abs((M / 2) - edge.weight);
            // int64_t new_score = g_score[current] + d_score;

            // int64_t new_score = g_score[current] + edge.weight;

            // Option: Keep sums score for each vertex
            int64_t a = S1[current] + edge.weight;
            int64_t b = S2[current] + (M - edge.weight);
            int64_t new_score = max(a, b);

            if (new_score < f_score[neighbour]) {
                // This path is better. Record it!
                prev[neighbour] = edge;
                // g_score[neighbour] = new_score;
                S1[neighbour] = a;
                S2[neighbour] = b;
                f_score[neighbour] = new_score;
                frontier.push({neighbour, f_score[neighbour]});
            }
        }
    }

    list<Edge> path;
    return path;
}

void printAnswer(const list<Edge>& path, const int64_t M) {
    if (path.empty()) {
        cout << "NO" << endl;
        return;
    }

    for (Edge e : path)
        cout << e.i + 1 << endl;
    cout << betaIneq(path, M) << endl;
}

void printDebug(const list<Edge>& path, const int64_t V, const int64_t E, const int64_t M) {
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

    int64_t V;
    int64_t E;
    int64_t M;

    std::cin >> V >> E >> M;

    Graph G = Graph(V);

    int64_t v1, v2, weight;
    while (std::cin >> v1 >> v2 >> weight) {
        G.addEdge(v1 - 1, v2 - 1, weight);
    }

    list<Edge> path = searchAStar(G, M, 0, V - 1);

    printAnswer(path, M);

    // printDebug(path, V, E, M);
}
