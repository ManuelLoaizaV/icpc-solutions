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

const int N = 1000000;
int dp[N + 1];
bool done[N + 1];

int DP(int n) {
  if (n == 0) return 0;
  if (done[n]) return dp[n];
  dp[n] = N + 1;
  vector<int> digits = GetDigits(n);
  for (int digit : digits) {
    dp[n] = min(dp[n], 1 + DP(n - digit));
  }
  done[n] = true;
  return dp[n];
}

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n;
  cout << DP(n) << endl;
  return 0;
}