#include <bits/stdc++.h>
using namespace std;

int main(void) {
  int n;
  long long s;
  scanf("%d %lld", &n, &s);
  vector<long long> a(n);
  for (int i = 0; i < n; i++) scanf("%lld", &a[i]);
  // invariant: sum = \sum_{i = l} ^ r a_i
  long long sum = 0;
  int l = 0;
  int ans = 0;
  for (int r = 0; r < n; r++) {
    sum += a[r];
    while (sum > s) sum -= a[l++];
    ans = max(ans, r - l + 1);
  }
  printf("%d\n", ans);
  return 0;
}
