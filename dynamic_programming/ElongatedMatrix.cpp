#include <iostream>
#include <climits>
#define FAST_IO ios::sync_with_stdio(0);cin.tie(nullptr)
using namespace std;

const int N = 16;
const int LG = 1 << N;
const int M = 1e4;
const int INF = INT_MAX;

int a[N][M];
int cost[N][N], last_first[N][N];
int n, m, lim;

int ObtenerBit(int mascara, int bit) {
  return (mascara >> bit) & 1;
}

void PrenderBit(int& mascara, int bit) {
  mascara = (mascara | (1 << bit));
}

bool is_done[LG][N][N];
int dp[LG][N][N];

int DP(int mask, int first, int last) {
  if (mask == lim - 1) {
    return last_first[last][first];
  }
  if (is_done[mask][first][last]) return dp[mask][first][last];
  dp[mask][first][last] = 0;
  for (int i = 0; i < n; i++) {
    if (!ObtenerBit(mask, i)) {
      int new_mask = mask;
      PrenderBit(new_mask, i);
      if (mask == 0) {
        dp[mask][first][last] = max(dp[mask][first][last], DP(new_mask, i, i));
      } else {
        dp[mask][first][last] = max(dp[mask][first][last], min(cost[last][i], DP(new_mask, first, i)));
      }
    }
  }
  is_done[mask][first][last] = true;
  return dp[mask][first][last];
}

int main(void) {
  FAST_IO;
  cin >> n >> m;
  lim = 1 << n;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      cin >> a[i][j];
    }
  }
  // O(n^2 * m)
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      int cur = INF;
      for (int k = 0; k < m; k++) {
        cur = min(cur, abs(a[i][k] - a[j][k]));
      }
      cost[i][j] = cur;
    }
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      int cur = INF;
      for (int k = 0; k < m - 1; k++) {
        cur = min(cur, abs(a[i][k] - a[j][k + 1]));
      }
      last_first[i][j] = cur;
    }
  }
  cout << DP(0, 0, 0) << '\n';
  return 0;
}
