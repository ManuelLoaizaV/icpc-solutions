#include <bits/stdc++.h>
using namespace std;

void Solve(void) {
  int n;
  cin >> n;
  string s;
  cin >> s;
  vector<int> cnt(26, 0);
  for (int i = 0; i < n; i++) cnt[s[i] - 'A']++;
  int n_problems = 0;
  for (int i = 0; i < 26; i++) {
    if (cnt[i] > i) n_problems++;
  }
  cout << n_problems << '\n';
}

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int t;
  cin >> t;
  while (t--) Solve();
  return 0;
}
