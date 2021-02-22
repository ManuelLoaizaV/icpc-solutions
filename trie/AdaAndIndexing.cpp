//https://www.spoj.com/problems/ADAINDEX/
#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 1;  // total de caracteres + 1
const int ALPHABET = 26;

struct Trie {
  int trie[N][ALPHABET];
  int cnt[N];
  bool is_terminal[N];
  int nodes = 1;
  void Build(void) {
    for (int i = 0; i < nodes; i++) {
      is_terminal[i] = false;
      cnt[i] = 0;
      for (int j = 0; j < ALPHABET; j++) trie[i][j] = 0;
    }
    nodes = 1;
  }
  void AddWord(const string& s) {
    int n = s.size();
    int u = 0;
    for (int i = 0; i < n; i++) {
      int c = s[i] - 'a';
      if (trie[u][c] == 0) trie[u][c] = nodes++;
      u = trie[u][c];
      cnt[u]++;
    }
    is_terminal[u] = true;
  }
  int IsPrefix(const string& s) {
    int n = s.size();
    int u = 0;
    for (int i = 0; i < n; i++) {
      int c = s[i] - 'a';
      if (trie[u][c] == 0) return 0;
      u = trie[u][c];
    }
    return cnt[u];
  }
  bool IsWord(const string& s) {
    int n = s.size();
    int u = 0;
    for (int i = 0; i < n; i++) {
      int c = s[i] - 'a';
      if (trie[u][c] == 0) return false;
      u = trie[u][c];
    }
    return is_terminal[u];
  }
} trie;

int main(void) {
  ios::sync_with_stdio(0);
  cin.tie(0);
  int n, q;
  cin >> n >> q;
  trie.Build();
  for (int i = 0; i < n; i++) {
    string s;
    cin >> s;
    trie.AddWord(s);
  }
  while (q--) {
    string s;
    cin >> s;
    cout << trie.IsPrefix(s) << '\n';
  }
  return 0;
}
