// https://codeforces.com/problemset/problem/474/B
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n;
  vector<int> v(n);
  for (int i = 0; i < n; i++) cin >> v[i];
  vector<int> prefixes(n);
  prefixes[0] = v[0];
  for (int i = 1; i < n; i++) {
    prefixes[i] = prefixes[i - 1] + v[i];
  }
  int q;
  cin >> q;
  while (q--) {
    int worm;
    cin >> worm;
    int box_index = lower_bound(prefixes.begin(), prefixes.end(), worm) - prefixes.begin();
    cout << box_index + 1 << '\n';
  }
  return 0;
}