// https://open.kattis.com/problems/different
#include <bits/stdc++.h>
using namespace std;

typedef long long Long;

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  Long a, b;
  while (cin >> a >> b) {
    Long diff = abs(a - b);
    cout << diff << '\n';
  }
  return 0;
}