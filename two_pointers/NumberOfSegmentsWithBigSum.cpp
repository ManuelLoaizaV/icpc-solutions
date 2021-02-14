#include <bits/stdc++.h>
using namespace std;

int main(void) {
  int n;
  long long s;
  scanf("%d %lld", &n, &s);
  vector<long long> a(n);
  for (int i = 0; i < n; i++) scanf("%lld", &a[i]);
  long long ans = 0;
  long long sum = 0;
  int l = 0;
  for (int r = 0; r < n; r++) {
    sum += a[r];
    while (sum - a[l] >= s) sum -= a[l++];
    if (sum >= s) ans += (long long) (l + 1);
  }
  printf("%lld\n", ans);
  return 0;
}
