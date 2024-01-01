// https://codeforces.com/contest/1916/problem/C
#include <bits/stdc++.h>

#define debug(x) cout << #x << " = " << x << endl

using namespace std;

typedef long long Long;
typedef long double Double;

const Long INF = 1e18;
const Long MOD = 998244353LL;
const char ENDL = '\n';
const string YES = "YES";
const string NO = "NO";

namespace Div {
  bool SameSign(Long a, Long b) {
    return a > 0 && b > 0 || a < 0 && b < 0;
  }
  Long Floor(Long a, Long b) {
    assert(b != 0);
    if (a == 0) return 0;
    if (a % b == 0) return a / b;
    if (SameSign(a, b)) return abs(a) / abs(b);
    return -((abs(a) - 1LL) / abs(b) + 1LL);
  }
  Long Ceil(Long a, Long b) {
    assert(b != 0);
    if (a == 0) return 0;
    if (a % b == 0) return a / b;
    if (!SameSign(a, b)) return (-1LL) * (abs(a) / abs(b));
    return (abs(a) - 1LL) / abs(b) + 1LL;
  }
}

void Solve(void) {
  Long n;
  cin >> n;
  Long sum = 0LL;

  vector<Long> cnt(2, 0LL);
  for (int i = 0; i < n; i++) {
    Long x;
    cin >> x;
    cnt[x & 1]++;
    sum += x;
    if (i > 0) cout << " ";
    if (i == 0) {
      cout << sum;
    } else {
      Long take = 0;
      if (cnt[1] > 0) {
        take = Div::Ceil(cnt[1], 3LL);
        if (cnt[1] % 3LL == 2LL) {
          take--;
        }
      }
      cout << sum - take;
    }
  }
  cout << ENDL;
}

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int t = 1;
  cin >> t;
  while (t--) Solve();
  return 0;
}
