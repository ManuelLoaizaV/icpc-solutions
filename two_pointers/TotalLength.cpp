#include <bits/stdc++.h>
using namespace std;

typedef long long Long;

void Add(Long x, Long& s) {
  s += x;
}

void Delete(Long x, Long& s) {
  s -= x;
}

bool IsGood(Long x, Long s) {
  return x <= s;
}

int main(void) {
  int n;
  Long s;
  scanf("%d %lld", &n, &s);
  vector<Long> a(n);
  for (int i = 0; i < n; i++) scanf("%lld", &a[i]);
  Long ans = 0;
  Long sum = 0;
  int l = 0;
  for (int r = 0; r < n; r++) {
    Add(a[r], sum);
    while (!IsGood(sum, s)) Delete(a[l++], sum);
    if (sum <= s) {
      Long len = r - l + 1;
      ans += len * (len + 1) / 2;
    }
  }
  printf("%lld\n", ans);
  return 0;
}
