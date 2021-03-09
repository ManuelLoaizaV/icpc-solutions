//https://codeforces.com/problemset/problem/842/D
#include <bits/stdc++.h>
using namespace std;

const int N = 5700000 + 1;  // total de caracteres + 1
const int MAX_N = 5e3;
const int LEN = 19;
const int ALPHABET = 2;
const int C = (int) '0';

struct Trie {
  map<int, int> trie[N];
  int cnt[N];
  bool is_terminal[N];
  int modify[LEN];
  int nodes = 1;
  void Clear(void) {
    for (int i = 0; i < LEN; i++) modify[i] = 0;
    for (int i = 0; i < nodes; i++) {
      is_terminal[i] = false;
      trie[i].clear();
      cnt[i] = 0;
    }
    nodes = 1;
  }
  void AddWord(const string& s) {
    int n = s.size();
    int u = 0;
    for (int i = 0; i < n; i++) {
      int c = s[i] - C;
      if (trie[u].count(c) == 0) trie[u][c] = nodes++;
      u = trie[u][c];
      cnt[u]++;
    }
    is_terminal[u] = true;
  }
  void Update(const string& s) {
    for (int i = 0; i < LEN; i++) modify[i] ^= (s[i] - C);
  }
  int Mex(void) {
    int ans = 0;
    int u = 0;
    for (int i = 0; i < LEN; i++) {
      int nxt = modify[i];
      int len = LEN - 1 - i;
      // Si no hay una rama con cero, el mex tiene cero en todo lo que sigue
      if (trie[u].count(nxt) == 0) return ans;
      // En otro caso, chequeo si es que la rama del cero esta completa
      int v = trie[u][nxt];
      // En caso estar completa, me muevo hacia la rama con unos
      if (cnt[v] == (1 << len)) {
        ans += (1 << len);
        if (trie[u].count(nxt ^ 1) == 0) return ans;
        u = trie[u][nxt ^ 1];
      } else {
        // Sino, me muevo hacia la rama de ceros
        u = v;
      }
    }
    return ans;
  }
} trie;

string IntToString(int n) {
  string ans = "";
  for (int i = 0; i < LEN; i++) {
    ans += char(C + (n & 1));
    n >>= 1;
  }
  reverse(ans.begin(), ans.end());
  return ans;
}

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int n, m;
  cin >> n >> m;
  trie.Clear();
  set<int> a;
  for (int i = 0; i < n; i++) {
    int b;
    cin >> b;
    a.insert(b);
  }
  for (int b : a) trie.AddWord(IntToString(b));
  while (m--) {
    int x;
    cin >> x;
    trie.Update(IntToString(x));
    cout << trie.Mex() << '\n';
  }
  return 0;
}
