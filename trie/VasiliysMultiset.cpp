//https://codeforces.com/problemset/problem/706/D
#include <bits/stdc++.h>
using namespace std;

typedef long long Long;

const int C = (int) '0';
const int LG = 32;
const int N = 3200000 + 1;  // total de caracteres + 1
const int ALPHABET = 2;

Long pot[LG];

struct Trie {
  int trie[N][ALPHABET];
  int cnt[N];
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
      cnt[u]++;
    }
    is_terminal[u] = true;
  }
  void DeleteWord(const string& s) {
    int n = s.size();
    int u = 0;
    for (int i = 0; i < n; i++) {
      int c = s[i] - C;
      int next_u = trie[u][c];
      cnt[next_u]--;
      if (cnt[next_u] == 0) trie[u][c] = 0;
      u = next_u;
    }
    if (cnt[u] == 0) is_terminal[u] = false;
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

string LongToString(Long n) {
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

int main(void) {
  ios::sync_with_stdio(0);
  cin.tie(0);
  pot[0] = 1;
  for (int i = 1; i < LG; i++) pot[i] = 2 * pot[i - 1];
  trie.AddWord(LongToString(0));
  int q;
  cin >> q;
  while (q--) {
    char t;
    Long n;
    cin >> t >> n;
    if (t == '+') {
      trie.AddWord(LongToString(n));
    } else if (t == '-') {
      trie.DeleteWord(LongToString(n));
    } else {
      cout << trie.GetMax(LongToString(n)) << '\n';
    }
  }
  return 0;
}
