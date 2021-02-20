//https://atcoder.jp/contests/abc192/tasks/abc192_e
#include <bits/stdc++.h>
#include <unistd.h>
#define FAST_IO ios::sync_with_stdio(0);cin.tie(NULL)
#define all(v) (v).begin(),(v).end()
using namespace std;

typedef long long Long;
typedef long double Double;
typedef unsigned long long ULong;
typedef pair<Long, Long> Pair;

const int N = 1e5;
const Long INF = 1e18;
const Double EPS = 1e-9;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
Long random(Long a, Long b) { return uniform_int_distribution<Long> (a, b) (rng); }

struct Edge {
  int to;
  Long t, k;
};

vector<Edge> adj[N];
Long d[N];

void AddEdge(int a, int b, Long t, Long k) {
  adj[a].push_back({b, t, k});
  adj[b].push_back({a, t, k});
}

void Dijkstra(int s, int n) {
  for (int i = 0; i < n; i++) d[i] = INF;
  d[s] = 0;
  priority_queue<Pair, vector<Pair>, greater<Pair>> q;
  q.push({0, s});
  while (!q.empty()) {
    Pair path = q.top();
    int u = path.second;
    q.pop();
    if (d[u] != path.first) continue;
    for (auto& e : adj[u]) {
      int v = e.to;
      Long w = e.t;
      Long k = e.k;
      Long rem = d[u] % k;
      if (rem > 0) w += (k - rem);
      if (d[u] + w < d[v]) {
        d[v] = d[u] + w;
        q.push({d[v], v});
      }
    }
  }
}

void Solve(void) {
  Long n, m, x, y;
  cin >> n >> m >> x >> y;
  x--;
  y--;
  for (int i = 0; i < m; i++) {
    Long a, b, t, k;
    cin >> a >> b >> t >> k;
    a--;
    b--;
    AddEdge(a, b, t, k);
  }
  Dijkstra(x, n);
  if (d[y] == INF) {
    cout << -1 << '\n';
  } else {
    cout << d[y] << '\n';
  }
}

int main(void) {
  FAST_IO;
  int t = 1;
  //cin >> t;
  while (t--) Solve();
  return 0;
}

