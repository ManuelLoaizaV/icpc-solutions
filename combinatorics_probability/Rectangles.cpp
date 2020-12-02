#include <iostream>
#define FAST_IO ios::sync_with_stdio(0);cin.tie(nullptr)
using namespace std;

typedef long long Long;

const int N = 55;
Long nck[N][N];
bool a[N][N], is_done[N][N];

Long nCk(int n, int k) {
  if (k == 0 || n == k) return 1LL;
  if (is_done[n][k]) return nck[n][k];
  nck[n][k] = nCk(n - 1, k - 1) + nCk(n - 1, k);
  is_done[n][k] = true;
  return nck[n][k];
}

int main(void) {
  FAST_IO;
  int n, m;
  cin >> n >> m;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      cin >> a[i][j];
    }
  }
  Long ans = n * m;
  for (int i = 0; i < n; i++) {
    int cnt = 0;
    for (int j = 0; j < m; j++) if (a[i][j]) cnt++;
    for (int k = 2; k <= cnt; k++) ans += nCk(cnt, k);
    cnt = m - cnt;
    for (int k = 2; k <= cnt; k++) ans += nCk(cnt, k);
  }
  for (int j = 0; j < m; j++) {
    int cnt = 0;
    for (int i = 0; i < n; i++) if (a[i][j]) cnt++;
    for (int k = 2; k <= cnt; k++) ans += nCk(cnt, k);
    cnt = n - cnt;
    for (int k = 2; k <= cnt; k++) ans += nCk(cnt, k);
  }
  cout << ans << '\n';
  return 0;
}
