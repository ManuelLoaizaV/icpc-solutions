#include <bits/stdc++.h>
using namespace std;

typedef long long Long;

const Long MOD = 998244353;

Long Add(Long x, Long y) {
  return (x + y) % MOD;
}

Long Mul(Long x, Long y) {
  return (x * y) % MOD;
}

const int N = 3e5;

bool is_possible = true;
Long pot[N + 1];
Long current = 0;

struct Graph {
  vector<int> adj[N];
  int in[N], out[N], color[N], timer;  // DFS
  void Clear(int n) {
    for (int i = 0; i < n; i++) {
      adj[i].clear();
      in[i] = out[i] = 0;
      color[i] = 0;
    }
    is_possible = true;
    timer = 0;
  }
  void AddEdge(int u, int v) {
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  Long DFS(int u, int c = 0) {
    Long cnt = 1LL;
    if (c & 1) current++;
    in[u] = ++timer;
    color[u] = c;
    for (int v : adj[u]) {
      if (in[v] == 0) {
        cnt += DFS(v, 1 - c);  // tree edge
      } else {
        if (color[v] == c) is_possible = false;
      }
    }
    out[u] = ++timer;
    return cnt;
  }
} g;


void Solve(void) {
  int n, m;
  cin >> n >> m;
  g.Clear(n);
  for (int i = 0; i < m; i++) {
    int u, v;
    cin >> u >> v;
    u--;
    v--;
    g.AddEdge(u, v);
  }
  Long answer = 1;
  for (int i = 0; i < n; i++) {
    if (g.in[i] == 0) {
      current = 0;
      Long size = g.DFS(i);
      answer = Mul(answer, Add(pot[current], pot[size - current]));
    }
  }
  if (is_possible) {
    cout << answer << '\n';
  } else {
    cout << 0 << '\n';
  }
}

int main(void) {
  ios::sync_with_stdio(0);
  cin.tie(nullptr);
  pot[0] = 1LL;
  for (int i = 1; i <= N; i++) pot[i] = Mul(pot[i - 1], 2LL);
  int t;
  cin >> t;
  while (t--) Solve();
  return 0;
}
