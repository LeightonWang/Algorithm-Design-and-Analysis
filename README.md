# Algorithm: Design & Analysis

The repository of my code for SJTU AI2615: Algorithm Design and Analysis (2023 spring)

上海交通大学AI2615: 算法设计与分析（2023年春季学期） 个人代码仓库

## Compile
What is stored in this repository is code for each OJ exercise. Complie each cpp file respectively in the method you like.

## Introduction to the code

### Divide and Conquer
Code for 3 problems of divide and conquer.

### Graph
2 algorithms implemented:
- Dijkstra: Finding the shortest path
- Kosaraju: Finding *Strong Connected Components* (SCC) of a given directed graph.

### Greedy
2 algorithms implemented:
- Kruskal: Finding the minimum spanning tree for given undirected graphs.
- End-Time-First-Schedule

### DP
Since my limited command on dynamic programming, the only code here is the easiest version.
- Longest Descending Subsequences
    - Denote $f(i)$ the length of the longest descending subsequence who ends at $a_i$. The transition is
    $$f(i)=\max \left( 1,\max_{j< i, a_j >a_i} \{f(j)+1\} \right)$$
    - Time complexity: $O(n^2)$
    - Cannot pass all the test cases.Can be improved by priority queue.

### Max Flow
2 algorithms implemented:
- **Dinic**: Finding the maximum flow on a network graph.
- **Hopcroft-Karp**: Dinic algorithm on *bipartite graphs* to find max match of the graph. The code uses the algorithm to compute the ***largest independent set*** by computing the vertex cover through the max match.
