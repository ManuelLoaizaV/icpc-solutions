//https://codeforces.com/problemset/problem/1076/E
#include <iostream>
#include <utility>
#include <vector>
#define FAST_IO ios::sync_with_stdio(0);cin.tie(nullptr)
using namespace std;

typedef long long Long;
typedef pair<int, int> Pair;

const int N = 3e5 + 5;

vector<int> adj[N];
vector<pair<int, Long>> upd[N];
Long ans[N];

struct FenwickTree {
  Long tree[N + 1];

  void Update(int i, Long delta) {
    while (i <= N) {
      tree[i] += delta;
      i += (i & -i);
    }
  }

  Long Query(int i) {
    Long ans = 0;
    while (i > 0) {
      ans += tree[i];
      i -= (i & -i);
    }
    return ans;
  }
} ft;

void DFS(int u, int h = 1, int p = -1) {
  // Actualizo
  for (auto e : upd[u]) {
    ft.Update(h, e.second);
    ft.Update(h + e.first + 1, -e.second);
  }
  // Consulto
  ans[u] = ft.Query(h);
  for (int v : adj[u]) if (v != p) DFS(v, h + 1, u);
  // Desactualizo
  for (auto e : upd[u]) {
    ft.Update(h, -e.second);
    ft.Update(h + e.first + 1, e.second);
  }
}

int main(void) {
  FAST_IO;
  int n;
  cin >> n;
  for (int i = 0; i < n - 1; i++) {
    int x, y;
    cin >> x >> y;
    x--;
    y--;
    adj[x].push_back(y);
    adj[y].push_back(x);
  }
  int q;
  cin >> q;
  while (q--) {
    int v, d;
    Long x;
    cin >> v >> d >> x;
    v--;
    upd[v].push_back({d, x});
  }
  DFS(0);
  for (int i = 0; i < n; i++) {
    if (i > 0) cout << " ";
    cout << ans[i];
  }
  cout << '\n';
  return 0;
}
