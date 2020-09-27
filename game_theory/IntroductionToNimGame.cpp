#include <bits/stdc++.h>
#define FAST_IO ios::sync_with_stdio(0);cin.tie(NULL)
using namespace std;

typedef long long Long;

void Solve() {
  Long n;
  cin >> n;
  Long ans = 0;
  for (int i = 0; i < n; i++) {
    Long x;
    cin >> x;
    ans ^= x;
  }
  if (ans) cout << "First" << '\n';
  else cout << "Second" << '\n';
}

int main() {
  FAST_IO;
  Long t;
  cin >> t;
  while (t--) Solve();
  return 0;
}
