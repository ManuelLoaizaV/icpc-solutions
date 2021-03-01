//https://codeforces.com/problemset/problem/12/D
#include <bits/stdc++.h>
using namespace std;

const int N = 5e5 + 10;
const int INF = 1e9;

struct Lady {
  int a, b, c;
  bool operator < (const Lady& other) {
    if (a != other.a) return a < other.a;
    if (b != other.b) return b < other.b;
    return c < other.c;
  }
};

struct FenwickTree {
  int tree[N + 1];
  FenwickTree(void) {
    for (int i = 0; i <= N; i++) tree[i] = -INF;
  }
  void Update(int i, int val) {
    i = N - i;
    while (i <= N) {
      tree[i] = max(tree[i], val);
      i += (i & -i);
    }
  }
  int Query(int i) {
    i = N - i;
    int ans = -INF;
    while (i > 0) {
      ans = max(ans, tree[i]);
      i -= (i & -i);
    }
    return ans;
  }
} ft;

void Compress(vector<int>& a) {
  int n = a.size();
  vector<pair<int, int>> pairs;
  for (int i = 0; i < n; i++) pairs.push_back({a[i], i});
  sort(pairs.begin(), pairs.end());
  int nxt = 1;
  for (int i = 0; i < n; i++) {
    if (i > 0 && pairs[i].first != pairs[i - 1].first) nxt++;
    a[pairs[i].second] = nxt;
  }
}

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n;
  debug(n);
  vector<vector<int>> ladies(3, vector<int>(n));
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < n; j++) {
      debug(i, j);
      cin >> ladies[i][j];
    }
  }
  for (int i = 0; i < 3; i++) Compress(ladies[i]);
  vector<Lady> l(n);
  for (int i = 0; i < n; i++) {
    l[i].a = ladies[0][i];
    l[i].b = ladies[1][i];
    l[i].c = ladies[2][i];
  }
  sort(l.begin(), l.end());
  int ans = 0;
  for (int i = n - 1; i >= 0; i--) {
    int j = i;
    while (j >= 0 && l[j].a == l[i].a) j--;
    j++;
    for (int k = j; k <= i; k++) {
      int mx = ft.Query(l[k].b + 1);
      if (mx > l[k].c) ans++;
    }
    for (int k = j; k <= i; k++) {
      ft.Update(l[k].b, l[k].c);
    }
    i = j;
  }
  cout << ans << '\n';
  return 0;
}

