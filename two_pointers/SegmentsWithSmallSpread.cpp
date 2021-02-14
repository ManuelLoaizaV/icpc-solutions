#include <bits/stdc++.h>
using namespace std;

typedef pair<long long, long long> Pair;
typedef long long Long;

const int N = 1e5;
const int LG = 32 - __builtin_clz(N);

struct SparseTable {
  Pair st[N][LG];
  Pair f(const Long& x) { return {x, x}; }
  Pair f(const Pair& x, const Pair& y) { return {min(x.first, y.first), max(x.second, y.second)}; }
  void Build(vector<Long>& a, int n) {
    for (int i = 0; i < n; i++) st[i][0] = f(a[i]);
    for (int j = 1; j < LG; j++)
      for (int i = 0; i + (1 << j) <= n; i++)
        st[i][j] = f(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
  }
  // O(1). Solo funciona con operadores idempotentes.
  Pair Query(int l, int r) {
    int range = r - l + 1;
    int lg = 31 - __builtin_clz(range);
    return f(st[l][lg], st[r - (1 << lg) + 1][lg]);
  }
} st;

void Add(int l, int r, Long& delta) {
  Pair query = st.Query(l, r);
  delta = query.second - query.first;
}

void Delete(int l, int r, Long& delta) {
  Pair query = st.Query(l + 1, r);
  delta = query.second - query.first;
}

bool IsGood(Long delta, Long k) {
  return delta <= k;
}

int main(void) {
  int n;
  Long k;
  scanf("%d %lld", &n, &k);
  vector<Long> a(n);
  for (int i = 0; i < n; i++) scanf("%lld", &a[i]);
  st.Build(a, n);
  Long ans = 0;
  Long delta = 0;
  int l = 0;
  for (int r = 0; r < n; r++) {
    Add(l, r, delta);
    while (!IsGood(delta, k)) Delete(l++, r, delta);
    ans += (Long) (r - l + 1);
  }
  printf("%lld\n", ans);
  return 0;
}
