#include <bits/stdc++.h>
using namespace std;

int main(void) {
  int n;
  long long s;
  scanf("%d %lld", &n, &s);
  vector<long long> a(n);
  for (int i = 0; i < n; i++) scanf("%lld", &a[i]);
  int ans = n + 1;
  int l = 0;
  long long sum = 0;
  for (int r = 0; r < n; r++) {
    sum += a[r];
    while (sum - a[l] >= s) sum -= a[l++];
    if (sum >= s) ans = min(ans, r - l + 1);
  }
  if (ans == n + 1) {
    printf("-1\n");
  } else {
    printf("%d\n", ans);
  }
  return 0;
}
