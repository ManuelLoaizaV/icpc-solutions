//https://www.spoj.com/problems/ADAROBOT/
#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>
using namespace std;

typedef long long Long;

int main(void) {
  ios::sync_with_stdio(0);
  cin.tie(nullptr);
  Long q;
  cin >> q;
  vector<pair<Long, Long>> queries(q);
  for (Long i = 0; i < q; i++) {
    cin >> queries[i].first;
    queries[i].second = i;
  }
  sort(queries.begin(), queries.end());
  vector<Long> ans(q);
  Long t = 0;
  Long n = 0;
  Long bit;
  for (Long i = 0; i < q; i++) {
    while (n < queries[i].first) {
      n += 2;
      bit = 64LL - __builtin_clzl(n & -n);
      t = bit * bit * bit + t;
    }
    ans[queries[i].second] = t;
  }
  for (int i = 0; i < q; i++) cout << ans[i] << '\n';
  return 0;
}
