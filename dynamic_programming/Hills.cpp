//https://codeforces.com/problemset/problem/1012/C
#include <iostream>
#include <vector>
using namespace std;

typedef long long Long;

const int N = 5000;
const Long INF = 1e18;

vector<Long> a, decr_a;

bool is_done[N][(N + 1) / 2][2];
Long dp[N][(N + 1) / 2][2];
int n;

// DP(i, j, k) minimo costo de construir j casas en las viviendas
// [i .. n - 1] sabiendo que el anterior (k? si : no) ha sido decrementado.
Long DP(int pos, int rem, bool decr) {
  if (rem == 0) return 0;
  if (pos >= n) return INF;
  if (is_done[pos][rem][decr]) return dp[pos][rem][decr];
  dp[pos][rem][decr] = DP(pos + 1, rem, false);
  int cur = pos + 1;
  if (decr) {
    Long left = (decr_a[cur - 1] < a[cur]) ? 0 : (decr_a[cur - 1] - a[cur] + 1);
    Long right = (a[cur + 1] < a[cur]) ? 0 : (a[cur + 1] - a[cur] + 1);
    dp[pos][rem][decr] = min(dp[pos][rem][decr], left + right + DP(pos + 2, rem - 1, right != 0));
  } else {
    Long left = (a[cur - 1] < a[cur]) ? 0 : (a[cur - 1] - a[cur] + 1);
    Long right = (a[cur + 1] < a[cur]) ? 0 : (a[cur + 1] - a[cur] + 1);
    dp[pos][rem][decr] = min(dp[pos][rem][decr], left + right + DP(pos + 2, rem - 1, right != 0));
  }
  is_done[pos][rem][decr] = true;
  return dp[pos][rem][decr];
}

int main(void) {
  ios::sync_with_stdio(0);
  cin.tie(nullptr);
  cin >> n;
  a.push_back(-INF);
  decr_a.push_back(-INF);
  for (int i = 0; i < n; i++) {
    Long x;
    cin >> x;
    a.push_back(x);
    if (a.end()[-1] < a.end()[-2]) {
      decr_a.push_back(x);
    } else {
      decr_a.push_back(a.end()[-2] - 1);
    }
  }
  a.push_back(-INF);
  decr_a.push_back(-INF);
  int mx = (n + 1) / 2;
  for (int k = 1; k <= mx; k++) {
    cout << DP(0, k, false) << " ";
  }
  cout << '\n';
  return 0;
}
