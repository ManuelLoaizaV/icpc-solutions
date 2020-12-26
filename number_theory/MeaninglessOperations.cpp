#include <iostream>
#define FAST_IO ios::sync_with_stdio(0);cin.tie(nullptr)
using namespace std;

typedef long long Long;

int main(void) {
  FAST_IO;
  Long q;
  cin >> q;
  while (q--) {
    Long n;
    cin >> n;
    Long mx = (1LL << (32 - __builtin_clz(n))) - 1LL;
    if (n == mx) {
      Long who = -1;
      for (Long i = 2; i * i <= mx; i++) {
        if (mx % i == 0) {
          who = mx / i;
          break;
        }
      }
      if (who == -1) who = 1;
      cout << who << '\n';
    } else {
      cout << mx << '\n';
    }
  }
  return 0;
}
