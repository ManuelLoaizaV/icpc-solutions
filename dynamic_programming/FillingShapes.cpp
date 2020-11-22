#include <bits/stdc++.h>
#define FAST_IO ios::sync_with_stdio(0);cin.tie(NULL)
#define debug(x) cout << #x << " = " << x << endl
using namespace std;

const int N = 65;

typedef long long Long;

Long dp[N];
bool is_done[N];

Long DP(Long n) {
  if (n == 0) return 1LL;
  if (n <= 1) return 0LL;
  if (is_done[n]) return dp[n];
  dp[n] = 2LL * DP(n - 2);
  is_done[n] = true;
  return dp[n];
}

int main(void) {
  FAST_IO;
  Long n;
  cin >> n;
  cout << DP(n) << '\n';
  return 0;
}
