// https://codeforces.com/contest/1658/problem/A
//#pragma GCC optimize ("Ofast,unroll-loops")
//#pragma GCC target ("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#include <bits/stdc++.h>
#include <unistd.h>
#define debug(x) cout << #x << " = " << x << endl
using namespace std;

typedef long long Long;
typedef long double Double;
typedef unsigned long long ULong;
typedef pair<Long, Long> Pair;

const int N = 1e6;
const Long INF = 1e18;
const Double EPS = 1e-9;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
Long random(Long a, Long b) { return uniform_int_distribution<Long>(a, b)(rng); }

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int t;
  cin >> t;
  while (t--) {
    Long n;
    cin >> n;
    string s;
    cin >> s;
    int add = 0;
    vector<int> positions;
    for (int i = 0; i < n; i++) {
      if (s[i] == '0') {
        positions.push_back(i);
      }
    }
    int n_positions = (int)positions.size();
    for (int i = 0; i < n_positions - 1; i++) {
      int delta = positions[i + 1] - positions[i];
      if (delta <= 2) {
        add += (2 - delta + 1);
      }
    }
    cout << add << '\n';
  }
  return 0;
}
