#include <algorithm>
#include <iostream>
#include <vector>
#define FAST_IO ios::sync_with_stdio(0);cin.tie(nullptr)
using namespace std;

typedef unsigned long long Long;

const int SZ = 450;
const int N = 1e6 + 5;
Long freq[N];

struct Query {
  int id, l, r;
  Query() {}
  Query(int id, int l, int r) : id(id), l(l), r(r) {}
  bool operator < (const Query& other) const {
    int block = l / SZ;
    int other_block = other.l / SZ;
    if (block != other_block) return (block < other_block);
    return (r > other.r);
  }
};

struct Mo {
  void Add(Long val, Long& ans) {
    ans -= val * freq[val] * freq[val];
    freq[val]++;
    ans += val * freq[val] * freq[val];
  }
  void Delete(Long val, Long& ans) {
    ans -= val * freq[val] * freq[val];
    freq[val]--;
    ans += val * freq[val] * freq[val];
  }
  vector<Long> Build(const vector<Long>& a, vector<Query>& q) {
    sort(q.begin(), q.end());
    vector<Long> ans(q.size());
    int l = 0;
    int r = -1;
    Long acc = 0LL;
    for (int i = 0; i < q.size(); i++) {
      while (r < q[i].r) Add(a[++r], acc);
      while (l > q[i].l) Add(a[--l], acc);
      while (r > q[i].r) Delete(a[r--], acc);
      while (l < q[i].l) Delete(a[l++], acc);
      ans[q[i].id] = acc;
    }
    return ans;
  }
} mo;

int main(void) {
  FAST_IO;
  int n, q;
  cin >> n >> q;
  vector<Long> a(n);
  for (int i = 0; i < n; i++) cin >> a[i];
  vector<Query> queries;
  for (int i = 0; i < q; i++) {
    int l, r;
    cin >> l >> r;
    l--;
    r--;
    queries.push_back(Query(i, l, r));
  }
  vector<Long> ans = mo.Build(a, queries);
  for (Long x : ans) cout << x << '\n';
  return 0;
}
