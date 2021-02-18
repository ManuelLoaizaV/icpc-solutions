//#pragma GCC optimize ("Ofast,unroll-loops")
//#pragma GCC target ("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#include <bits/stdc++.h>
#include <unistd.h>
#define FAST_IO ios::sync_with_stdio(0);cin.tie(NULL)
#define debug(x) cout << #x << " = " << x << endl
#define all(v) (v).begin(),(v).end()
using namespace std;

typedef long long Long;
typedef long double Double;
typedef unsigned long long ULong;
typedef pair<Long, Long> Pair;

const int N = 1e6;
const Long INF = 1e18;
const Double EPS = 1e-9;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
Long random(Long a, Long b) { return uniform_int_distribution<Long> (a, b) (rng); }

int main(void) {
  FAST_IO;
  Long n;
  cin >> n;
  vector<Long> a(n);
  for (int i = 0; i < n; i++) cin >> a[i];
  sort(a.begin(), a.end());
  int l = 0;
  int r = n - 1;
  vector<Long> ans(n);
  for (int i = 0; i < n; i++) {
    if (i & 1) {
      ans[i] = a[r--];
    } else {
      ans[i] = a[l++];
    }
  }
  for (int i = 1; i < n; i++) {
    if (i & 1) {
      if (ans[i] < ans[i - 1]) {
        cout << "Impossible" << '\n';
        return 0;
      }
    } else {
      if (ans[i] > ans[i - 1]) {
        cout << "Impossible" << '\n';
        return 0;
      }
    }
  }
  for (Long x : ans) cout << x << " ";
  cout << '\n';
  return 0;
}

