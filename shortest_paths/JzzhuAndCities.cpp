//https://codeforces.com/problemset/problem/449/B
#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
using namespace std;

typedef long long Long;

const Long INF = 1e18;
const int N = 1e5;

struct Edge {
  int v;
  Long w;
  bool t;
  bool operator > (const Edge& other) const {
    if (w != other.w) return w > other.w;
    return t;
  }
};

vector<Edge> adj[N];
Long d[N];
bool done[N];

void AddEdge(int u, int v, Long w, bool train) {
  adj[u].push_back({v, w, train});
  adj[v].push_back({u, w, train});
}

int Dijkstra(int s) {
  int cnt = 0;
  for (int i = 0; i < N; i++) d[i] = INF;
  d[s] = 0;
  priority_queue<Edge, vector<Edge>, greater<Edge>> q;
  q.push({s, 0, false});
  while (!q.empty()) {
    Edge path = q.top();
    int u = path.v;
    q.pop();
    if (done[u]) continue;
    done[u] = true;
    if (path.t) cnt++;
    for (Edge e : adj[u]) {
      int v = e.v; Long w = e.w; bool t = e.t;
      if (d[u] + w < d[v]) {
        d[v] = d[u] + w;
        q.push({v, d[v], t});
      } else if (d[u] + w == d[v] && !done[v]) {
        q.push({v, d[v], t});
      }
    }
  }
  return cnt;
}

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int n, m, k;
  cin >> n >> m >> k;
  for (int i = 0; i < m; i++) {
    int u, v;
    Long w;
    cin >> u >> v >> w;
    u--;
    v--;
    AddEdge(u, v, w, false);
  }
  for (int i = 0; i < k; i++) {
    int s;
    Long w;
    cin >> s >> w;
    s--;
    AddEdge(0, s, w, true);
  }
  cout << k - Dijkstra(0) << '\n';
  return 0;
}
