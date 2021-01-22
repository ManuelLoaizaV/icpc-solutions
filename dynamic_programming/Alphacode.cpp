//https://www.spoj.com/problems/ACODE/
#include <iostream>
#include <string>
using namespace std;

typedef long long Long;

const int N = 5e3;
const int ALPHABET = 26;

string s;
int a[N];
int n;
bool is_done[N];
Long dp[N];

Long DP(int pos) {
  if (pos == n) return 1;
  if (is_done[pos]) return dp[pos];
  dp[pos] = 0;
  if (a[pos] > 0) {
    dp[pos] = DP(pos + 1);
    if (pos < n - 1) {
      int num = 10 * a[pos] + a[pos + 1];
      if (num <= ALPHABET) dp[pos] += DP(pos + 2);
    }
  }
  is_done[pos] = true;
  return dp[pos];
}

void Solve(void) {
  n = s.size();
  for (int i = 0; i < n; i++) a[i] = s[i] - '0';
  for (int i = 0; i < n; i++) is_done[i] = false;
  cout << DP(0) << '\n';
}

int main(void) {
  ios::sync_with_stdio(0);
  cin.tie(nullptr);
  while (true) {
    cin >> s;
    if (s.size() == 1 && s[0] == '0') break;
    Solve();
  }
  return 0;
}
