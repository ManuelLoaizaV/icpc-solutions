//https://www.hackerrank.com/challenges/synchronous-shopping/problem
#include <bits/stdc++.h>
using namespace std;

typedef long long Long;
typedef pair<Long, int> Pair;

const int N = 1e3;
const int K = 10;
const int LIM = 1 << K;
const Long INF = 1e14;

int n, m, k;
int t[N];
Long d[N][LIM];
vector<Pair> adj[N];

void TurnOn(int& mask, int bit) {
  mask = mask | (1 << bit);
}

void AddEdge(int u, int v, Long w) {
  adj[u].push_back({v, w});
  adj[v].push_back({u, w});
}

void Dijkstra(int s) {
  int lim = 1 << k;
  for (int i = 0; i < n; i++) 
    for (int mask = 0; mask < lim; mask++)
      d[i][mask] = INF;
  d[s][t[s]] = 0;
  priority_queue<Pair, vector<Pair>, greater<Pair>> q;
  q.push({d[s][t[s]], s * lim + t[s]});
  while (!q.empty()) {
    Pair p = q.top();
    q.pop();
    int u = p.second / lim;
    int mask = p.second % lim;
    Long weight = p.first;
    if (d[u][mask] != weight) continue;
    for (Pair e : adj[u]) {
      int v = e.first;
      Long w = e.second;
      int new_mask = mask | t[v];
      if (d[u][mask] + w < d[v][new_mask]) {
        d[v][new_mask] = d[u][mask] + w;
        q.push({d[v][new_mask], v * lim + new_mask});
      }
    }
  }
}

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cin >> n >> m >> k;
  for (int i = 0; i < n; i++) {
    int len;
    cin >> len;
    for (int j = 0; j < len; j++) {
      int bit;
      cin >> bit;
      bit--;
      TurnOn(t[i], bit);
    }
  }
  for (int i = 0; i < m; i++) {
    int u, v;
    Long w;
    cin >> u >> v >> w;
    u--; v--;
    AddEdge(u, v, w);
  }
  Dijkstra(0);
  int lim = 1 << k;
  Long mn = d[n - 1][lim - 1];
  for (int a = 0; a < lim; a++) {
    for (int b = 0; b < lim; b++) {
      Long tmp = max(d[n - 1][a], d[n - 1][b]);
      if ((a | b) == (lim - 1)) mn = min(mn, tmp);
    }
  }
  cout << mn << '\n';
  return 0;
}
