#include <iostream>
#include <queue>
#define FAST_IO ios::sync_with_stdio(0);cin.tie(NULL)
using namespace std;

typedef pair<int, int> Pair;

const int N = 3e3;
const int INF = 1e9;

vector<Pair> adj[N];
int min_weight[N];
int parent[N];

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
  return total_weight;
}

int main(void) {
  FAST_IO;
  int n, m;
  cin >> n >> m;
  for (int i = 0; i < m; i++) {
    int u, v, w;
    cin >> u >> v >> w;
    u--;
    v--;
    adj[u].push_back({v, w});
    adj[v].push_back({u, w});
  }
  int root;
  cin >> root;
  cout << MST(n, root - 1) << '\n';
  return 0;
}
