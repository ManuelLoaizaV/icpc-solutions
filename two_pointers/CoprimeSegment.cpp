#include <bits/stdc++.h>
using namespace std;

typedef long long Long;

const int N = 1e5;
const int LG = 32 - __builtin_clz(N);

struct SparseTable {
  Long st[N][LG];
  Long f(const Long& x) { return x; }
  Long f(const Long& x, const Long& y) { return __gcd(x, y); }
  void Build(vector<Long>& a, int n) {
    for (int i = 0; i < n; i++) st[i][0] = f(a[i]);
    for (int j = 1; j < LG; j++)
      for (int i = 0; i + (1 << j) <= n; i++)
        st[i][j] = f(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
  }
  // O(1). Solo funciona con operadores idempotentes.
  Long Query(int l, int r) {
    int range = r - l + 1;
    int lg = 31 - __builtin_clz(range);
    return f(st[l][lg], st[r - (1 << lg) + 1][lg]);
  }
} st;

void Add(int l, int r, Long& g) {
  g = st.Query(l, r);
}

void Delete(int l, int r, Long& g) {
  g = st.Query(l + 1, r);
}

bool IsGood(int l, int r) {
  return st.Query(l, r) == 1;
}

int main(void) {
  int n;
  scanf("%d", &n);
  vector<Long> a(n);
  for (int i = 0; i < n; i++) scanf("%lld", &a[i]);
  st.Build(a, n);
  int ans = n + 1;
  int l = 0;
  Long g = a[0];
  for (int r = 0; r < n; r++) {
    Add(l, r, g);
    while (l < r && IsGood(l + 1, r)) Delete(l++, r, g);
    if (g == 1) ans = min(ans, r - l + 1);
  }
  if (ans == n + 1) {
    printf("-1\n");
  } else {
    printf("%d\n", ans);
  }
  return 0;
}
