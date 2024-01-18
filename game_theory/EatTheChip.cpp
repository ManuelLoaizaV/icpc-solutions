// https://codeforces.com/contest/1921/problem/E
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

const int N = 1e6;
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
const string DRAW = "Draw";

void Solve(void) {
  Long height, width;
  Pair alice, bob;
  cin >> height >> width;
  cin >> alice.first >> alice.second;
  cin >> bob.first >> bob.second;

  Long height_delta = bob.first - alice.first;
  if (height_delta <= 0) {
    cout << DRAW << ENDL;
    return;
  }
  
  Long width_delta = abs(bob.second - alice.second);
  if (width_delta > height_delta) {
    cout << DRAW << ENDL;
    return;
  }
  Long alice_moves = (height_delta + 1LL) / 2LL;
  Long bob_moves = height_delta / 2LL;
  Pair alice_range = {max(1LL, alice.second - alice_moves), min(width, alice.second + alice_moves)};
  Pair bob_range = {max(1LL, bob.second - bob_moves), min(width, bob.second + bob_moves)};

  if (height_delta & 1) {
    if (
      bob_range.first < alice_range.first ||
      bob_range.second > alice_range.second
    ) {
      cout << DRAW << ENDL;
    } else {
      cout << ALICE << ENDL;
    }
  } else {
    if (
      alice_range.first < bob_range.first ||
      alice_range.second > bob_range.second
    ) {
      cout << DRAW << ENDL;
    } else {
      cout << BOB << ENDL;
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