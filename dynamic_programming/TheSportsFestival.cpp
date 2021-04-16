//https://codeforces.com/contest/1509/problem/C
#include <bits/stdc++.h>
using namespace std;

typedef long long Long;

const int N = 2e3;

Long dp[N][N];
bool done[N][N];
vector<Long> a;

Long DP(int l, int r) {
  if (l == r) return 0;
  if (done[l][r]) return dp[l][r];
  Long d = a[r] - a[l];
  dp[l][r] = d + min(DP(l + 1, r), DP(l, r - 1));
  done[l][r] = true;
  return dp[l][r];
}

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n;
  a = vector<Long>(n);
  for (int i = 0; i < n; i++) cin >> a[i];
  sort(a.begin(), a.end());
  cout << DP(0, n - 1) << '\n';
  return 0;
}
