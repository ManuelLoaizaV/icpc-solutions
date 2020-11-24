#include <algorithm>
#include <iostream>
#define FAST_IO ios::sync_with_stdio(0);cin.tie(nullptr)
using namespace std;

typedef long long Long;

const int N = 1e3;
const int K = 2e3;
const Long INF = 3e13;

int n, k, p;
Long a[N];
Long b[K];
Long dp[N][K];
bool is_done[N][K];

Long DP(int pos, int key) {
  if (pos == n) return 0;
  if (key == k) return INF;
  if (is_done[pos][key]) return dp[pos][key];
  Long dist = abs(a[pos] - b[key]) + abs(b[key] - p);
  Long mx = max(dist, DP(pos + 1, key + 1));
  dp[pos][key] = min(mx, DP(pos, key + 1));
  is_done[pos][key] = true;
  return dp[pos][key];
}

int main(void) {
  FAST_IO;
  cin >> n >> k >> p;
  for (int i = 0; i < n; i++) cin >> a[i];
  for (int i = 0; i < k; i++) cin >> b[i];
  sort(a, a + n);
  sort(b, b + k);
  cout << DP(0, 0) << '\n';
  return 0;
}
