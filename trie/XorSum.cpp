//https://icpcarchive.ecs.baylor.edu/index.php?option=onlinejudge&page=show_problem&problem=2683
#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << '\n'
using namespace std;

typedef long long Long;

const int C = (int) '0';
const int LG = 32;
const int N = 3200000 + 1;  // total de caracteres + 1
const int ALPHABET = 2;

Long pot[LG];

struct Trie {
  int trie[N][ALPHABET];
  bool is_terminal[N];
  int nodes = 1;
  void Build(void) {
    for (int i = 0; i < nodes; i++) {
      is_terminal[i] = false;
      for (int j = 0; j < ALPHABET; j++) trie[i][j] = 0;
    }
    nodes = 1;
  }
  void AddWord(const string& s) {
    int n = s.size();
    int u = 0;
    for (int i = 0; i < n; i++) {
      int c = s[i] - C;
      if (trie[u][c] == 0) trie[u][c] = nodes++;
      u = trie[u][c];
    }
    is_terminal[u] = true;
  }
  bool IsWord(const string& s) {
    int n = s.size();
    int u = 0;
    for (int i = 0; i < n; i++) {
      int c = s[i] - C;
      if (trie[u][c] == 0) return false;
      u = trie[u][c];
    }
    return is_terminal[u];
  }
  Long GetMax(const string& s) {
    Long ans = 0;
    int u = 0;
    for (int i = 0; i < LG; i++) {
      int c = s[i] - C;
      if (trie[u][1 - c] == 0) {
        u = trie[u][c];
      } else {
        ans += pot[LG - i - 1];
        u = trie[u][1 - c];
      }
    }
    return ans;
  }
} trie;

string IntToString(Long n) {
  string s = "";
  if (n == 0) {
    for (int i = 0; i < LG; i++) s += '0';
  } else {
    for (int i = 0; i < LG; i++) {
      if (n & 1) {
        s += '1';
      } else {
        s += '0';
      }
      n >>= 1;
    }
    reverse(s.begin(), s.end());
  }
  return s;
}

void Solve(void) {
  trie.Build();
  int n;
  cin >> n;
  vector<Long> a(n);
  for (int i = 0; i < n; i++) cin >> a[i];
  vector<Long> x(n);
  x[0] = a[0];
  for (int i = 1; i < n; i++) x[i] = x[i - 1] ^ a[i];
  trie.AddWord(IntToString(0));
  Long ans = 0;
  for (int i = 0; i < n; i++) {
    string cur = IntToString(x[i]);
    Long tmp = trie.GetMax(cur);
    ans = max(ans, tmp);
    if (!trie.IsWord(cur)) trie.AddWord(cur);
  }
  cout << ans << '\n';
}

int main(void) {
  ios::sync_with_stdio(0);
  cin.tie(0);
  pot[0] = 1LL;
  for (int i = 1; i < LG; i++) pot[i] = 2 * pot[i - 1];
  int t;
  cin >> t;
  while (t--) Solve();
  return 0;
}
