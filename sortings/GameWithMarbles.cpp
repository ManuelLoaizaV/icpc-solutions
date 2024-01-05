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
  Long n;
  cin >> n;
  vector<Long> v(n);

  Long max_score = 0LL;
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < n; j++) {
      Long x;
      cin >> x;
      v[j] += x;
      if (i == 1) max_score -= x;
    }
  }

  if (n & 1) {
    max_score--;
  }

  sort(v.begin(), v.end());
  reverse(v.begin(), v.end());
  for (int i = 0; i < n; i += 2) {
    max_score += v[i];
  }
  cout << max_score << ENDL;
}

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int t = 1;
  cin >> t;
  while (t--) Solve();
  return 0;
}
 
