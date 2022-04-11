// https://codeforces.com/contest/1658/problem/E
//#pragma GCC optimize ("Ofast,unroll-loops")
//#pragma GCC target ("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#include <bits/stdc++.h>
#include <unistd.h>
#define debug(x) cout << #x << " = " << x << endl
using namespace std;

typedef long long Long;
typedef long double Double;
typedef unsigned long long ULong;
typedef pair<Long, Long> Pair;

const int N = 1e6;
const Long INF = 1e18;
const Double EPS = 1e-9;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
Long random(Long a, Long b) { return uniform_int_distribution<Long>(a, b)(rng); }

struct Cell {
  int x, y, val;
  bool operator<(const Cell& other) const {
    return val < other.val;
  }
};

int GetManhattan(int x, const set<int>& s) {
  int mn = *s.begin();
  auto it = s.end();
  it--;
  int mx = *it;
  return max(abs(mx - x), abs(mn - x));
}

void Solve(void) {
  int n, k;
  cin >> n >> k;
  vector<Cell> cells(n * n);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cin >> cells[i * n + j].val;
      cells[i * n + j].x = i;
      cells[i * n + j].y = j;
    }
  }
  sort(cells.begin(), cells.end());
  vector<vector<bool>> wins(n, vector<bool>(n, false));

  set<int> sums, diffs;
  for (int i = n * n - 1; i >= 0; i--) {
    int x = cells[i].x;
    int y = cells[i].y;
    int sum = x + y;
    int diff = x - y;
    if (i == n * n - 1) {
      wins[x][y] = true;
    } else {
      int mx = max(GetManhattan(sum, sums), GetManhattan(diff, diffs));
      if (mx <= k) {
        wins[x][y] = true;
      }
    }
    if (wins[x][y]) {
      sums.insert(sum);
      diffs.insert(diff);
    }
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (wins[i][j]) {
        cout << "M";
      } else {
        cout << "G";
      }
    }
    cout << '\n';
  }
}

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int t = 1;
  while (t--) Solve();
  return 0;
}
