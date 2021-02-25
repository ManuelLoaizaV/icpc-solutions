//https://www.spoj.com/problems/SUFEQPRE/
#include <bits/stdc++.h>
using namespace std;

typedef long long Long;

const Long MOD = 1e9 + 7;
const Long B = 67;
const int N = 1e6 + 50;
const Long C = (Long) 'a';

Long Add(Long a, Long b) { return (a + b) % MOD; }
Long Mul(Long a, Long b) { return (a * b) % MOD; }
Long Sub(Long a, Long b) { return (a - b + MOD) % MOD; }

struct Hash {
  Long mod, base;
  vector<Long> pot;
  vector<Long> h;
  Hash(void) {}
  Hash(Long new_mod = MOD, Long new_base = B, Long new_n = N) {
    mod = new_mod;
    base = new_base;
    h = vector<Long>(new_n); 
    pot = vector<Long>(new_n);
    pot[0] = 1;
    for (int i = 1; i < new_n; i++) pot[i] = Mul(pot[i - 1], base);
  }
  void Build(const string& s) {
    int n = s.size();
    int len = h.size();
    for (int i = 0; i < n; i++) {
      h[i] = s[i] - C + 1;
      if (i > 0) h[i] = Add(h[i], Mul(h[i - 1], base));
    }
  }
  Long Query(int l, int r) {
    if (l == 0) return h[r];
    return Sub(h[r], Mul(h[l - 1], pot[r - l + 1]));
  }
};

int main(void) {
  ios::sync_with_stdio(0);
  cin.tie(0);
  Hash h(MOD, B);
  int t;
  cin >> t;
  for (int i = 1; i <= t; i++) {
    cout << "Case " << i << ": ";
    string s;
    cin >> s;
    h.Build(s);
    int n = s.size();
    int ans = 0;
    for (int i = 0; i < n - 1; i++)
      if (h.Query(0, i) == h.Query(n - 1 - i, n - 1)) ans++;
    cout << ans << '\n';
  }
  return 0;
}
