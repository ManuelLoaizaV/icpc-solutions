//https://codeforces.com/problemset/problem/707/E
#include <bits/stdc++.h>

using namespace std;

typedef long long Long;

const int N = 2e3;

struct FenwickTree {
  Long tree[N + 1][N + 1];
  void Clear(int n, int m) {
    for (int i = 0; i <= n; i++) {
      for (int j = 0; j <= m; j++) {
        tree[i][j] = 0;
      }
    }
  }
  void Update(int i, int y, Long delta) {
    while (i <= N) {
      int j = y;
      while (j <= N) {
        tree[i][j] += delta;
        j += (j & -j);
      }
      i += (i & -i);
    }
  }
  Long Query(int i, int y) {
    Long ans = 0;
    while (i > 0) {
      int j = y;
      while (j > 0) {
        ans += tree[i][j];
        j -= (j & -j);
      }
      i -= (i & -i);
    }
    return ans;
  }
  void Update(int x1, int y1, int x2, int y2, Long delta) {
    Update(x1, y1, delta);
    Update(x2 + 1, y1, -delta);
    Update(x1, y2 + 1, -delta);
    Update(x2 + 1, y2 + 1, delta);
  }
  Long Query(int x1, int y1, int x2, int y2) {
    return Query(x2, y2) - Query(x2, y1 - 1) - Query(x1 - 1, y2) + Query(x1 - 1, y1 - 1);
  }
} ft;

struct Bulb {
  int x;
  int y;
  Long w;
};

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int n, m, k;
  cin >> n >> m >> k;
  vector<vector<Bulb>> garland(k);
  vector<vector<int>> sw(k);
  for (int i = 0; i < k; i++) {
    int len;
    cin >> len;
    for (int j = 0; j < len; j++) {
      int x, y;
      Long w;
      cin >> x >> y >> w;
      garland[i].push_back({x, y, w});
    }
  }
  int q;
  cin >> q;
  vector<vector<int>> ask;
  for (int i = 0; i < q; i++) {
    string t;
    cin >> t;
    if (t[0] == 'A') {
      vector<int> aux(5);
      for (int j = 0; j < 4; j++) cin >> aux[j];
      aux[4] = i;
      ask.push_back(aux);
    } else {
      int id;
      cin >> id;
      --id;
      sw[id].push_back(i);
    }
  }
  vector<Long> ans((int)ask.size(), 0);
  for (int i = 0; i < k; i++) {
    for (auto& bulb : garland[i]) {
      ft.Update(bulb.x, bulb.y, bulb.w);
    }
    bool is_on = true;
    int cur = 0;
    for (int j = 0; j < ask.size(); j++) {
      while (cur < (int)sw[i].size() && sw[i][cur] < ask[j][4]) {
        is_on = !is_on;
        cur++;
      }
      if (is_on) ans[j] += ft.Query(ask[j][0], ask[j][1], ask[j][2], ask[j][3]);
    }
    for (auto& bulb : garland[i]) {
      ft.Update(bulb.x, bulb.y, -bulb.w);
    }
  }
  for (Long a : ans) cout << a << '\n';
  return 0;
}
