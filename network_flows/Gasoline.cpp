//https://codeforces.com/gym/101908/problem/G
#include <bits/stdc++.h>
using namespace std;

typedef long long Long;

const int N = 3e3;
const int T = 1e6 + 5;
const Long INF = 1e18;

Long upperbound = T;

struct Edge {
  int to;
  Long capacity;
  Long timer;
  Long flow;
  Edge* rev;
  Edge(void): rev(nullptr) {}
  Edge(int to, Long capacity, Long timer) : to(to), capacity(capacity), timer(timer), flow(0LL), rev(nullptr) {}
};

struct Graph {
  vector<Edge*> adj[N];
  int level[N];
  int next_edge[N];
  void Clear(int n) {
    for (int i = 0; i < n; i++) {
      adj[i].clear();
      level[i] = -1;
      next_edge[i] = 0;
    }
  }
  void Clear2(int n) {
    for (int i = 0; i < n; i++) {
      for (auto& e : adj[i]) e->flow = 0;
      level[i] = -1;
      next_edge[i] = 0;
    }
  }
  void AddEdge(int u, int v, Long w, Long t, bool directed = true) {
    Edge* forward = new Edge(v, w, t);
    Edge* backward = new Edge(u, 0, t);
    forward->rev = backward;
    backward->rev = forward;
    adj[u].push_back(forward);
    adj[v].push_back(backward);
    if (!directed) {
      forward = new Edge(u, w, t);
      backward = new Edge(v, 0, t);
      forward->rev = backward;
      backward->rev = forward;
      adj[v].push_back(forward);
      adj[u].push_back(backward);
    }
  }
  Long DFS(int u, int t, Long f) {
    if (u == t) return f;
    for (int &i = next_edge[u]; i < adj[u].size(); i++) {
      Edge* e = adj[u][i];
      if (e->timer > upperbound) continue;
      int v = e->to;
      Long residual_capacity = e->capacity - e->flow;
      if (residual_capacity == 0 || level[v] != level[u] + 1) continue;
      Long increase = DFS(v, t, min(f, residual_capacity));
      if (increase > 0) {
        e->flow += increase;
        e->rev->flow -= increase;
        return increase;
      }
    }
    return 0LL;
  }
  bool BFS(int s, int t) {
    deque<int> q;
    q.push_back(s);
    level[s] = 0;
    while (!q.empty()) {
      int u = q.front();
      q.pop_front();
      for (Edge* e : adj[u]) {
        if (e->timer > upperbound) continue;
        int v = e->to;
        Long residual_capacity = e->capacity - e->flow;
        if (level[v] == -1 && residual_capacity > 0) {
          level[v] = level[u] + 1;
          q.push_back(v);
        }
      }
    }
    return level[t] != -1;
  }
  Long MaxFlow(int s, int t, int n) {
    Clear2(n);
    Long answer = 0;
    while (true) {
      fill(level, level + n, - 1);
      if (!BFS(s, t)) break;
      fill(next_edge, next_edge + n, 0);
      Long increase;
      do {
        increase = DFS(s, t, INF);
        answer += increase;
      } while (increase > 0);
    }
    return answer;
  }
} graph;

int main(void) {
  ios::sync_with_stdio(0);
  cin.tie(0);
  int p, r, c;
  cin >> p >> r >> c;
  Long total_demand = 0;
  graph.Clear(p + r + 2);
  // Demanda de las estaciones de gas
  for (int i = 0; i < p; i++) {
    Long d;
    cin >> d;
    total_demand += d;
    graph.AddEdge(0, i + 1, d, 0);
  }
  // Stock en litros de las refinerias
  for (int i = 0; i < r; i++) {
    Long e;
    cin >> e;
    graph.AddEdge(p + 1 + i, p + r + 1, e, 0);
  }
  // Tiempo que tardan los camiones de las estaciones a las refinerias
  for (int i = 0; i < c; i++) {
    int u, v;
    Long t;
    cin >> u >> v >> t;
    graph.AddEdge(u, p + v, INF, t);
  }
  Long maximum_flow = graph.MaxFlow(0, p + r + 1, p + r + 2);
  if (maximum_flow != total_demand) {
    cout << -1 << '\n';
    return 0;
  }
  Long left = 1;
  Long right = T;
  upperbound = 1;
  // TTTTTT
  if (total_demand == graph.MaxFlow(0, p + r + 1, p + r + 2)) {
    cout << 1 << '\n';
    return 0;
  }
  // FFFTTT
  while (right - left > 1) {
    Long m = (left + right) / 2;
    upperbound = m;
    if (total_demand == graph.MaxFlow(0, p + r + 1, p + r + 2)) {
      right = m;
    } else {
      left = m;
    }
  }
  cout << right << '\n';
  return 0;
}
