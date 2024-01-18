// https://codeforces.com/problemset/problem/977/F
#include <algorithm>
#include <bits/stdc++.h>

#ifndef ONLINE_JUDGE
#define debug(x) cerr << "[" << #x << "]: " << x << endl
#else
#define debug(x) 69
#endif

using namespace std;

typedef long long Long;
typedef long double Double;
typedef pair<Long, Long> Pair;

const int N = 1e6;
const Long MOD = 998244353LL;
const Long INF = 1e18;
const Double PI = acos(-1);
const Double EPS = 1e-9;

const char A = 'a';
const char ZERO = '0';
const char ENDL = '\n';

const string YES = "YES";
const string NO = "NO";

void Solve(void) {
  int n;
  cin >> n;
  vector<int> a(n);
  for (int i = 0; i < n; i++) cin >> a[i];
  map<int, vector<int>> positions;
  for (int i = 0; i < n; i++) {
    positions[a[i]].push_back(i);
  }

  // dp(i) = longest contiguous increasing subsequence in [i, n) start at i
  vector<int> dp(n, 1);
  for (int i = n - 2; i >= 0; i--) {
    if (positions.count(a[i] + 1) == 0) continue;
    auto next = upper_bound(positions[a[i] + 1].begin(), positions[a[i] + 1].end(), i);
    if (next == positions[a[i] + 1].end()) continue;
    dp[i] += dp[*next];
  }

  int start = max_element(dp.begin(), dp.end()) - dp.begin();
  int lcis = dp[start];
  cout << lcis << ENDL;
  for (int i = 0; i < lcis; i++) {
    if (i > 0) cout << " ";
    cout << start + 1;
    if (i == lcis - 1) break;
    start = *upper_bound(positions[a[start] + 1].begin(), positions[a[start] + 1].end(), start);
  }
  cout << ENDL;
}

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int t = 1;
  // cin >> t;
  while (t--) Solve();
  return 0;
}
