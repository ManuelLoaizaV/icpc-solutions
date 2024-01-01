// https://codeforces.com/contest/1916/problem/D
#include <bits/stdc++.h>

#define debug(x) cout << #x << " = " << x << endl

using namespace std;

typedef long long Long;
typedef long double Double;

const Long N = 99;
const Long INF = 1e18;
const Long MOD = 998244353LL;
const char ENDL = '\n';
const string YES = "YES";
const string NO = "NO";

vector<vector<string>> squares(N + 1);

void Precompute(void) {
  squares[1] = {"1"};
  squares[3] = {"169", "196", "961"};
  string zeroes = "";
  for (int i = 5; i <= 99; i += 2) {
    zeroes += "0";
    for (int j = 0; j < i - 2; j++) {
      squares[i].push_back(squares[i - 2][j] + "00");
    }
    squares[i].push_back("1" + zeroes + "6" + zeroes + "9");
    squares[i].push_back("9" + zeroes + "6" + zeroes + "1");
  }
}

void Solve(void) {
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) {
    cout << squares[n][i] << ENDL;
  }
}

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  Precompute();
  int t = 1;
  cin >> t;
  while (t--) Solve();
  return 0;
}
