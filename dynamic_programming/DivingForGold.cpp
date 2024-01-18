// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=931
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

const int N = 30;
const int T = 1000;
const Long MOD = 998244353LL;
const Long INF = 1e18;
const Double PI = acos(-1);
const Double EPS = 1e-9;

const char A = 'a';
const char ZERO = '0';
const char ENDL = '\n';

const string YES = "YES";
const string NO = "NO";

bool done[T + 1][N];
Long dp[T + 1][N];
vector<int> solution;
void Clear(int t, int n) {
  for (int i = 0; i <= t; i++)
    for (int j = 0; j < n; j++)
      done[i][j] = false;
  solution.clear();
}

// dp(t, i) = max gold with treasures [i, n) with time t
Long DP(Long t, Long i, const Long& w, const vector<Long>& d, const vector<Long>& v) {
  if (i == (int)d.size()) return 0;
  if (done[t][i]) return dp[t][i];
  dp[t][i] = DP(t, i + 1, w, d, v);
  Long remaining_time = t - 3LL * w * d[i];
  if (remaining_time >= 0) {
    dp[t][i] = max(dp[t][i], v[i] + DP(remaining_time, i + 1, w, d, v));
  }
  done[t][i] = true;
  return dp[t][i];
}

void Reconstruct(Long t, Long i, const Long& w, const vector<Long>& d, const vector<Long>& v) {
  if (i == (int)d.size()) return;
  Long remaining_time = t - 3LL * w * d[i];
  if (
    remaining_time >= 0 &&
    DP(t, i, w, d, v) == v[i] + DP(remaining_time, i + 1, w, d, v)
  ) {
    solution.push_back(i);
    Reconstruct(remaining_time, i + 1, w, d, v);
  } else {
    Reconstruct(t, i + 1, w, d, v);
  }
}

void Solve(Long t, Long w) {
  Long n;
  cin >> n;
  vector<Long> d(n);
  vector<Long> v(n);
  for (int i = 0; i < n; i++) cin >> d[i] >> v[i];

  Clear(t, n);
  cout << DP(t, 0, w, d, v) << ENDL;
  Reconstruct(t, 0, w, d, v);
  int solution_size = (int)solution.size();
  cout << solution_size << ENDL;
  for (int i = 0; i < solution_size; i++) {
    int j = solution[i];
    cout << d[j] << " " << v[j] << ENDL;
  }
}

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  Long t, w;
  bool first_test = true;
  while (cin >> t >> w) {
    if (first_test) {
      first_test = false;
    } else {
      cout << ENDL;
    }
    Solve(t, w);
  }
  return 0;
}
