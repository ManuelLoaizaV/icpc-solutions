// https://codeforces.com/contest/1658/problem/D2
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

const int B = 17;
const int N = 1e6;
const Long INF = 1e18;
const Double EPS = 1e-9;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
Long random(Long a, Long b) { return uniform_int_distribution<Long>(a, b)(rng); }

vector<int> Half(const vector<int>& v) {
  int n = (int) v.size();
  vector<int> half;
  for (int i = 0; i < n; i += 2) {
    half.push_back(v[i] >> 1);
  }
  return half;
}

bool Check(int l, int r, int x, const vector<int>& a) {
  vector<int> b;
  for (int i = l; i <= r; i++) b.push_back(i ^ x);
  sort(b.begin(), b.end());
  return a == b;
}

int Destroy(int l, int r, vector<int> a) {
  int n = (int) a.size();
  sort(a.begin(), a.end());

  // Odd length implies known x
  if (n & 1) {
    int total_xor, range_xor;
    total_xor = range_xor = 0;
    for (int i = 0; i < n; i++) {
      total_xor ^= a[i];
      range_xor ^= (l + i);
    }
    int x = total_xor ^ range_xor;
    return x;
  }

  // Even length has two cases
  // Case 1: If all numbers appear in pairs
  // we can't conclude anything,
  // so we remove the last bit
  bool perfect = true;
  for (int i = 0; i < n; i += 2) {
    int pair_xor = a[i] ^ a[i + 1];
    if (pair_xor != 1) {
      perfect = false;
      break;
    }
  }
  if (perfect) {
    vector<int> half = Half(a);
    int x = Destroy(l >> 1, r >> 1, half) << 1;
    return x;
  }

  // Case 2: We have pairs except two numbers
  // that don't match, so we bruteforce them
  unordered_set<int> aux;
  for (int e : a) {
    aux.insert(e);
  }
  vector<int> candidates;
  for (int i = 0; i < n; i++) {
    if (aux.count(a[i] ^ 1) > 0) continue;
    candidates.push_back(a[i]);
  }
  for (int candidate : candidates) {
    int x = candidate ^ l;
    if (Check(l, r, x, a)) {
      return x;
    }
  }
  return -1;
}

void Solve(void) {
  int l, r;
  cin >> l >> r;
  int n = r - l + 1;
  vector<int> a(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  int x = Destroy(l, r, a);
  cout << x << '\n';
}

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int t = 1;
  cin >> t;
  while (t--) Solve();
  return 0;
}
