//https://www.spoj.com/problems/TAXI/en/
#include <bits/stdc++.h>
using namespace std;

typedef long long Long;
typedef pair<Long, Long> Pair;

const int N = 1e3;
const Long INF = 1e18;

struct Edge {
  int to;
  Long capacity;
  Long flow;
  Edge* rev;
  Edge(void): rev(nullptr) {}
  Edge(int to, Long capacity) : to(to), capacity(capacity), flow(0LL), rev(nullptr) {}
};
struct Graph {
  vector<Edge*> adj[N];
  int level[N];
  int next_edge[N];
  void Clear(int n = N) {
    for (int i = 0; i < n; i++) {
      adj[i].clear();
      level[i] = -1;
      next_edge[i] = 0;
    }
  }
  void AddEdge(int u, int v, Long w, bool directed) {
    Edge* forward = new Edge(v, w);
    Edge* backward = new Edge(u, 0);
    forward->rev = backward;
    backward->rev = forward;
    adj[u].push_back(forward);
    adj[v].push_back(backward);
    if (!directed) {
      forward = new Edge(u, w);
      backward = new Edge(v, 0);
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

Long Distance(const Pair& p1, const Pair& p2) {
  return abs(p1.first - p2.first) + abs(p1.second - p2.second);
}

void Solve(void) {
  int p, t;
  cin >> p >> t;
  Long s, c;
  cin >> s >> c;
  vector<Pair> people(p), taxis(t);
  for (int i = 0; i < p; i++) cin >> people[i].first >> people[i].second;
  for (int i = 0; i < t; i++) cin >> taxis[i].first >> taxis[i].second;
  graph.Clear(t + p + 2);
  for (int i = 1; i <= t; i++) graph.AddEdge(0, i, 1, true);
  for (int i = 0; i < t; i++) {
    for (int j = 0; j < p; j++) {
      Long distance = Distance(taxis[i], people[j]);
      if (c * s >= 200 * distance) graph.AddEdge(i + 1, t + 1 + j, 1, true);
    }
  }
  for (int i = 1; i <= p; i++) graph.AddEdge(t + i, t + p + 1, 1, true);
  cout << graph.MaxFlow(0, t + p + 1, t + p + 2) << '\n';
}

int main(void) {
  ios::sync_with_stdio(0);
  cin.tie(0);
  int t;
  cin >> t;
  while (t--) Solve();
  return 0;
}
