// https://www.spoj.com/problems/BTCK/en/
#include <bits/stdc++.h>
using namespace std;

typedef long long Long;

const int N = 10;
Long a[N];
Long permutation[N];

void Solve(void) {
  for (int i = 0; i < N; i++) {
    cin >> a[i];
    permutation[i] = i;
  }
  
  Long k;
  cin >> k;
  bool found = false;
  do {
    Long sum = 0;
    for (int i = 0; i < N; i++) {
      sum += permutation[i] * a[i];
      if (sum > k) break;
    }
    if (sum <= k) {
      found = true;
      break;
    }
  } while (next_permutation(permutation, permutation + N));

  if (found) {
    for (int i = 0; i < N; i++) {
      if (i > 0) cout << " ";
      cout << permutation[i];
    }
    cout << '\n';
  } else {
    cout << "-1" << '\n';
  }
}

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int t;
  cin >> t;
  while (t--) Solve();
  return 0;
}
