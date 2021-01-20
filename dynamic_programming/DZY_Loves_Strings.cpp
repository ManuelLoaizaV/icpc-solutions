#include <iostream>
#include <vector>
using namespace std;

typedef long long Long;

const int ALPH = 26;
const int N = 1e3 + 2;

string s;
Long w[ALPH];
Long k, mx;


bool is_done[N][N];
Long dp[N][N];

Long DP(Long pos, Long used) {
  if (pos == s.size()) {
    Long rem = k - used;
    return mx * ((s.size() + 1 + used) * rem + rem * (rem - 1) / 2);
  }
  if (is_done[pos][used]) return dp[pos][used];
  dp[pos][used] = (pos + 1 + used) * w[s[pos] - 'a'] + DP(pos + 1, used);
  dp[pos][used] = max(dp[pos][used], (pos + 1 + used) * mx + DP(pos + 1, used + 1));
  is_done[pos][used] = true;
  return dp[pos][used];
}

int main(void) {
  ios::sync_with_stdio(0);
  cin.tie(nullptr);
  cin >> s >> k;
  for (int i = 0; i < ALPH; i++) cin >> w[i];
  mx = w[0];
  for (int i = 1; i < ALPH; i++) mx = max(mx, w[i]);
  cout << DP(0, 0) << '\n';
  return 0;
}
