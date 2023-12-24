// https://codeforces.com/contest/1909/problem/A
#include <bits/stdc++.h>

#define debug(x) cout << #x << " = " << x << endl

using namespace std;

typedef long long Long;

const int N = 1e6;
const Long INF = 1e18;
const char ENDL = '\n';
const string YES = "YES";
const string NO = "NO";

void Solve(void) {
  int n;
  cin >> n;
  set<char> s;
  while (n--) {
    int x, y;
    cin >> x >> y;
    if (x > 0) s.insert('R');
    if (x < 0) s.insert('L');
    if (y > 0) s.insert('U');
    if (y < 0) s.insert('D');
  }
  if ((int)s.size() == 4) {
    cout << NO << ENDL;
  } else {
    cout << YES << ENDL;
  }
}

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int t = 1;
  cin >> t;
  while (t--) Solve();
  return 0;
}