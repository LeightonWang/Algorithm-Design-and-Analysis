#include <bits/stdc++.h>

using namespace std;

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

private:
    int numNodes;
    vector<vector<Edge>> graph;
    vector<int> levels;
    vector<int> nextEdge;
};

int main() {
    // 构建图
    int n, m;
    cin >> n >> m;
    Dinic dinic(n);

    int u, v, c;
    for (int i = 0; i < m; i++) {
        cin >> u >> v >> c;
        dinic.addEdge(u - 1, v - 1, c);
    }

    // 计算最大流
    int source = 0;
    int sink = n - 1;
    int maxFlow = dinic.maxFlow(source, sink);

    cout << maxFlow << endl;

    return 0;
}
