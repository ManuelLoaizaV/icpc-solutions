//https://codeforces.com/problemset/problem/768/C
#include <iostream>
#include <vector>
using namespace std;

const int N = 1 << 10;

int main(void) {
  ios::sync_with_stdio(0);
  cin.tie(nullptr);
  int n, k, x;
  cin >> n >> k >> x;
  vector<int> a(n);
  for (int i = 0; i < n; i++) cin >> a[i];
  
  int cnt[N], acc[N];
  for (int i = 0; i < N; i++) cnt[i] = acc[i] = 0;
  for (int i = 0; i < n; i++) cnt[a[i]]++;
  acc[0] = cnt[0];
  for (int i = 1; i < N; i++) acc[i] = acc[i - 1] + cnt[i];

  int cur_cnt[N], cur_acc[N];
  for (int it = 0; it < k; it++) {
    for (int i = 0; i < N; i++) cur_cnt[i] = cur_acc[i] = 0;
    for (int i = 0; i < N; i++) {
      if (cnt[i] == 0) continue;
      int prev_acc = (i == 0) ? 0 : acc[i - 1];
      if (prev_acc & 1) {
        int add = cnt[i] / 2;
        cur_cnt[i ^ x] += add;
        cur_cnt[i] += (cnt[i] - add);
      } else {
        if (cnt[i] & 1) {
          int add = (cnt[i] + 1) / 2;
          cur_cnt[i ^ x] += add;
          cur_cnt[i] += (cnt[i] - add);
        } else {
          cur_cnt[i ^ x] += cnt[i] / 2;
          cur_cnt[i] += cnt[i] / 2;
        }
      }
    }
    for (int i = 0; i < N; i++) cnt[i] = cur_cnt[i];
    acc[0] = cnt[0];
    for (int i = 1; i < N; i++) acc[i] = acc[i - 1] + cnt[i];
  }
  int mn, mx;
  mn = mx = -1;
  for (int i = 0; i < N; i++) {
    if (cnt[i] > 0) {
      if (mn == -1) {
        mn = mx = i;
      } else {
        mn = min(mn, i);
        mx = max(mx, i);
      }
    }
  }
  cout << mx << " " << mn << '\n';
  return 0;
}
