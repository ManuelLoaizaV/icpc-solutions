// https://open.kattis.com/problems/busnumbers
#include <bits/stdc++.h>
using namespace std;

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n;
  vector<int> v(n);
  for (int i = 0; i < n; i++) {
    cin >> v[i];
  }
  sort(v.begin(), v.end());
  for (int i = 0; i < n; i++) {
    if (i > 0) {
      cout << " ";
    }
    if (i < n - 2 && v[i] + 2 == v[i + 2]) {
      int j = i + 2;
      while (j < n && v[j] == v[j - 1] + 1) j++;
      cout << v[i] << "-" << v[j - 1];
      i = j - 1;
    } else {
      cout << v[i];
    }
  }
  cout << '\n';
  return 0;
}