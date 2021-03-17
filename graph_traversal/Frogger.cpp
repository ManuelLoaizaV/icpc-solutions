//https://onlinejudge.org/index.php?option=onlinejudge&Itemid=8&category=7&page=show_problem&problem=475
#include <bits/stdc++.h>
using namespace std;

typedef long long Long;
typedef long double Double;
typedef pair<Long, Long> Pair;

const int N = 200;
const Long INF = 1e4;
const Double EPS = 1e-6;

vector<pair<int, Double>> adj[N];
vector<pair<Long, Long>> pairs;
bool used[N];

bool Check(int n, Double m) {
  for (int i = 0; i < n; i++) used[i] = false;
  used[0] = true;
  queue<int> q;
  q.push(0);
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    for (auto e : adj[u]) {
      int v = e.first;
      Double w = e.second;
      if (!used[v] && w <= m) {
        used[v] = true;
        q.push(v);
      }
    }
  }
  return used[1];
}

void AddEdge(int u, int v) {
  Long dx = pairs[u].first - pairs[v].first;
  Long dy = pairs[u].second - pairs[v].second;
  Double dist = sqrt((Double) (dx * dx + dy * dy));
  adj[u].push_back({v, dist});
  adj[v].push_back({u, dist});
}

void Clear(int n) {
  pairs.clear();
  pairs.resize(n);
  for (int i = 0; i < n; i++) adj[i].clear();
}

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int n;
  int tt = 0;
  while (cin >> n) {
    if (n == 0) break;
    tt++;
    cout << "Scenario #" << tt << '\n';
    cout << "Frog Distance = ";
    Clear(n);
    for (int i = 0; i < n; i++) cin >> pairs[i].first >> pairs[i].second;
    for (int i = 0; i < n - 1; i++)
      for (int j = i + 1; j < n; j++)
        AddEdge(i, j);
    Double l = 0;
    Double r = INF;
    while (r - l > EPS) {
      Double m = (l + r) / 2;
      if (Check(n, m)) {
        r = m;
      } else {
        l = m;
      }
    }
    cout << fixed << setprecision(3) << (l + r) / 2 << '\n';
    cout << '\n';
  }
  return 0;
}
