// https://codeforces.com/contest/1921/problem/F
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

const int N = 1e5;
const int S = 317;
const Long MOD = 998244353LL;
const Long INF = 1e18;
const Double PI = acos(-1);
const Double EPS = 1e-9;

const char A = 'a';
const char ZERO = '0';
const char ENDL = '\n';

const string YES = "YES";
const string NO = "NO";

Long prefix_sums[N][S];
Long prefix_sums_sums[N][S];

void Solve(void) {
  int n, Q;
  cin >> n >> Q;

  vector<Long> a(n);
  for (int i = 0; i < n; i++) cin >> a[i];

  int n_sqrt = sqrt(n);
  for (int s = 1; s <= n_sqrt; s++) {
    for (int i = 0; i < n; i++) {
      if (i - s >= 0) {
        prefix_sums[i][s] = prefix_sums[i - s][s];
        prefix_sums_sums[i][s] = prefix_sums_sums[i - s][s];
      } else {
        prefix_sums[i][s] = 0;
        prefix_sums_sums[i][s] = 0;
      }
      prefix_sums[i][s] += a[i];
      prefix_sums_sums[i][s] += prefix_sums[i][s];
    }
  }

  for (int q = 0; q < Q; q++) {
    int s, d, k;
    cin >> s >> d >> k;
    s--;
    Long sum = 0LL;
    if (d <= n_sqrt) {
      sum = prefix_sums[s + (k - 1) * d][d] * (Long)k;
      if (s + (k - 2) * d >= 0) {
        sum -= prefix_sums_sums[s + (k - 2) * d][d];
      }
      if (s - 2 * d >= 0) {
        sum += prefix_sums_sums[s - 2 * d][d];
      }
    } else {
      for (Long i = 0; i < k; i++) {
        sum += a[s + i * d] * (i + 1LL);
      }
    }
    if (q > 0) cout << " ";
    cout << sum;
  }
  cout << ENDL;
}

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int t = 1;
  cin >> t;
  while (t--) Solve();
  return 0;
}