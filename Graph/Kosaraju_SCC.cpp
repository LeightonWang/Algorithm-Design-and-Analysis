#include <bits/stdc++.h>
using namespace std;

// 第一次DFS用的函数
void dfs1(int v, vector<int>& marked, vector<vector<int>>& adj, stack<int>& s) {
    marked[v] = 1;
    for (int i = 0; i < adj[v].size(); i++) {
        int neighbor = adj[v][i];
        if (!marked[neighbor]) {
            dfs1(neighbor, marked, adj, s);
        }
    }
    s.push(v);
}

//第二次dfs用的函数
void dfs2(int v, vector<int>& marked, vector<vector<int>>& iadj, vector<int>& scc) {
    marked[v] = 1;
    scc.push_back(v);
    for (int i = 0; i < iadj[v].size(); i++) {
        int neighbor = iadj[v][i];
        if (!marked[neighbor]) {
            dfs2(neighbor, marked, iadj, scc);
        }
    }
}


vector<vector<int>> SCC_kosaraju(int n, vector<vector<int>>& adj) {
    // 在原始图上跑DFS，得finishing time的顺序
    vector<int> marked(n, 0);
    stack<int> finishStack;
    for (int i = 0; i < n; i++) {
        if (!marked[i]) {
            dfs1(i, marked, adj, finishStack);
        }
    }

    // 反转图
    vector<vector<int>> iadj(n); // 反图的邻接表
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < adj[i].size(); j++) {
            int neighbor = adj[i][j];
            iadj[neighbor].push_back(i);
        }
    }

    // 在反转图上跑DFS，以确定开始DFS的点
    vector<vector<int>> sccs;
    marked = vector<int>(n, 0);
    while (!finishStack.empty()) {
        int v = finishStack.top();
        finishStack.pop();
        if (!marked[v]) {
            vector<int> scc;
            dfs2(v, marked, iadj, scc);
            sccs.push_back(scc);
        }
    }
    return sccs;
}

int main() {
    int n, m;
    cin >> n >> m;

    bool noDuplicate = true; // 输入时检测是否有重边，有则不再添加
    vector<vector<int>> adj(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        for (auto x: adj[u - 1]) {
            if (x == v - 1) {
                noDuplicate = false;
                break;
            }
        }
        if (noDuplicate) adj[u - 1].push_back(v - 1);
        noDuplicate = true;
    }

    vector<vector<int>> sccs = SCC_kosaraju(n, adj);

    long long res = 0; long long k;
    for (int i = 0; i < sccs.size(); i++) {
        k = sccs[i].size();
        res += k * (k - 1) / 2; // 对于各个SCC，这样的序数对为 C_size^2
    }

    cout << res;

    return 0;
}
