#include <bits/stdc++.h>
#define FAST_IO ios::sync_with_stdio(0);cin.tie(NULL)
using namespace std;

typedef long long Long;

void Solve() {
  Long n;
  cin >> n;
  Long ans = 0;
  for (Long i = 1; i <= n; i++) {
    Long cnt;
    cin >> cnt;
    ans ^= ((cnt & 1) * i);
  }
  if (ans) cout << "Tom Wins" << '\n';
  else cout << "Hanks Wins" << '\n';
}

int main() {
  FAST_IO;
  Long t;
  cin >> t;
  while (t--) Solve();
  return 0;
}
