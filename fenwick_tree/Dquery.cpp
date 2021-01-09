//https://www.spoj.com/problems/DQUERY/en/
#include <algorithm>
#include <iostream>
#include <vector>
#define FAST_IO ios::sync_with_stdio(0);cin.tie(nullptr)
using namespace std;

const int N = 3e4;
const int MAX_N = 1e6;

struct DQuery {
  int l, r, id;

  bool operator < (const DQuery& other) {
    return r < other.r;
  }
};

struct FenwickTree {
  int tree[N + 1];

  void Update(int i, int delta) {
    while (i <= N) {
      tree[i] += delta;
      i += (i & -i);
    }
  }

  int Query(int i) {
    int ans = 0;
    while (i > 0) {
      ans += tree[i];
      i -= (i & -i);
    }
    return ans;
  }
} ft;

int main(void) {
  FAST_IO;
  int n;
  cin >> n;
  vector<int> a(n + 1);
  for (int i = 1; i <= n; i++) cin >> a[i];
  int q;
  cin >> q;
  vector<DQuery> dq(q);
  for (int i = 0; i < q; i++) {
    cin >> dq[i].l;
    cin >> dq[i].r;
    dq[i].id = i;
  }
  
  vector<int> ans(q);
  sort(dq.begin(), dq.end());
  vector<int> last(MAX_N + 1, 0);
  int cur = 0;
  for (int i = 0; i < q; i++) {
    while (cur < dq[i].r) {
      cur++;
      if (last[a[cur]] != 0) ft.Update(last[a[cur]], -1);
      ft.Update(cur, 1);
      last[a[cur]] = cur;
    }
    ans[dq[i].id] = ft.Query(dq[i].r) - ft.Query(dq[i].l - 1);
  }
  for (int i = 0; i < q; i++) {
    cout << ans[i] << '\n';
  }
  return 0;
}
