//https://codeforces.com/problemset/problem/459/D
#include <bits/stdc++.h>
using namespace std;

typedef long long Long;

const int N = 1e6;

struct FenwickTree {
  Long tree[N + 1];
  void Update(int i, Long delta) {
    while (i <= N) {
      tree[i] += delta;
      i += (i & -i);
    }
  }
  int Query(int i) {
    int sum = 0;
    while (i > 0) {
      sum += tree[i];
      i -= (i & -i);
    }
    return sum;
  }
} ft;

int Compress(vector<int>& a) {
  int n = a.size();
  vector<pair<int, int>> pairs(n);
  for (int i = 0; i < n; i++) pairs[i] = {a[i], i};
  sort(pairs.begin(), pairs.end());
  int nxt = 0;
  for (int i = 0; i < n; i++) {
    if (i > 0 && pairs[i].first != pairs[i - 1].first) nxt++;
    a[pairs[i].second] = nxt;
  }
  return nxt + 1;
}

int main(void) {
  ios::sync_with_stdio(0);
  cin.tie(0);
  int n;
  cin >> n;
  vector<int> a(n);
  for (int i = 0; i < n; i++) cin >> a[i];
  int sz = Compress(a);
  vector<int> frequency(sz, 0);
  // Creo los prefijos
  vector<int> prefix(n, 0);
  for (int i = 0; i < n; i++) {
    frequency[a[i]]++;
    prefix[i] = frequency[a[i]];
  }
  // Analizo los sufijos
  for (int i = 0; i < sz; i++) frequency[i] = 0;
  Long ans = 0;
  for (int i = n - 1; i >= 0; i--) {
    ans += ft.Query(prefix[i]);
    frequency[a[i]]++;
    ft.Update(frequency[a[i]] + 1, 1LL);
  }
  cout << ans << '\n';
  return 0;
}
