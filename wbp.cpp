#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const ll INF = LLONG_MAX / 4;

struct Edge {
    int to; // Destination vertex of the edge
    int id; // Edge ID
    ll w1, w2; // Two weights associated with the edge
};
// Graph represented as an adjacency list of edges
using Graph = vector<vector<Edge>>;

struct Result {
    vector<ll> d1, d2, LB;
    vector<int> B;      // Edge IDs of the best path found
    ll objective = INF; // max(sum1, sum2)
    bool feasible = false;
};

// Dijkstra：// Find shortest paths from target to all vertices using either w1 or w2.
// mode = 1: use w1, mode = 2: use w2
// if next is not nullptr, it will store the next edge on the shortest path for each vertex.
// Output: dist[v] = shortest distance from v to target
// next[v] = next edge on the shortest path from v to target
vector<ll> dijkstra(const Graph& graph, int target, int mode,
                    vector<Edge>* next = nullptr) {
    int n = (int)graph.size();
    vector<ll> dist(n, INF);
    if (next) next->assign(n, Edge{-1, -1, 0, 0});
    // Min-heap priority queue to select the vertex with the smallest distance
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<>> pq;
    dist[target] = 0;
    pq.push({0, target});
    // Dijkstra's algorithm main loop   
    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (d != dist[u]) continue;

        for (const Edge& e : graph[u]) {
            ll w = (mode == 1) ? e.w1 : e.w2;
            if (dist[e.to] > d + w) {
                dist[e.to] = d + w;
                if (next) (*next)[e.to] = Edge{u, e.id, e.w1, e.w2};
                pq.push({dist[e.to], e.to});
            }
        }
    }
    return dist;
}

// Build the path from start to target using the next edges and calculate the objective value.
ll buildPath(const vector<Edge>& next, int start, int target, vector<int>& path) {
    ll sum1 = 0, sum2 = 0;
    path.clear();
    for (int v = start; v != target; v = next[v].to) {
        path.push_back(next[v].id);
        sum1 += next[v].w1;
        sum2 += next[v].w2;
    }
    return max(sum1, sum2);
}

// Preprocessing: Calculate d1, d2, LB; obtain two candidate paths using w1 and w2, and select the better one as B.
Result preprocessing(const Graph& graph) {
    int n = (int)graph.size();
    int target = n - 1;

    Result res;
    vector<Edge> next1, next2; // To store the next edges on the shortest paths for w1 and w2
    // Calculate shortest paths from target to all vertices using w1 and w2
    res.d1 = dijkstra(graph, target, 1, &next1);
    res.d2 = dijkstra(graph, target, 2, &next2);

    res.LB.resize(n); // Lower bound for each vertex
    for (int v = 0; v < n; v++) res.LB[v] = max(res.d1[v], res.d2[v]);
    // Check if there is a feasible path from start (0) to target (n-1)
    res.feasible = (res.d1[0] != INF);
    if (!res.feasible) return res;
    // Build two candidate paths from start to target using the next edges for w1 and w2
    vector<int> path1, path2;
    // Calculate the objective values for both paths
    ll obj1 = buildPath(next1, 0, target, path1);
    ll obj2 = buildPath(next2, 0, target, path2);
    // Select the better path based on the objective value
    if (obj1 <= obj2) {
        res.B = path1;
        res.objective = obj1;
    } else {
        res.B = path2;
        res.objective = obj2;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    ll M;
    // Read the number of vertices, edges, and the maximum weight M from input
    cin >> n >> m >> M;

    Graph graph(n);
    for (int i = 1; i <= m; i++) {
        int u, v;
        ll w;
        // Read the edge endpoints and weight from input
        cin >> u >> v >> w;
        --u; --v;
        // Add edges to the graph with weights w and M - w for the two objectives
        graph[u].push_back({v, i, w, M - w});
        // Add the reverse edge as well since the graph is undirected
        graph[v].push_back({u, i, w, M - w});
    }
    // Preprocess the graph to find the best path and its objective value
    Result res = preprocessing(graph);

    if (!res.feasible) {
        cout << "NO\n";
        return 0;
    }

    for (int id : res.B) cout << id << '\n';
    cout << res.objective << '\n';
    return 0;
}
