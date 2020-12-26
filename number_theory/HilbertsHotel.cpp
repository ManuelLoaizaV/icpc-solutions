#include <iostream>
#include <set>
using namespace std;

typedef long long Long;

Long GetClass(Long num, Long mod) {
  if (num >= 0) return (num % mod);
  return (mod - ((-1) * num) % mod) % mod;
}

int main(void) {
  int t;
  cin >> t;
  while (t--) {
    Long n;
    cin >> n;
    bool is_ok = true;
    set<Long> uni;
    for (Long i = 0; i < n; i++) {
      Long a;
      cin >> a;
      Long clase = GetClass(a + i, n);
      if (uni.count(clase) > 0) is_ok = false;
      uni.insert(clase);
    }
    if (is_ok) {
      cout << "YES" << '\n';
    } else {
      cout << "NO" << '\n';
    }
  }
  return 0;
}
