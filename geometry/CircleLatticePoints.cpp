//https://atcoder.jp/contests/abc191/tasks/abc191_d
#include <bits/stdc++.h>
#define FAST_IO ios::sync_with_stdio(0);cin.tie(NULL)
#define debug(x) cout << #x << " = " << x << '\n'
using namespace std;

typedef long long Long;
typedef long double Double;
typedef unsigned long long ULong;
typedef pair<Long, Long> Pair;

const Long S = 1e4;

Long Ceil(Long n) {
  Long remainder = abs(n) % S;
  if (remainder == 0) return n;
  if (n >= 0) return n - remainder + S;
  return n + remainder;
}

Long Floor(Long n) {
  Long remainder = abs(n) % S;
  if (remainder == 0) return n;
  if (n >= 0) return n - remainder;
  return n + remainder - S;
}

Long Square(Long x) { return x * x; }

bool IsInside(Long dx, Long dy, Long r) {
  return Square(dx) + Square(dy) <= Square(r);
}

void Solve(void) {
  Double x_0, y_0, r;
  cin >> x_0 >> y_0 >> r;
  Long int_x_0 = llround(x_0 * S);
  Long int_y_0 = llround(y_0 * S);
  Long int_r = llround(r * S);
  Long answer = 0LL;
  Long lower_y = Ceil(int_y_0 - int_r);
  Long upper_y = Floor(int_y_0 + int_r);
  for (Long y = lower_y; y <= upper_y; y += S) {
    Long left_l = int_x_0 - int_r - 1;
    Long left_r = int_x_0;
    while (left_r - left_l > 1) {
      Long left_mid = (left_l + left_r) / 2;
      if (IsInside(left_mid - int_x_0, y - int_y_0, int_r)) {
        left_r = left_mid;
      } else {
        left_l = left_mid;
      }
    }
    Long right_l = int_x_0;
    Long right_r = int_x_0 + int_r + 1;
    while (right_r - right_l > 1) {
      Long right_mid = (right_l + right_r) / 2;
      if (IsInside(right_mid - int_x_0, y - int_y_0, int_r)) {
        right_l = right_mid;
      } else {
        right_r = right_mid;
      }
    }
    Long left = Ceil(left_r);
    Long right = Floor(right_l);
    if (left <= right) answer += (right - left) / S + 1LL;
  }
  cout << answer << '\n';
}
int main(void) {
  FAST_IO;
  int t = 1;
  //cin >> t;
  while (t--) Solve();
  return 0;
}
