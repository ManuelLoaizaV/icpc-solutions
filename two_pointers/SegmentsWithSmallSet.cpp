#include <bits/stdc++.h>
using namespace std;

const int N = 1e5;

int frequency[N + 1];

void Add(int x, int& cnt) {
  frequency[x]++;
  if (frequency[x] == 1) cnt++;
}

void Delete(int x, int& cnt) {
  frequency[x]--;
  if (frequency[x] == 0) cnt--;
}

bool IsGood(int cnt, int k) {
  return cnt <= k;
}

int main(void) {
  int n, k;
  scanf("%d %d", &n, &k);
  vector<int> a(n);
  for (int i = 0; i < n; i++) scanf("%d", &a[i]);
  long long ans = 0;
  int current = 0;
  int l = 0;
  for (int r = 0; r < n; r++) {
    Add(a[r], current);
    while (!IsGood(current, k)) Delete(a[l++], current);
    ans += (long long) (r - l + 1);
  }
  printf("%lld\n", ans);
  return 0;
}
