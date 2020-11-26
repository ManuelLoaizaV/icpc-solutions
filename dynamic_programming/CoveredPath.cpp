#include <iostream>
#define FAST_IO ios::sync_with_stdio(0);cin.tie(nullptr)
using namespace std;

const int N = 100;
const int INF = 7e4;

int dp[12 * N][N];
bool is_done[12 * N][N];
int v1, v2, t, d;

int DP(int cur, int pos) {
  if (pos == t - 1) {
    if (cur == v2) return v2;
    return -INF;
  }
  if (is_done[cur][pos]) return dp[cur][pos];
  int rem = -INF;
  for (int delta = -d; delta <= d; delta++) {
    int next = max(0, cur + delta);
    rem = max(rem, DP(next, pos + 1));
  }
  if (rem < 0) {
    dp[cur][pos] = -INF;
  } else {
    dp[cur][pos] = cur + rem; 
  }
  is_done[cur][pos] = true;
  return dp[cur][pos];
}

int main(void) {
  FAST_IO;
  cin >> v1 >> v2 >> t >> d;
  cout << DP(v1, 0) << '\n';
  return 0;
}
