// https://codeforces.com/contest/1916/problem/A
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

void Solve(void) {
  Long n, k;
  cin >> n >> k;
  vector<Long> v(n);
  Long mul = 1LL;
  for (int i = 0; i < n; i++) {
    cin >> v[i];
    mul *= v[i];
  }
  Long target = 2023LL;
  if (target % mul != 0) {
    cout << NO << ENDL;
    return;
  }
  cout << YES << ENDL;
  for (int i = 0; i < k; i++) {
    if (i > 0) cout << " ";
    if (i == 0) {
      cout << target / mul;
    } else {
      cout << 1;
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
