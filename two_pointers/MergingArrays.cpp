#include <bits/stdc++.h>
using namespace std;

int main(void) {
  int n, m;
  scanf("%d %d", &n, &m);
  vector<int> a(n), b(m);
  for (int i = 0; i < n; i++) scanf("%d", &a[i]);
  for (int i = 0; i < m; i++) scanf("%d", &b[i]);
  vector<int> ans;
  int i, j;
  i = j = 0;
  while (i < a.size() || j < b.size()) {
    if (j == b.size() || i < a.size() && a[i] < b[j]) {
      ans.push_back(a[i++]);
    } else {
      ans.push_back(b[j++]);
    }
  }
  for (int x : ans) printf("%d ", x);
  printf("\n");
  return 0;
}
