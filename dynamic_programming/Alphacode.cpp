// https://www.spoj.com/problems/ACODE/en/
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
const char ONE = '1';
const char TWO = '2';
const char SIX = '6';
const char ENDL = '\n';

const string YES = "YES";
const string NO = "NO";

void Solve(const string& s) {
  int n = (int)s.size();
  // dp(i) = number of encodings of s[i..n)
  vector<Long> dp(n + 1, 0LL);
  // Base case: Empty string has 1 encoding
  dp[n] = 1LL;
  for (int i = n - 1; i >= 0; i--) {
    if (s[i] != ZERO) {
      dp[i] += dp[i + 1];
    }
    if (i < n - 1 && (s[i] == ONE || s[i] == TWO && s[i + 1] <= SIX)) {
      dp[i] += dp[i + 2];
    }
  }
  cout << dp[0] << ENDL;
}

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  while (true) {
    string s;
    cin >> s;
    if (s == "0") break;
    Solve(s);
  }
  return 0;
}
