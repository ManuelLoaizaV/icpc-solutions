//https://onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=1960
#include <bits/stdc++.h>
using namespace std;

typedef long long Long;

const Long MOD = 1e9 + 7;
const Long B = 67;
const int N = 1e3;
const Long C = (Long) 'a';

Long Add(Long a, Long b, Long m) { return (a + b) % m; }
Long Mul(Long a, Long b, Long m) { return (a * b) % m; }
Long Sub(Long a, Long b, Long m) { return (a - b + m) % m; }

struct Hash {
  Long mod, base;
  vector<Long> pot;
  vector<vector<Long>> h;
  Hash(void) {}
  Hash(Long new_mod = MOD, Long new_base = B, Long new_n = N) {
    mod = new_mod;
    base = new_base;
    h = vector<vector<Long>> (new_n, vector<Long>(new_n, 0));
    pot = vector<Long>(new_n * new_n);
    pot[0] = 1;
    for (int i = 1; i < new_n * new_n; i++) pot[i] = Mul(pot[i - 1], base, mod);
  }
  void Build(const vector<string>& s) {
    int n = s.size();
    int m = s[0].size();
    int len = h.size();
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        h[i][j] = s[i][j] - C + 1;
        if (i > 0) h[i][j] = Add(h[i][j], Mul(h[i - 1][j], pot[len], mod), mod);
        if (j > 0) h[i][j] = Add(h[i][j], Mul(h[i][j - 1], base, mod), mod);
        if (i > 0 && j > 0) h[i][j] = Sub(h[i][j], Mul(Mul(base, pot[len], mod), h[i - 1][j - 1], mod), mod);
      }
    }
  }
  Long Query(int x, int y) {
    if (x < 0 || y < 0) return 0LL;
    return h[x][y];
  }
  Long Query(int x1, int y1, int x2, int y2) {
    Long len = h.size();
    Long ans = Query(x2, y2);
    ans = Sub(ans, Mul(Query(x2, y1 - 1), pot[y2 - y1 + 1], mod), mod);
    ans = Sub(ans, Mul(Query(x1 - 1, y2), pot[len * (x2 - x1 + 1)], mod), mod);
    ans = Add(ans, Mul(Query(x1 - 1, y1 - 1), pot[len * (x2 - x1 + 1) + (y2 - y1 + 1)], mod), mod);
    return ans;
  }
};

struct MultiHash {
  vector<Hash> hashes;
  MultiHash(void) {}
  MultiHash(const vector<Long>& mods, const vector<Long>& bases) {
    for (int i = 0; i < mods.size(); i++) hashes.push_back(Hash(mods[i], bases[i]));
  }
  void Build(const vector<string>& s) {
    for (int i = 0; i < hashes.size(); i++) hashes[i].Build(s);
  }
  vector<Long> Query(int x1, int y1, int x2, int y2) {
    vector<Long> ans;
    for (int i = 0; i < hashes.size(); i++)
      ans.push_back(hashes[i].Query(x1, y1, x2, y2));
    return ans;
  }
} hs, ht;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
Long random(Long a, Long b) { return uniform_int_distribution<Long> (a, b) (rng); }

vector<Long> GetBases(const vector<Long>& mods) {
  vector<Long> ans;
  for (Long m : mods) {
    Long base = 2LL * random(33, (m - 2) / 2) + 1;
    ans.push_back(base);
  }
  return ans;
}

void Solve(void) {
  int n, m;
  cin >> n >> m;
  vector<string> s(n);
  for (int i = 0; i < n; i++) cin >> s[i];
  int x, y;
  cin >> x >> y;
  vector<string> t(x);
  for (int i = 0; i < x; i++) cin >> t[i];
  hs.Build(s);
  ht.Build(t);
  int ans = 0;
  for (int i = 0; i < n - x + 1; i++) {
    for (int j = 0; j < m - y + 1; j++) {
      if (hs.Query(i, j, i + x - 1, j + y - 1) == ht.Query(0, 0, x - 1, y - 1)) ans++;
    }
  }
  cout << ans << '\n';
}

int main(void) {
  ios::sync_with_stdio(0);
  cin.tie(0);
  vector<Long> mods = {MOD, MOD + 2};
  vector<Long> bases = GetBases(mods);
  hs = MultiHash(mods, bases);
  ht = MultiHash(mods, bases);
  int t;
  cin >> t;
  while (t--) Solve();
  return 0;
}
