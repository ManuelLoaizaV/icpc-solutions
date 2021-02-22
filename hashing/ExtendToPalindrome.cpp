//https://onlinejudge.org/index.php?option=onlinejudge&Itemid=8&page=show_problem&problem=2470
#include <bits/stdc++.h>
using namespace std;

void __print(int x) {cerr << x;}
void __print(long x) {cerr << x;}
void __print(long long x) {cerr << x;}
void __print(unsigned x) {cerr << x;}
void __print(unsigned long x) {cerr << x;}
void __print(unsigned long long x) {cerr << x;}
void __print(float x) {cerr << x;}
void __print(double x) {cerr << x;}
void __print(long double x) {cerr << x;}
void __print(char x) {cerr << '\'' << x << '\'';}
void __print(const char *x) {cerr << '\"' << x << '\"';}
void __print(const string &x) {cerr << '\"' << x << '\"';}
void __print(bool x) {cerr << (x ? "true" : "false");}

template<typename T, typename V>
void __print(const pair<T, V> &x) {cerr << '{'; __print(x.first); cerr << ','; __print(x.second); cerr << '}';}
template<typename T>
void __print(const T &x) {int f = 0; cerr << '{'; for (auto &i: x) cerr << (f++ ? "," : ""), __print(i); cerr << "}";}
void _print() {cerr << "]\n";}
template <typename T, typename... V>
void _print(T t, V... v) {__print(t); if (sizeof...(v)) cerr << ", "; _print(v...);}
#ifndef ONLINE_JUDGE
#define debug(x...) cerr << "[" << #x << "] = ["; _print(x)
#else
#define debug(x...)
#endif

typedef long long Long;
typedef pair<Long, Long> Pair;

const int N = 2e5;
const Long B[2] = {29LL, 31LL};
const Long MOD = 1e9 + 7;

typedef long long Long;

Long Add(Long a, Long b) {
  return (a + b) % MOD;
}

Long Sub(Long a, Long b) {
  return (a - b + MOD) % MOD;
}

Long Mul(Long a, Long b) {
  return (a * b) % MOD;
}

Long P[N][2];

struct Hash {
  Long h[N][2];
  void Build(const string& s) {
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
} h, rh;

void Precalculate(int n) {
  P[0][0] = P[0][1] = 1;
  for (int i = 1; i < n; i++) {
    for (int j = 0; j < 2; j++) {
      P[i][j] = Mul(P[i - 1][j], B[j]);
    }
  }
}

void Solve(const string& s) {
  string rs = s;
  reverse(rs.begin(), rs.end());
  h.Build(s);
  rh.Build(rs);
  int n = s.size();
  // Si la cadena es palindroma
  if (h.Query(0, n - 1) == rh.Query(0, n - 1)) {
    cout << s << '\n';
    return;
  }
  for (int len = 1; len < n; len++) {
    int new_len = n + len;
    int center, l1, r1, l2, r2, sz;
    bool is_valid = false;
    if (new_len & 1) {
      center = new_len / 2;
      l2 = center + 1;
      r2 = n - 1;
      sz = r2 - l2 + 1;
      if (sz == 0) is_valid = true;
      r1 = center - 1;
      l1 = r1 - sz + 1;
    } else {
      center = new_len / 2 - 1;
      l2 = center + 1;
      r2 = n - 1;
      sz = r2 - l2 + 1;
      l1 = center - sz + 1;
      r1 = center;
      if (sz == 0) is_valid = true;
    }
    //debug(new_len, center, l1, r1, l2, r2, sz);
    if (!is_valid && h.Query(l1, r1) == rh.Query(n - 1 - r2, n - 1 - l2)) is_valid = true;
    if (is_valid) {
      string ans = s;
      for (int i = 0; i < len; i++) ans += s[len - i - 1];
      cout << ans << '\n';
      return;
    }
  }
}

int main(void) {
  ios::sync_with_stdio(0);
  cin.tie(0);
  Precalculate(N);
  string s;
  while (cin >> s) Solve(s);
  return 0;
}
