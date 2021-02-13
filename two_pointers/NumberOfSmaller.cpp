#include <bits/stdc++.h>
using namespace std;

int main(void) {
  int n, m;
  scanf("%d %d", &n, &m);
  vector<int> a(n), b(m);
  for (int i = 0; i < n; i++) scanf("%d", &a[i]);
  for (int i = 0; i < m; i++) scanf("%d", &b[i]);
  int i = 0;
  for (int j = 0; j < m; j++) {
    while (i < n && a[i] < b[j]) i++;
    printf("%d ", i);
  }
  printf("\n");
  return 0;
}
