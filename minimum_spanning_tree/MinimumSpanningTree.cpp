#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

typedef pair<int, int> Pair;

const int N = 2e4;
const int INF = 1e9;

vector<Pair> adj[N];
int min_weight[N], parent[N];

int MST(int n, int root = 0) {
  int total_weight = 0;
  int total_nodes = 0;
  vector<bool> on_tree(n, false);
  for (int i = 0; i < n; i++) min_weight[i] = INF;
  min_weight[root] = 0;
  parent[root] = -1;
  priority_queue<Pair, vector<Pair>, greater<Pair>> pq;
  pq.push({0, root});
  while (!pq.empty()) {
    Pair current = pq.top();
    pq.pop();
    int w = current.first;
    int u = current.second;
    if (on_tree[u]) continue;
    total_weight += w;
    total_nodes++;
    on_tree[u] = true;
    for (Pair edge : adj[u]) {
      int v = edge.first;
      int _w = edge.second;
      if (_w < min_weight[v] && !on_tree[v]) {
        min_weight[v] = _w;
        parent[v] = u;
        pq.push({_w, v});
      }
    }
  }
  if (total_nodes == n) return total_weight;
  return -1;
}

void Solve(int n, int m) {
  for (int i = 0; i < n; i++) adj[i].clear();
  for (int i = 0; i < m; i++) {
    int u, v, w;
    cin >> u >> v >> w;
    adj[u].push_back({v, w});
    adj[v].push_back({u, w});
  }
  int cost = MST(n, 0);
  if (cost == -1) {
    cout << "Impossible" << '\n';
  } else {
    vector<Pair> answer;
    for (int i = 0; i < n; i++) {
      if (parent[i] != -1) {
        answer.push_back({min(i, parent[i]), max(i, parent[i])});
      }
    }
    sort(answer.begin(), answer.end());
    cout << cost << '\n';
    for (Pair edge : answer) {
      cout << edge.first << " " << edge.second << '\n';
    }
  }
}

int main(void) {
  int n, m;
  while (cin >> n >> m) {
    if (n == 0 && m == 0) break;
    Solve(n, m);
  }
  return 0;
}
