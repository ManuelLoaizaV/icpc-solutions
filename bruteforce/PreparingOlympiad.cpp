//https://codeforces.com/problemset/problem/550/B
#include <bits/stdc++.h>
#include <unistd.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;

typedef long long Long;
typedef long double Double;
typedef unsigned long long ULong;
typedef pair<Long, Long> Pair;

const Long INF = (Long) 1e9;

Long GetBit(Long mask, Long bit) {
  return (mask >> bit) & 1LL;
}

void TurnOn(Long& mask, Long bit) {
  mask = mask | (1LL << bit);
}

void TurnOff(Long& mask, Long bit) {
  mask = mask & (~(1 << bit));
}

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int n, l, r, x;
  cin >> n >> l >> r >> x;
  vector<Long> a(n);
  for (int i = 0; i < n; i++) cin >> a[i];
  int sup = 1 << n;
  Long ans = 0;
  for (int i = 0; i < sup; i++) {
    Long mn = INF;
    Long mx = -INF;
    Long cnt = 0;
    Long sum = 0;
    for (int j = 0; j < n; j++) {
      if (GetBit((Long) i, (Long) j) == 1) {
        mn = min(mn, a[j]);
        mx = max(mx, a[j]);
        cnt++;
        sum += a[j];
      }
    }
    if (cnt > 1 && l <= sum && sum <= r && mx - mn >= x) ans++;
  }
  cout << ans << '\n';
  return 0;
}
