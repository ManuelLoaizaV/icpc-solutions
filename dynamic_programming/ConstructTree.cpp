// https://codeforces.com/contest/1917/problem/F
#include <bits/stdc++.h>

#define debug(x) cout << #x << " = " << x << endl

using namespace std;

typedef long long Long;

const int D = 2000;
const Long INF = 1e18;
const char ENDL = '\n';
const string YES = "Yes";
const string NO = "No";


void Solve(void) {
  Long n, d;
  cin >> n >> d;
  vector<Long> l(n);
  for (int i = 0; i < n; i++) cin >> l[i];
  sort(l.begin(), l.end());
  reverse(l.begin(), l.end());

  // If the minimum diameter is greater than d, it is impossible
  if (l[0] + l[1] > d) {
    cout << NO << ENDL;
    return;
  }

  // dp[x][y]: Is it possible to get two disjoint subsets
  // with sums equal to x and y, respectively?
  vector<bitset<D + 1>> dp(d + 1);
  
  // Base case: Two empty subsets
  dp[0].set(0, true);

  // Update reachable states when inserting l_i into one of the two subsets
  for (int i = 1; i < n; i++) {
    for (int x = d; x >= 0; x--) {
      // Insert l_i into the first subset
      if (x + l[i] <= d) {
        dp[x + l[i]] |= dp[x];
      }
      // Insert l_i into the second subset
      dp[x] |= (dp[x] << l[i]);
    }
  }

  // If the greatest length could be part of a diameter,
  // then that diameter is a solution
  if (dp[d - l[0]][0]) {
    cout << YES << ENDL;
    return;
  }

  // Check each partition of size two of the diameter 
  for (int x = l[0]; x < d; x++) {
    if (dp[x][d - x] && (x + l[0] <= d)) {
      cout << YES << ENDL;
      return;
    }
  }

  cout << NO << ENDL;
}

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int t = 1;
  cin >> t;
  while (t--) Solve();
  return 0;
}

