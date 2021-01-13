//https://codeforces.com/problemset/problem/1461/C
#include <iomanip>
#include <iostream>
#include <vector>
#define FAST_IO ios::sync_with_stdio(0);cin.tie(nullptr)
using namespace std;

typedef long double Double;

int GetFail(int n, const vector<int>& a) {
  for (int i = n - 1; i >= 0; i--) {
    if (a[i] != (i + 1)) return i + 1;
  }
  return 0;
}

void Solve(void) {
  int n, m;
  cin >> n >> m;
  vector<int> a(n);
  for (int i = 0; i < n; i++) cin >> a[i];
  int mn = GetFail(n, a);
  Double mul = 1;
  for (int i = 0; i < m; i++) {
    int r;
    Double p;
    cin >> r >> p;
    if (r >= mn) mul *= (1.0 - p);
  }
  Double ans = 1.0 - mul;
  if (mn == 0) ans = 1.0;
  cout << fixed << setprecision(10) << ans << '\n';
}

int main(void) {
  FAST_IO;
  int t;
  cin >> t;
  while (t--) Solve();
  return 0;
}
