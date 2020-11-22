#include <bits/stdc++.h>
#define FAST_IO ios::sync_with_stdio(0);cin.tie(NULL)
#define debug(x) cout << #x << " = " << x << endl
using namespace std;

const int ALPHABET= 26;

typedef long long Long;

bool is_valid[ALPHABET];
vector<Long> dp;
vector<bool> is_done;
string s;

Long DP(int pos) {
  if (pos == s.size()) return 0;
  if (is_done[pos]) return dp[pos];
  if (is_valid[s[pos] - 'a']) {
    dp[pos] = 1;
    dp[pos] += DP(pos + 1);
  } else {
    dp[pos] = 0;
  }
  is_done[pos] = true;
  return dp[pos];
}

int main(void) {
  FAST_IO;
  Long n, k;
  cin >> n >> k;
  cin >> s;
  while (k--) {
    char c;
    cin >> c;
    is_valid[c - 'a'] = true;
  }
  dp.resize(n, 0);
  is_done.resize(n, false);
  Long ans = 0LL;
  for (int i = 0; i < n; i++) ans += DP(i);
  cout << ans << '\n';
  return 0;
}
