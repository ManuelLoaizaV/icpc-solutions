//https://codeforces.com/problemset/problem/1355/B
#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

void Solve(void) {
  int n;
  cin >> n;
  vector<int> a(n);
  for (int i = 0; i < n; i++) cin >> a[i];
  sort(a.begin(), a.end());
  int ans = 0;
  int acc = 0;
  for (int i = 0; i < n; i++) {
    if (acc + 1 == a[i]) {
      ans++;
      acc = 0;
    } else {
      acc++;
    }
  }
  cout << ans << '\n';
}

int main(void) {
  ios::sync_with_stdio(0);
  cin.tie(nullptr);
  int t;
  cin >> t;
  while (t--) Solve();
  return 0;
}
