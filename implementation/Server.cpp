// https://open.kattis.com/problems/server
#include <bits/stdc++.h>
using namespace std;

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int n, t;
  cin >> n >> t;
  vector<int> v(n);
  for (int i = 0; i < n; i++) cin >> v[i];
  int cnt = 0;
  int sum = 0;
  for (int i = 0; i < n; i++) {
    sum += v[i];
    if (sum <= t) {
      cnt++;
    } else {
      break;
    }
  }
  cout << cnt << '\n';
  return 0;
}