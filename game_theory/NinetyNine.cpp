//https://open.kattis.com/problems/ninetynine
#include <bits/stdc++.h>
#include <unistd.h>
#define FAST_IO ios::sync_with_stdio(0);cin.tie(NULL)
#define all(v) (v).begin(),(v).end()
using namespace std;

typedef int Long;
typedef long double Double;
typedef unsigned long long ULong;
typedef pair<Long, Long> Pair;

const int N = 1e6;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
Long random(Long a, Long b) { return uniform_int_distribution<Long> (a, b) (rng); }

int Query(int n) {
  cout << n << endl;
  if (n == 99) exit(0);
  cin >> n;
  return n;
}

void Solve(void) {
  int current = Query(2);
  while (true) {
    if (current % 3 == 0) {
      current = Query(current + 1);
    } else {
      current = Query(current + 3 - (current % 3));
    }
  }
}

int main(void) {
  //FAST_IO;
  int t = 1;
  //cin >> t;
  while (t--) Solve();
  return 0;
}

