//https://www.spoj.com/problems/YODANESS/en/
#include <iostream>
#include <map>
#include <vector>
#define FAST_IO ios::sync_with_stdio(0);cin.tie(nullptr)
using namespace std;

typedef long long Long;

const int N = 3e4;

struct FenwickTree {
  Long tree[N + 1];

  void Build(int n) {
    for (int i = 0; i <= n; i++) tree[i] = 0;
  }

  void Update(int i, Long delta) {
    while (i <= N) {
      tree[i] += delta;
      i += (i & -i);
    }
  }

  Long Query(int i) {
    Long ans = 0LL;
    while (i > 0) {
      ans += tree[i];
      i -= (i & -i);
    }
    return ans;
  }
} ft;

void Solve(void) {
  int n;
  cin >> n;
  ft.Build(n);

  map<string, int> mp;
  string s;
  for (int i = 1; i <= n; i++) {
    cin >> s;
    mp[s] = i;
  }
  vector<int> a(n);
  for (int i = 0; i < n; i++) {
    cin >> s;
    a[i] = mp[s];
  }
  Long ans = 0;
  for (int i = n - 1; i >= 0; i--) {
    ans += ft.Query(a[i]);
    ft.Update(a[i] + 1, 1LL);
  }
  cout << ans << '\n';
}

int main(void) {
  FAST_IO;
  int t;
  cin >> t;
  while (t--) Solve();
  return 0;
}
