#include <iostream>
#include <queue>
#include <set>
#include <utility>
#include <vector>
#define FAST_IO ios::sync_with_stdio(0);cin.tie(nullptr)
using namespace std;

typedef long long Long;

const Long INF = 1e12;
const int N = 1e5;

vector<pair<int, Long>> adj[N];
Long d[N];
int p[N];

void Dijkstra(int n, const vector<int>& subs) {
  for (int i = 0; i < n; i++) {
    d[i] = INF;
    p[i] = -1;
  }
  priority_queue<pair<Long, int>,
    vector<pair<Long, int>>,
    greater<pair<Long, int>>> q;
  for (int u : subs) {
    p[u] = u;
    d[u] = 0;
    q.push({0, u});
  } 
  while (!q.empty()) {
    pair<Long, int> path = q.top();
    int u = path.second;
    q.pop();
    if (d[u] != path.first) continue;
    for (auto e : adj[u]) {
      int v = e.first;
      Long w = e.second;
      if (d[u] + w < d[v]) {
        d[v] = d[u] + w;
        p[v] = p[u];
        q.push({d[v], v});
      }
    }
  }
}

int main(void) {
  FAST_IO;
  int n, k, l;
  cin >> n >> k >> l;
  vector<int> subs;
  set<int> uni;
  bool has_repeated = false;
  for (int i = 0; i < n; i++) {
    int who;
    cin >> who;
    who--;
    subs.push_back(who);
    if (uni.count(who) > 0) has_repeated = true;
    uni.insert(who);
  }
  for (int i = 0; i < l; i++) {
    int u, v;
    Long w;
    cin >> u >> v >> w;
    u--;
    v--;
    adj[u].push_back({v, w});
    adj[v].push_back({u, w});
  }

  if (has_repeated) {
    cout << 0 << '\n';
    return 0;
  }

  Dijkstra(k, subs);
  Long ans = INF;
  for (int u = 0; u < k; u++) {
    for (auto e : adj[u]) {
      int v = e.first;
      Long w = e.second;
      if (p[u] != p[v]) ans = min(ans, d[u] + w + d[v]);
    }
  }
  ans *= 3;
  cout << ans << '\n';
  return 0;
}
