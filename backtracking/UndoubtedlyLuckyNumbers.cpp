// https://codeforces.com/problemset/problem/244/B
#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << '\n'
using namespace std;

typedef long long Long;

Long GetSize(Long n) {
  if (n < 10) return 1LL;
  return 1LL + GetSize(n / 10);
}

Long num;

Long Backtrack(Long i, Long j, bool i_used, bool j_used, const Long& n) {
  if (num > n) return 0LL;
  Long cnt = 0LL;
  if (i_used && j_used && num <= n) cnt++;
  for (Long k = 0; k < 2; k++) {
    num = 10LL * num + (k ? i : j);
    cnt += Backtrack(i, j, i_used || k, j_used || !k, n);
    num /= 10LL;
  }
  return cnt;
}

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  Long n;
  cin >> n;
  Long sz = GetSize(n);
  Long result = 0LL;

  // Case one digit
  for (Long d = 1; d <= 9; d++) {
    num = d;
    while (num <= n) {
      result++;
      num = 10LL * num + d;
    }
  }

  // Case two digits
  for (Long i = 0; i <= 9; i++) {
    for (Long j = i; j <= 9; j++) {
      if (i == j) continue;
      num = 0;
      if (i == 0) num = j;
      result += Backtrack(i, j, false, i == 0, n);
    }
  }
  cout << result << '\n';
  return 0;
}
