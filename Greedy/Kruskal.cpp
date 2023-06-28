#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Structure of edge
struct Edge {
    int from, to, weight;
};

// The Union-Find set
class UnionFind {
public:
    UnionFind(int n) {
        count = n;
        parent.resize(n);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }

    int find(int p) {
        while (p != parent[p]) {
            parent[p] = parent[parent[p]];
            p = parent[p];
        }
        return p;
    }

    void unite(int p, int q) {
        int rootP = find(p);
        int rootQ = find(q);
        if (rootP == rootQ) return;
        parent[rootP] = rootQ;
        count--;
    }

    int getCount() const {
        return count;
    }

private:
    vector<int> parent;
    int count;
};

// Kruskal算法实现
vector<Edge> kruskal(vector<vector<pair<int, int>>>& graph) {
    vector<Edge> res;
    int n = graph.size();
    vector<Edge> edges;
    for (int i = 0; i < n; i++) {  // Transform the adjandance list into a set of edges
        for (int j = 0; j < graph[i].size(); j++) {
            Edge edge = {i, graph[i][j].first, graph[i][j].second};
            edges.push_back(edge);
        }
    }
    sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) { return a.weight < b.weight; });  // Sort the edges by the weight in ascending order.
    UnionFind uf(n);
    for (int i = 0; i < edges.size(); i++) {
        Edge edge = edges[i];
        int from = edge.from, to = edge.to, weight = edge.weight;
        if (uf.find(from) != uf.find(to)) {  // Same CC?
            uf.unite(from, to);  // Add the edge to the MST
            res.push_back(edge);
            if (uf.getCount() == 1) break;
        }
    }
    return res;
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, int>>> graph(n);

    int u, v, w;
    for (int i = 0; i < m; i++) {
        cin >> u >> v >> w;
        graph[u - 1].push_back({v - 1, w});
    }

    vector<Edge> MST = kruskal(graph);
    int res = 0;
    for (auto e: MST) {
        res += e.weight;
    }
    cout << res;

    return 0;
}