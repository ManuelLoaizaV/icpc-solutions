#include <iostream>
#include <vector>
using namespace std;

typedef long long Long;

const int LG = 22;

int main(void) {
  ios::sync_with_stdio(0);
  cin.tie(nullptr);
  int n;
  cin >> n;
  vector<int> a(n);
  for (int i = 0; i < n; i++) cin >> a[i];
  Long ans = 0LL;
  Long p = 1LL;
  for (int bit = 0; bit < LG; bit++) {
    Long ones = 0;
    for (int i = 0; i < n; i++) {
      if (a[i] & 1) ones++;
      a[i] >>= 1;
    }
    Long zeroes = n - ones;
    ans += ones * zeroes * p;
    p <<= 1;
  }
  cout << ans << '\n';
  return 0;
}
