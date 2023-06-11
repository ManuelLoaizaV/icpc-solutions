//https://codeforces.com/problemset/problem/371/C
#include <bits/stdc++.h>
#include <unistd.h>
#define FAST_IO ios::sync_with_stdio(0);cin.tie(NULL)
#define all(v) (v).begin(),(v).end()
using namespace std;

typedef long long Long;
typedef long double Double;
typedef unsigned long long ULong;
typedef pair<Long, Long> Pair;

const int N = 1e6;
const Long INF = 1e12 + 105;
const Double EPS = 1e-9;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
Long random(Long a, Long b) { return uniform_int_distribution<Long> (a, b) (rng); }

Long n[3];
Long cur[3];
Long price[3];
Long money;

bool Check(Long target) {
  Long sum = 0;
  for (int i = 0; i < 3; i++) {
    Long needed = n[i] * target;
    if (cur[i] < needed) sum += price[i] * (needed - cur[i]);
  }
  return sum <= money;
}

void Solve(void) {
  string s;
  cin >> s;
  for (char c : s) {
    if (c == 'B') {
      n[0]++;
    } else if (c == 'S') {
      n[1]++;
    } else {
      n[2]++;
    }
  }
  for (int i = 0; i < 3; i++) cin >> cur[i];
  for (int i = 0; i < 3; i++) cin >> price[i];
  cin >> money;
  Long l = 0;
  Long r = INF;
  while (r - l > 1) {
    Long m = (l + r) / 2;
    if (Check(m)) {
      l = m;
    } else {
      r = m;
    }
  }
  cout << l << '\n';
}

int main(void) {
  FAST_IO;
  int t = 1;
  //cin >> t;
  while (t--) Solve();
  return 0;
}
