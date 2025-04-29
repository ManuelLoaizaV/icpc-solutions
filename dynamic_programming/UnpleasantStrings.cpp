// https://codeforces.com/contest/2104/problem/E
#include <bits/stdc++.h>

#ifndef ONLINE_JUDGE
#define debug(x) cerr << "[" << #x << "]: " << x << endl
#else
#define debug(x) 69
#endif

using namespace std;

typedef long long Long;
typedef long double Double;
typedef pair<Long, Long> Pair;

const int N = 50;
const Long MOD = 998244353LL;
const Long INF = 1e18;
const Double PI = acos(-1);
const Double EPS = 1e-9;

const char A = 'a';
const char ZERO = '0';
const char ENDL = '\n';

const string YES = "YES";
const string NO = "NO";

const string ALICE = "Alice";
const string BOB = "Bob";

void Solve(void) {
  int n;
  cin >> n;
  string cards;
  cin >> cards;
  vector<bool> alice(n + 1, false), bob(n + 1, false);
  for (int i = 1; i <= n; i++) {
    if (cards[i - 1] == 'A') {
      alice[i] = true;
    } else {
      bob[i] = true;
    }
  }

  string A = ALICE;
  string B = BOB;

  if (alice[1] && alice[n]) {
    cout << A << ENDL;
    return;
  }

  if (bob[1] && bob[n]) {
    cout << B << ENDL;
    return;
  }

  if (n == 2) {
    if (alice[1]) {
      cout << A << ENDL;
    } else {
      cout << B << ENDL;
    }
    return;
  }

  int cnt_alice{0};
  int cnt_bob{0};
  for (int i = 1; i <= n; ++i) {
    if (alice[i]) ++cnt_alice;
    if (bob[i]) ++cnt_bob;
  }

  if (cnt_alice == 1) {
    cout << B << ENDL;
    return;
  }

  if (cnt_bob == 1) {
    cout << A << ENDL;
    return;
  }

  if (alice[1]) {
    // A: 1...
    // B: ...n
    cout << B << ENDL;
  } else {
    // A: ...n
    // B: 1...
    if (alice[n - 1]) {
      cout << A << ENDL;
    } else {
      cout << B << ENDL;
    }
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