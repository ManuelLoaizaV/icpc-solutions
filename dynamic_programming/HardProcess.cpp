#include <iostream>
#define FAST_IO ios::sync_with_stdio(0);cin.tie(nullptr)
using namespace std;

const int N = 3e5 + 5;

int n, k;
bool a[N];
int dp[N];

bool IsValid(int len) {
  for (int i = 0; i < n - len + 1; i++) {
    int zeroes = dp[i + len - 1] - ((i == 0) ? 0 : dp[i - 1]);
    if (zeroes <= k) return true;
  }
  return false;
}

int Search(void) {
  int l = 1;
  int r = n;
  if (IsValid(r)) return r;
  if (!IsValid(l)) return 0;
  while (r - l > 1) {
    int m = (l + r) / 2;
    if (IsValid(m)) {
      l = m;
    } else {
      r = m;
    }
  }
  return l;
}

int main(void) {
  FAST_IO;
  cin >> n >> k;
  for (int i = 0; i < n; i++) cin >> a[i];
  dp[0] = !a[0];
  for (int i = 1; i < n; i++) {
    dp[i] = dp[i - 1];
    if (!a[i]) dp[i]++;
  }
  int ans = Search();
  cout << ans << '\n';
  if (ans > 0) {
    for (int i = 0; i < n - ans + 1; i++) {
      int zeroes = dp[i + ans - 1] - ((i == 0) ? 0 : dp[i - 1]);
      if (zeroes <= k) {
        for (int j = 0; j < ans; j++) a[i + j] = true;
        break;
      }
    }
  }
  for (int i = 0; i < n; i++) {
    if (i > 0) cout << " ";
    cout << a[i];
  }
  cout << '\n';
  return 0;
}
