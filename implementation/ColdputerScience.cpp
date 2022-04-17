// https://open.kattis.com/problems/cold
#include <bits/stdc++.h>
using namespace std;

typedef long long Long;

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  Long n;
  cin >> n;
  Long cnt = 0;
  while (n--) {
    Long t;
    cin >> t;
    if (t < 0) {
      cnt++;
    }
  }
  cout << cnt << '\n';
  return 0;
}