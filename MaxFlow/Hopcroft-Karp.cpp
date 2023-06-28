#include <bits/stdc++.h>

using namespace std;

void dfs(vector<vector<int>>& adjList, int node, vector<int>& colors, int color) {
    colors[node] = color;

    for (int neighbor : adjList[node]) {
        if (colors[neighbor] == -1) {
            dfs(adjList, neighbor, colors, 1 - color);
        }
    }
}

vector<int> bipartitePartition(vector<vector<int>>& adjList) {
    int numNodes = adjList.size();
    vector<int> colors(numNodes, -1); // Initialize colors to -1

    for (int node = 0; node < numNodes; ++node) {
        if (colors[node] == -1) {
            dfs(adjList, node, colors, 0);
        }
    }

    return colors;
}

struct Edge {
    int to;  // 目标节点
    int capacity;  // 容量
    int flow;  // 流量
    int reverseEdge;  // 反向边
};

// Dinic算法类
class Dinic {
public:
    Dinic(int numNodes) : numNodes(numNodes) {
        graph.resize(numNodes);
        levels.resize(numNodes);
        nextEdge.resize(numNodes);
    }

    void addEdge(int from, int to, int capacity) {
        Edge e1 = {to, capacity, 0, graph[to].size()};
        Edge e2 = {from, 0, 0, graph[from].size()};
        graph[from].push_back(e1);
        graph[to].push_back(e2);
    }

    // BFS to find the level graph
    bool BFS(int source, int sink) {
        levels.assign(numNodes, -1);
        queue<int> q;
        q.push(source);
        levels[source] = 0;

        while (!q.empty()) {
            int current = q.front();
            q.pop();

            for (const Edge& e : graph[current]) {
                if (levels[e.to] == -1 && e.flow < e.capacity) {
                    levels[e.to] = levels[current] + 1;
                    q.push(e.to);
                }
            }
        }

        return levels[sink] != -1;
    }

    int DFS(int current, int sink, int minCapacity) {
        if (current == sink)
            return minCapacity;

        for (int& i = nextEdge[current]; i < graph[current].size(); ++i) {
            Edge& e = graph[current][i];

            if (levels[e.to] == levels[current] + 1 && e.flow < e.capacity) {
                int bottleneck = DFS(e.to, sink, min(minCapacity, e.capacity - e.flow));

                if (bottleneck > 0) {
                    e.flow += bottleneck;
                    graph[e.to][e.reverseEdge].flow -= bottleneck;
                    return bottleneck;
                }
            }
        }

        return 0;
    }

    int maxFlow(int source, int sink) {
        int totalFlow = 0;

        while (BFS(source, sink)) {
            nextEdge.assign(numNodes, 0);
            int flow;

            while ((flow = DFS(source, sink, 1145141919)) > 0) {
                totalFlow += flow;
            }
        }

        return totalFlow;
    }

    vector<int> maxMatching(vector<int> colors) {
        vector<int> mate(numNodes - 2, -1);
        pair<int, int> tmp;
        for (int i = 1; i <= numNodes - 2; i++) {
            if (colors[i - 1] == 1) continue;
            for (auto Edge: graph[i]) {
                if (Edge.flow > 0) {
                    mate[i - 1] = Edge.to - 1;
                    mate[Edge.to - 1] = i - 1;
                }
            }
        }

        return mate;
    }

    
private:
    int numNodes;
    vector<vector<Edge>> graph;
    vector<int> levels;
    vector<int> nextEdge;
};

vector<bool> findVertexCoverFromMatching(const vector<int>& mate, const vector<int>& side, vector<vector<int>> graph, int n) {
    std::vector<bool> visited(n, false);
    std::queue <int> q;
    for (int i = 0; i < n; i++) {
        if (side[i] && mate[i] == -1) {
            visited[i] = true;
            q.push(i);
        }
    }

    while (!q.empty()) { // breadth first search
        int u = q.front();
        q.pop();

        for (int v : graph[u]) if (!visited[v] && v != mate[u]) {
                visited[v] = true;

                int x = mate[v];
                if (x != -1 && !visited[x]) {
                    visited[x] = true;
                    q.push(x);
                }
            }
    }

    std::vector<bool> inCover(n, false);
    for (int i = 0; i < n; i++) {
        inCover[i] = visited[i] xor side[i];
    }

    return inCover;
}



int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> graph(n);
    int u, v;

    for (int i = 0; i < m; i++) {
        cin >> u >> v;
        graph[u - 1].push_back(v - 1);
        graph[v - 1].push_back(u - 1);
    }

    vector<int> colors = bipartitePartition(graph);

    // source: 0; target: n+1
    Dinic dinic(n + 2);
    for (int i = 0; i < n; i++) {
        if (colors[i] == 0) {
            dinic.addEdge(0, i + 1, 1);
            for (auto x: graph[i])
                dinic.addEdge(i + 1, x + 1, 1);
        }
        else {
            dinic.addEdge(i + 1, n + 1, 1);
        }
    }

    int maxMatch = dinic.maxFlow(0, n + 1);
    // cout << maxMatch;

    vector<int> mate = dinic.maxMatching(colors);
    // cout << "Matchings:\n";
    // for (auto p: mate) {
    //     cout << p << ' ';
    // }
    // cout << '\n';

    vector<bool> cover = findVertexCoverFromMatching(mate, colors, graph, n);
    int cnt = 0;
    // cout << "minimum vertex cover:\n";
    for (int i = 0; i < n; i++) {
        if (!cover[i]) {
            cnt++;
        }
    }
    cout << cnt << '\n';

    for (int i = 0; i < n; i++) {
        if (!cover[i]) cout << i + 1 << ' ';
    }

    return 0;
}