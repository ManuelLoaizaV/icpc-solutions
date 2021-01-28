//https://codeforces.com/problemset/problem/598/D
#include <iostream>
using namespace std;

const int N = 1e3;

int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, 1, -1};

struct Graph {
  string museum[N];
  bool is_used[N][N];
  int components, component[N][N], cnt[N * N];

  void Build(int n, int m) {
    components = 0;
    for (int i = 0; i < n; i++) cin >> museum[i];
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        is_used[i][j] = false;
        component[i][j] = 0;
        cnt[i * m + j] = 0;
      }
    }
  }

  bool IsValid(int x, int y) {
    return museum[x][y] == '.';
  }

  void DFS(int x, int y) {
    is_used[x][y] = true;
    component[x][y] = components;
    for (int it = 0; it < 4; it++) {
      int new_x = x + dx[it];
      int new_y = y + dy[it];
      if (!is_used[new_x][new_y]) {
        if (IsValid(new_x, new_y)) {
          DFS(new_x, new_y);
        } else {
          cnt[components]++;
        }
      }
    }
  }
} graph;

int main(void) {
  ios::sync_with_stdio(0);
  cin.tie(nullptr);
  int n, m, q;
  cin >> n >> m >> q;
  graph.Build(n, m);
  while (q--) {
    int u, v;
    cin >> u >> v;
    u--;
    v--;
    if (!graph.is_used[u][v]) {
      graph.DFS(u, v);
      graph.components++;
    }
    cout << graph.cnt[graph.component[u][v]] << '\n';
  }
  return 0;
}
