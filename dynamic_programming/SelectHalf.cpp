//https://atcoder.jp/contests/abc162/tasks/abc162_f
#include <iostream>
#include <vector>
#define FAST_IO ios::sync_with_stdio(0);cin.tie(nullptr)
using namespace std;

typedef long long Long;

const int N = 2e5;
const int K = 3;
const Long INF = 3e14;

vector<Long> a;
Long n;

Long dp[N][K + 1];
bool is_done[N][K + 1];

Long DP(int pos, int rem) {
  if (pos >= n) {
    int used = K - rem;
    int real_pos = pos - used;
    int cnt = real_pos / 2;
    if (cnt == n / 2) return 0;
    return -INF;
  }
  if (is_done[pos][rem]) return dp[pos][rem];
  dp[pos][rem] = -INF;
  dp[pos][rem] = max(dp[pos][rem], a[pos] + DP(pos + 2, rem));
  if (rem > 0) dp[pos][rem] = max(dp[pos][rem], DP(pos + 1, rem - 1));
  is_done[pos][rem] = true;
  return dp[pos][rem];
}

int main(void) {
  FAST_IO;
  cin >> n;
  a.resize(n);
  for (int i = 0; i < n; i++) cin >> a[i];
  cout << DP(0, K) << '\n';
  return 0;
}
