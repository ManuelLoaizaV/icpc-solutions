//https://codeforces.com/problemset/problem/1097/B
#include <bits/stdc++.h>
using namespace std;

typedef long long Long;

const Long MOD = 360;

Long GetBit(Long mask, Long bit) {
  return (mask >> bit) & 1LL;
}

void TurnOn(Long& mask, Long bit) {
  mask = mask | (1LL << bit);
}

void TurnOff(Long& mask, Long bit) {
  mask = mask & (~(1 << bit));
}

Long Add(Long a, Long b) {
  return (a + b) % MOD;
}

Long Mul(Long a, Long b) {
  return (a * b) % MOD;
}

Long Sub(Long a, Long b) {
  return (a - b + MOD) % MOD;
}

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n;
  vector<int> a(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  int sup = 1 << n;
  for (int i = 0; i < sup; i++) {
    Long sum = 0;
    for (int j = 0; j < n; j++) {
      if (GetBit((Long) i, (Long) j) == 1) {
        sum = Add(sum, a[j]);
      } else {
        sum = Sub(sum, a[j]);
      }
    }
    if (sum == 0) {
      cout << "YES" << '\n';
      return 0;
    }
  }
  cout << "NO" << '\n';
  return 0;
}
