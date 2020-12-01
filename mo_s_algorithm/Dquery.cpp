#include <algorithm>
#include <iostream>
#include <vector>
#define FAST_IO ios::sync_with_stdio(0);cin.tie(nullptr)
using namespace std;

const int SZ = 200;
const int N = 1e6 + 5;
int freq[N];

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
  void Add(int val, int& ans) {
    freq[val]++;
    if (freq[val] == 1) ans++;
  }
  void Delete(int val, int& ans) {
    freq[val]--;
    if (freq[val] == 0) ans--;
  }
  vector<int> Build(const vector<int>& a, vector<Query>& q) {
    sort(q.begin(), q.end());
    vector<int> ans(q.size());
    int l = 0;
    int r = -1;
    int acc = 0;
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
  int n;
  cin >> n;
  vector<int> a(n);
  for (int i = 0; i < n; i++) cin >> a[i];
  int q;
  cin >> q;
  vector<Query> queries;
  for (int i = 0; i < q; i++) {
    int l, r;
    cin >> l >> r;
    l--;
    r--;
    queries.push_back(Query(i, l, r));
  }
  vector<int> ans = mo.Build(a, queries);
  for (int x : ans) cout << x << '\n';
  return 0;
}
