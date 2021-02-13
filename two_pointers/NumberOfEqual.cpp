#include <bits/stdc++.h>
using namespace std;

int main(void) {
  int n, m;
  scanf("%d %d", &n, &m);
  vector<int> a(n), b(m);
  for (int i = 0; i < n; i++) scanf("%d", &a[i]);
  for (int i = 0; i < m; i++) scanf("%d", &b[i]);
  long long ans = 0;
  int l, r;
  l = r = 0;
  for (int j = 0; j < m; j++) {
    while (r < n && a[r] <= b[j]) {
      if (a[l] != a[r]) l = r;
      r++;
    }
    if (a[l] == b[j]) ans += (long long) (r - l);
  }
  printf("%lld\n", ans);
  return 0;
}
