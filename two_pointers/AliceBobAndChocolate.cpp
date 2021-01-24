//https://codeforces.com/problemset/problem/6/C
#include <bits/stdc++.h>
using namespace std;

int main(void) {
  ios::sync_with_stdio(0);
  cin.tie(nullptr);
  int n;
  cin >> n;
  vector<int> a(n);
  for (int i = 0; i < n; i++) cin >> a[i];
  int l, r, alice, bob;
  alice = bob = l = 0;
  r = n - 1;
  int current_alice, current_bob;
  current_alice = current_bob = 0;
  while (l < r) {
    int mn = min(a[l], a[r]);
    a[l] -= mn;
    a[r] -= mn;
    current_alice += mn;
    current_bob += mn;
    if (a[l] == 0) {
      alice++;
      l++;
      current_alice = 0;
    }
    if (a[r] == 0) {
      bob++;
      r--;
      current_bob = 0;
    }
  }
  if (l == r) {
    if (current_alice == 0 && current_bob == 0) {
      alice++;
    } else {
      if (current_alice > 0) {
        alice++;
      } else {
        bob++;
      }
    }
  }
  cout << alice << " " << bob << '\n';
  return 0;
}
