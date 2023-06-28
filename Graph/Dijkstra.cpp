/* 1342: Shortest Path */
#include <bits/stdc++.h>
using namespace std;

/*
adjandance list
pair[0], pair[1]分别表示到pair[0]有一条权重pair[1]的边
*/
vector<pair<long long, long long>> adj[2501];
long long dist[2501];

void dijkstra(long long s, long long t) {
    // Initialize the open list
    // OL is the open list
    priority_queue<pair<long long, long long>, vector<pair<long long, long long>>, greater<pair<long long, long long>>> OL;
    OL.push({0, s});

    for (int i = 0; i < 2501; i++) dist[i] = LONG_LONG_MAX;
    
    dist[s] = 0;
    
    while (!OL.empty()) {
        long long u = OL.top().second;
        OL.pop();
        // enumerate the neighbors
        for (auto& p : adj[u]) {
            long long v = p.first;
            long long w = p.second;
            // UPDATE
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                OL.push({dist[v], v});
            }
        }
    }
}

int main() {
    long long n, m, s, t;
    long long u, v, w;
    cin >> n >> m >> s >> t;
    
    for (long long i = 0; i < m; i++) {
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }
    
    dijkstra(s, t);
    cout << dist[t];
    
    return 0;
}