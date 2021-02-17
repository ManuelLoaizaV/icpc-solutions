//https://open.kattis.com/problems/thekingofthenorth
#include <bits/stdc++.h>
using namespace std;

typedef long long Long;
typedef pair<int, int> Pair;

const int N = 18e4 + 1;
const Long INF = 1e10;

int R, C;

int GetHash(const Pair& p) {
  return p.first * C + p.second;
}

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
  // Anadir arista interior del nodo
  void AddInternalEdge(const Pair& node, Long w) {
    int x = node.first;
    int y = node.second;
    int u = GetHash(node);
    int v = u + R * C;
    Edge* forward = new Edge(v, w);
    Edge* backward = new Edge(u, 0);
    forward->rev = backward;
    backward->rev = forward;
    adj[u].push_back(forward);
    adj[v].push_back(backward);
  }
  // Anadir arista entre nodos comunes
  void AddEdge(const Pair& node1, const Pair& node2) {
    int u_in = GetHash(node1);
    int u_out = u_in + R * C;
    int v_in = GetHash(node2);
    int v_out = v_in + R * C;
    
    Edge* forward = new Edge(v_in, INF);
    Edge* backward = new Edge(u_out, 0);
    forward->rev = backward;
    backward->rev = forward;
    adj[u_out].push_back(forward);
    adj[v_in].push_back(backward);

    forward = new Edge(u_in, INF);
    backward = new Edge(v_out, 0);
    forward->rev = backward;
    backward->rev = forward;
    adj[v_out].push_back(forward);
    adj[u_in].push_back(backward);
  }
  void AddEdgeToKing(const Pair& node, int king) {
    int from = GetHash(node) + R * C;
    Edge* forward = new Edge(king, INF);
    Edge* backward = new Edge(from, 0);
    forward->rev = backward;
    backward->rev = forward;
    adj[from].push_back(forward);
    adj[king].push_back(backward);
  }
  void AddEdgeFromExterior(const Pair& node, int exterior) {
    int to = GetHash(node);
    Edge* forward = new Edge(to, INF);
    Edge* backward = new Edge(exterior, 0);
    forward->rev = backward;
    backward->rev = forward;
    adj[exterior].push_back(forward);
    adj[to].push_back(backward);
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

int dx[4] = {1, 0};
int dy[4] = {0, 1};

int main(void) {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cin >> R >> C;
  vector<vector<Long>> kingdom(R, vector<Long> (C, 0));
  for (int i = 0; i < R; i++) {
    for (int j = 0; j < C; j++) {
      cin >> kingdom[i][j];
    }
  }

  Pair king;
  cin >> king.first >> king.second;
  auto IsValid = [&](const Pair& p) {
    return 0 <= p.first && p.first < R && 0 <= p.second && p.second < C;
  };

  graph.Clear(2 * R * C + 1);
  // Creo las aristas dentro de un mismo nodo
  for (int i = 0; i < R; i++) {
    for (int j = 0; j < C; j++) {
      Pair current = {i, j};
      if (current != king) {
        graph.AddInternalEdge(current, kingdom[i][j]);
      }
    }
  }

  int king_hash = GetHash(king);
  // Creo las aristas entre nodos
  for (int i = 0; i < R; i++) {
    for (int j = 0; j < C; j++) {
      Pair current = {i, j};
      for (int k = 0; k < 2; k++) {
        Pair nxt = {i + dx[k], j + dy[k]};
        if (!IsValid(nxt)) continue;
        if (current == king) {
          graph.AddEdgeToKing(nxt, king_hash);
        } else if (nxt == king) {
          graph.AddEdgeToKing(current, king_hash);
        } else {
          graph.AddEdge(current, nxt);
        }
      }
    }
  }
  int exterior = 2 * R * C;
  // Creo las aristas del exterior a los bordes
  for (int i = 0; i < R; i++) {
    for (int j = 0; j < C; j++) {
      if (i == 0 || j == 0) {
        graph.AddEdgeFromExterior({i, j}, exterior);
      }
    }
  }
  Long ans = kingdom[king.first][king.second];
  ans = min(ans, graph.MaxFlow(2 * R * C, GetHash(king), 2 * R * C + 1));
  cout << ans << '\n';
  return 0;
}
