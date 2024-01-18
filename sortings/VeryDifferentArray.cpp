// https://codeforces.com/contest/1921/problem/D
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
  Long n, m;
  cin >> n >> m;
  vector<Long> a(n);
  for (int i = 0; i < n; i++) cin >> a[i];
  sort(a.begin(), a.end());
  vector<Long> b(m);
  for (int i = 0; i < m; i++) cin >> b[i];
  sort(b.begin(), b.end());
  Long mx = 0;
  vector<Long> prefixes(n + 2, 0LL), suffixes(n + 2, 0LL);
  for (int i = 1; i <= n; i++) {
    prefixes[i] = prefixes[i - 1];
    int j = i - 1;
    prefixes[i] += abs(a[j] - b[m - 1 - j]);
  }
  for (int i = n; i >= 0; i--) {
    suffixes[i] = suffixes[i + 1];
    int j = i - 1;
    suffixes[i] += abs(a[j] - b[n - i]);
  }
  for (int i = 0; i <= n; i++) {
    Long tmp = prefixes[i] + suffixes[i + 1];
    mx = max(mx, tmp);
  }
  cout << mx << ENDL;
}

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int t = 1;
  cin >> t;
  while (t--) Solve();
  return 0;
}