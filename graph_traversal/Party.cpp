//https://codeforces.com/problemset/problem/115/A
#include <deque>
#include <iostream>
#include <vector>
using namespace std;

const int N = 2e3 + 1;
const int INF = 1e9;

struct Graph {
  vector<int> adj[N];
  int d[N];
  
  void AddEdge(int u, int v) {
    adj[u].push_back(v);
  }

  void BFS(int s) {
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
} graph;

int main(void) {
  ios::sync_with_stdio(0);
  cin.tie(nullptr);
  int n;
  cin >> n;
  vector<int> roots;
  for (int i = 1; i <= n; i++) {
    int p;
    cin >> p;
    if (p != -1) {
      graph.AddEdge(p, i);
    } else {
      roots.push_back(i);
    }
  }
  for (int i = 1; i <= n; i++) graph.d[i] = INF;
  for (int root : roots) graph.BFS(root);
  int mx = 0;
  for (int i = 1; i <= n; i++) mx = max(mx, graph.d[i] + 1);
  cout << mx << '\n';
  return 0;
}
