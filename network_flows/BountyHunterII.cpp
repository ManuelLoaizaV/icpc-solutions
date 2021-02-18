//https://codeforces.com/gym/100753/attachments
#include <bits/stdc++.h>
using namespace std;

typedef long long Long;

const int N = 2e3 + 5;
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

int main(void) {
  ios::sync_with_stdio(0);
  cin.tie(0);
  int n;
  cin >> n;
  graph.Clear(2 * n + 2);
  for (int i = 0; i < n; i++) {
    int k;
    cin >> k;
    for (int j = 0; j < k; j++) {
      int to;
      cin >> to;
      graph.AddEdge(i, n + to, 1, true);
    }
  }
  for (int i = 0; i < n; i++) graph.AddEdge(2 * n, i, 1, true);
  for (int i = 0; i < n; i++) graph.AddEdge(n + i, 2 * n + 1, 1, true);
  cout << n - graph.MaxFlow(2 * n, 2 * n + 1, 2 * n + 2) << '\n';
  return 0;
}
