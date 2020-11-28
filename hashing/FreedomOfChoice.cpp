#include <iostream>
#include <set>
#include <utility>
#include <vector>
#define FAST_IO ios::sync_with_stdio(0);cin.tie(nullptr)
using namespace std;

typedef long long Long;
typedef pair<Long, Long> Pair;

const int N = 1e5;
const Long B[2] = {29LL, 31LL};
const Long MOD = 1e9 + 7;

Long P[N][2];

Long Add(Long a, Long b) {
  return (a + b) % MOD;
}

Long Mul(Long a, Long b) {
  return (a * b) % MOD;
}

Long Sub(Long a, Long b) {
  return (a - b + MOD) % MOD;
}

struct Hash {
  Long h[N][2];

  void Initialize(const string& s) {
    int n = s.size();
    h[0][0] = h[0][1] = s[0] - 'A' + 1;
    for (int i = 1; i < n; i++) {
      for (int j = 0; j < 2; j++) {
        h[i][j] = Add(Mul(h[i - 1][j], B[j]), s[i] - 'A' + 1);
      }
    }
  }

  Pair Query(int l, int r) {
    vector<Long> ans(2);
    for (int j = 0; j < 2; j++) {
      if (l == 0) {
        ans[j] = h[r][j];
      } else {
        ans[j] = Sub(h[r][j], Mul(h[l - 1][j], P[r - l + 1][j]));
      }
    }
    return {ans[0], ans[1]};
  }
};

void Precalculate(int n) {
  P[0][0] = P[0][1] = 1;
  for (int i = 1; i < n; i++) {
    for (int j = 0; j < 2; j++) {
      P[i][j] = Mul(P[i - 1][j], B[j]);
    }
  }
}

int IsOk(int len, int n, Hash& hs, Hash& ht) {
  set<Pair> aux;
  for (int i = 0; i < n - len + 1; i++) {
    Pair cur = ht.Query(i, i + len - 1);
    aux.insert(cur);
  }
  for (int i = 0; i < n - len + 1; i++) {
    Pair cur = hs.Query(i, i + len - 1);
    if (aux.count(cur) > 0) return i;
  }
  return -1;
}

int main(void) {
  FAST_IO;
  int n;
  cin >> n;
  Precalculate(n);
  
  string s, t;
  cin >> s >> t;
  
  Hash hs, ht;
  hs.Initialize(s);
  ht.Initialize(t);

  int l = 1;
  int r = n;

  if (IsOk(l, n, hs, ht) == -1) {
    cout << '\n';
    return 0;
  }

  if (IsOk(r, n, hs, ht) != -1) {
    cout << t << '\n';
    return 0;
  }

  while (r - l > 1) {
    int m = (l + r) / 2;
    if (IsOk(m, n, hs, ht) != -1) {
      l = m;
    } else {
      r = m;
    }
  }

  int pos = IsOk(l, n, hs, ht);
  for (int i = 0; i < l; i++) cout << s[pos + i];
  cout << '\n';
  return 0;
}
