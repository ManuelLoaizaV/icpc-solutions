//https://www.spoj.com/problems/ORDERS/en/
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <iostream>
#include <vector>
#define FAST_IO ios::sync_with_stdio(0);cin.tie(nullptr)
using namespace std;
using namespace __gnu_pbds;

typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> OST;

void Solve(void) {
  int n;
  cin >> n;
  vector<int> cnt(n);
  for (int i = 0; i < n; i++) cin >> cnt[i];
  OST aux;
  for (int i = 1; i <= n; i++) aux.insert(i);
  vector<int> ans;
  for (int len = n - 1; len >= 0; len--) {
    int pos = len - cnt[len];
    int cur = *aux.find_by_order(len - cnt[len]);
    ans.push_back(cur);
    aux.erase(cur);
  }
  reverse(ans.begin(), ans.end());
  for (int i = 0; i < n; i++) {
    if (i > 0) cout << " ";
    cout << ans[i];
  }
  cout << '\n';
}

int main(void) {
  FAST_IO;
  int t;
  cin >> t;
  while (t--) Solve();
  return 0;
}
