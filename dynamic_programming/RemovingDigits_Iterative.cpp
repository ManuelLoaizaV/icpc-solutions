// https://cses.fi/problemset/task/1637/
#include <bits/stdc++.h>
using namespace std;

vector<int> GetDigits(int n) {
  vector<int> digits;
  while (n > 0) {
    int d = n % 10;
    if (d > 0) {
      digits.push_back(d);
    }
    n /= 10;
  }
  return digits;
}

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n;
  vector<int> dp(n + 1, n + 1);
  dp[0] = 0;
  for (int i = 1; i <= n; i++) {
    vector<int> digits = GetDigits(i);
    for (int digit : digits) {
      dp[i] = min(dp[i], 1 + dp[i - digit]);
    }
  }
  cout << dp[n] << endl;
  return 0;
}