#include <iostream>
#include <deque>
#include <vector>
using namespace std;

const int INF = 1e9;
const int N = 1e4;

struct Graph {
  vector<int> adj[N];
  int d[N];  // BFS
  void Clear(int n) {
    for (int i = 0; i < n; i++) {
      adj[i].clear();
    }
  }
  void AddEdge(int u, int v) {
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  void BFS(int s, int n) {
    for (int i = 0; i < n; i++) d[i] = INF;
    d[s] = 0;
    deque<int> tour;
    tour.push_back(s);
    while (!tour.empty()) {
      int u = tour.front();
      tour.pop_front();
      for (int v : adj[u]) {
        if (d[v] == INF) {
          d[v] = d[u] + 1;
          tour.push_back(v);
        }
      }
    }
  }
} g;


int main(void) {
  ios::sync_with_stdio(0);
  cin.tie(nullptr);
  int n;
  cin >> n;
  for (int i = 0; i < n - 1; i++) {
    int u, v;
    cin >> u >> v;
    u--;
    v--;
    g.AddEdge(u, v);
  }
  g.BFS(0, n);
  int mx = 0;
  int id = 0;
  for (int i = 0; i < n; i++) {
    if (g.d[i] > mx) {
      mx = g.d[i];
      id = i;
    }
  }
  g.BFS(id, n);
  mx = 0;
  for (int i = 0; i < n; i++) mx = max(mx, g.d[i]);
  cout << mx << '\n';
  return 0;
}
