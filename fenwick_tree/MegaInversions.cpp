//https://www.spoj.com/problems/TRIPINV/en/
#include <iostream>
#include <vector>
#define FAST_IO ios::sync_with_stdio(0);cin.tie(nullptr)
using namespace std;

typedef long long Long;

const int N = 1e5;

struct FenwickTree {
  Long tree[N + 1];

  void Update(int i, Long delta) {
    while (i <= N) {
      tree[i] += delta;
      i += (i & -i);
    }
  }

  Long Query(int i) {
    Long ans = 0;
    while (i > 0) {
      ans += tree[i];
      i -= (i & -i);
    }
    return ans;
  }
} inv, trinv;

int main(void) {
  FAST_IO;
  int n;
  cin >> n;
  vector<Long> a(n);
  for (int i = 0; i < n; i++) cin >> a[i];
  Long ans = 0LL;
  for (int i = n - 1; i >= 0; i--) {
    ans += trinv.Query(a[i]);
    trinv.Update(a[i] + 1, inv.Query(a[i]));
    inv.Update(a[i] + 1, 1);
  }
  cout << ans << '\n';
  return 0;
}
