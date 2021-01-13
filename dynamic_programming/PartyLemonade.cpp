//https://codeforces.com/problemset/problem/913/C
#include <iostream>
#define FAST_IO ios::sync_with_stdio(0);cin.tie(nullptr)
using namespace std;

typedef unsigned long long Long;

const int N = 31;

bool has_bit[N];
Long cost[N], dp[N][2];
bool is_done[N][2];

Long DP(int pos, bool has_started) {
  if (pos < 0) return 0;
  if (is_done[pos][has_started]) return dp[pos][has_started];
  if (has_started) {
    if (has_bit[pos]) {
      dp[pos][true] = cost[pos] + DP(pos - 1, true);
    } else {
      dp[pos][true] = min(cost[pos], DP(pos - 1, true));
    }
  } else {
    if (has_bit[pos]) {
      dp[pos][false] = cost[pos] + DP(pos - 1, true);
    } else {
      dp[pos][false] = min(cost[pos], DP(pos - 1, false));
    }
  }
  is_done[pos][has_started] = true;
  return dp[pos][has_started];
}

int main(void) {
  FAST_IO;
  Long n, L;
  cin >> n >> L;
  for (int i = 0; i < n; i++) cin >> cost[i];
  for (int i = 0; i < N; i++) {
    if (i < n) {
      if (i > 0) cost[i] = min(2 * cost[i - 1], cost[i]);
    } else {
      cost[i] = 2 * cost[i - 1];
    }
  }
  for (int i = 0; i < N; i++) {
    has_bit[i] = L & 1;
    L >>= 1;
  }
  cout << DP(30, false) << '\n';
  return 0;
}
