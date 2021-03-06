//https://codeforces.com/problemset/gymProblem/101992/H
#include <bits/stdc++.h>

using namespace std;

const int N = 1e5;
const int INF = (int) 1.01e9;

vector<pair<int, int>> adj[N];
vector<int> d;

void BFS(int s, int n) {
  d = vector<int>(n, INF);
  d[s] = 0;
  queue<int> q;
  q.push(s);
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    for (auto e : adj[u]) {
      int v = e.first;
      int w = e.second;
      if (d[u] + 1 < d[v]) {
        d[v] = d[u] + 1;
        q.push(v);
      }
    }
  }
}

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  freopen("path.in", "r", stdin);
  int tt;
  cin >> tt;
  while (tt--) {
    int n, m, s, l, k;
    cin >> n >> m >> s >> l >> k;
    --s;
    for (int i = 0; i < n; i++) adj[i].clear();
    while (m--) {
      int u, v, w;
      cin >> u >> v >> w;
      --u; --v;
      adj[u].push_back({v, w});
      adj[v].push_back({u, w});
    }
    BFS(s, n);
    vector<int> valid;
    for (int i = 0; i < n; i++) {
      for (auto e : adj[i]) {
        int j = e.first;
        int w = e.second;
        if (d[i] < k || d[j] < k) valid.push_back(w);
      }
    }
    sort(valid.begin(), valid.end());
    cout << valid.end()[-1] << '\n';
  }
  return 0;
}