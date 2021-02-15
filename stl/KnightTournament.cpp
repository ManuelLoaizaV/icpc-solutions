//https://codeforces.com/problemset/problem/356/A
#include <bits/stdc++.h>
using namespace std;

int main(void) {
  ios::sync_with_stdio(0);
  cin.tie(0);
  int n, m;
  cin >> n >> m;
  set<int> knights;
  for (int i = 0; i < n; i++) knights.insert(i);
  vector<int> ans(n, -1);
  while (m--) {
    int l, r, x;
    cin >> l >> r >> x;
    l--;
    r--;
    x--;
    auto it = knights.lower_bound(l);
    vector<int> aux;
    while (it != knights.end() && *it <= r) {
      aux.push_back(*it);
      it++;
    }
    for (auto knight : aux) {
      if (knight != x) {
        ans[knight] = x;
        knights.erase(knight);
      }
    }
  }
  for (int i = 0; i < n; i++) cout << ans[i] + 1 << " ";
  cout << '\n';
  return 0;
}
