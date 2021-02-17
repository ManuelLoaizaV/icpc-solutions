//https://cses.fi/problemset/task/1711/
#include <bits/stdc++.h>
using namespace std;

typedef long long Long;

const int N = 600;
const Long INF = 1e18;

struct Graph {
  vector<int> adj[N];
  Long capacity[N][N], flow[N][N];
  int level[N], next_edge[N];
  bool added[N][N];
  void Clear(int n = N) {
    for (int i = 0; i < n; i++) {
      adj[i].clear();
      level[i] = -1;
      next_edge[i] = 0;
      for (int j = 0; j < n; j++) {
        capacity[i][j] = 0;
        flow[i][j] = 0;
        added[i][j] = false;
      }
    }
  }
  void AddEdge(int u, int v, Long w, bool directed) {
    if (!added[min(u, v)][max(u, v)]) {
      adj[u].push_back(v);
      adj[v].push_back(u);
    }
    added[min(u, v)][max(u, v)] = true;
    capacity[u][v] += w;
    if (!directed) capacity[v][u] += w;
  }
  Long DFS(int u, int t, Long f) {
    if (u == t) return f;
    for (int& i = next_edge[u]; i < adj[u].size(); i++) {
      int v = adj[u][i];
      Long residual_capacity = capacity[u][v] - flow[u][v];
      if (residual_capacity == 0 || level[v] != level[u] + 1) continue;
      Long increase = DFS(v, t, min(f, residual_capacity));
      if (increase > 0) {
        flow[u][v] += increase;
        flow[v][u] -= increase;
        return increase;
      }
    }
    return 0;
  }
  bool BFS(int s, int t) {
    deque<int> q;
    q.push_back(s);
    level[s] = 0;
    while (!q.empty()) {
      int u = q.front();
      q.pop_front();
      for (int v : adj[u]) {
        Long residual_capacity = capacity[u][v] - flow[u][v];
        if (level[v] == -1 && residual_capacity > 0) {
          level[v] = level[u] + 1;
          q.push_back(v);
        }
      }
    }
    return level[t] != -1;
  }
  Long MaxFlow(int s, int t, int n) {
    Long ans = 0;
    while (true) {
      fill(level, level + n, -1);
      if (!BFS(s, t)) break;
      fill(next_edge, next_edge + n, 0);
      Long increase;
      do {
        increase = DFS(s, t, INF);
        ans += increase;
      } while (increase > 0);
    }
    return ans;
  }
} graph;

set<int> saturated[N];
int parent[N];
bool is_used[N];

void DFS(int u, int p) {
  parent[u] = p;
  is_used[u] = true;
  for (auto v : saturated[u]) if (!is_used[v]) DFS(v, u);
}

int main(void) {
  ios::sync_with_stdio(0);
  cin.tie(0);
  int n, m;
  cin >> n >> m;
  graph.Clear(n);
  while (m--) {
    int u, v;
    cin >> u >> v;
    u--;
    v--;
    graph.AddEdge(u, v, 1LL, true);
  }
  int max_flow = graph.MaxFlow(0, n - 1, n);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (graph.capacity[i][j] > 0 && graph.flow[i][j] == 1) {
        saturated[i].insert(j);
      }
    }
  }
  cout << max_flow << '\n';
  for (int i = 0; i < max_flow; i++) {
    for (int i = 0; i < n; i++) {
      parent[i] = -1;
      is_used[i] = false;
    }
    DFS(0, -1);
    vector<int> path;
    int last = n - 1;
    while (last != -1) {
      path.push_back(last);
      if (last != 1) saturated[parent[last]].erase(last);
      last = parent[last];
    }
    reverse(path.begin(), path.end());
    int len = path.size();
    cout << len << '\n';
    for (int i = 0; i < len; i++) {
      if (i > 0) cout << " ";
      cout << path[i] + 1;
    }
    cout << '\n';
  }
  return 0;
}
