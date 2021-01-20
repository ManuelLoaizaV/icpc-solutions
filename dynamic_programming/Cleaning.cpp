//https://codeforces.com/contest/1474/problem/D
#include <bits/stdc++.h>
#include <unistd.h>
#define FAST_IO ios::sync_with_stdio(0);cin.tie(NULL)
#define all(v) (v).begin(),(v).end()
using namespace std;

typedef long long Long;
typedef long double Double;
typedef unsigned long long ULong;
typedef pair<Long, Long> Pair;

const int N = 1e6;
const Long INF = 1e18;
const Double EPS = 1e-9;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
Long random(Long a, Long b) { return uniform_int_distribution<Long> (a, b) (rng); }

void Solve(void) {
  int n;
  cin >> n;
  vector<int> a(n + 2);
  a[0] = a[n + 1] = 0;
  for (int i = 1; i <= n; i++) cin >> a[i];
  vector<pair<int, bool>> left(n + 2), right(n + 2);
  left[0] = {0, true};
  for (int i = 1; i <= n + 1; i++) {
    int rem = left[i - 1].first;
    bool was_valid = left[i - 1].second;
    int sub = min(rem, a[i]);
    left[i].first = a[i] - sub;
    if (!was_valid) {
      left[i].second = false;
    } else {
      left[i].second = (a[i] >= rem);
    }
  }
  right[n + 1] = {0, true};
  for (int i = n; i >= 0; i--) {
    int rem = right[i + 1].first;
    bool was_valid = right[i + 1].second;
    int sub = min(rem, a[i]);
    right[i].first = a[i] - sub;
    if (!was_valid) {
      right[i].second = false;
    } else {
      right[i].second = (a[i] >= rem);
    }
  }
  if (left[n + 1].second || right[0].second) {
    cout << "YES" << '\n';
    return;
  }
  for (int i = 1; i < n; i++) {
    if (left[i - 1].second && right[i + 2].second) {
      vector<int> b;
      b.push_back(left[i - 1].first);
      b.push_back(a[i + 1]);
      b.push_back(a[i]);
      b.push_back(right[i + 2].first);
      int rem = b[0];
      bool is_possible = true;
      for (int j = 1; j < 4; j++) {
        if (b[j] < rem) {
          is_possible = false;
          break;
        }
        rem = b[j] - rem;
      }
      if (is_possible && (rem == 0)) {
        cout << "YES" << '\n';
        return;
      }
    }
  }
  cout << "NO" << '\n';
}

int main(void) {
  FAST_IO;
  int t = 1;
  cin >> t;
  while (t--) Solve();
  return 0;
}

