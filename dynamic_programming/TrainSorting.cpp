#include <bits/stdc++.h>
#define FAST_IO ios::sync_with_stdio(0);cin.tie(nullptr)
using namespace std;

int main(void) {
  FAST_IO;
  int n;
  cin >> n;
  if (n == 0) {
    cout << 0 << '\n';
    return 0;
  }
  vector<int> a(n);
  for (int i = 0; i < n; i++) cin >> a[i];
  reverse(a.begin(), a.end());
  vector<int> lis(n, 1);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < i; j++) {
      if (a[j] < a[i]) lis[i] = max(lis[i], lis[j] + 1);
    }
  }
  vector<int> lds(n, 1);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < i; j++) {
      if (a[j] > a[i]) lds[i] = max(lds[i], lds[j] + 1);
    }
  }
  int ans = 0;
  for (int i = 0; i < n; i++) {
    int tmp = lds[i] + lis[i] - 1;
    for (int j = 0; j < n; j++) {
      if (j != i && a[j] < a[i]) tmp = max(tmp, lds[i] + lis[j]);
    }
    ans = max(ans, tmp);
  }
  cout << ans << '\n';
  return 0;
}
