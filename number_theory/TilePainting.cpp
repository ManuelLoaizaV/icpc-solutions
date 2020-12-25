#include <iostream>
#define FAST_IO ios::sync_with_stdio(0);cin.tie(nullptr)
using namespace std;

typedef long long Long;

int main(void) {
  FAST_IO;
  Long n;
  cin >> n;
  Long p = n;
  Long cnt = 0;
  Long aux = n;
  for (Long i = 2; i * i <= n; i++) {
    if (aux % i == 0) {
      cnt++;
      p = i;
      while (aux % i == 0) aux /= i;
    }
  }
  if (p == n) {
    cout << p << '\n';
    return 0;
  }
  if (aux > 1) cnt++;
  if (cnt > 1) {
    cout << 1 << '\n';
    return 0;
  }
  cout << p << '\n';
  return 0;
}
