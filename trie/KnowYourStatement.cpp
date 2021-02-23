//https://codeforces.com/problemset/gymProblem/101628/K
#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 1e5;
const int C = (int)'a';
const int N = 1e6 + 1;
const int ALPHABET = 26;

string words[MAX_N];

struct Trie {
  map<int, int> trie[N];
  set<int> id[N];
  set<int> is_terminal[N];
  int nodes = 1;
  void Build(void) {
    for (int i = 0; i < nodes; i++) {
      trie[i].clear();
      id[i].clear();
      is_terminal[i].clear();
    }
    nodes = 1;
  }
  void AddWord(const string& s, int pos) {
    int n = s.size();
    int u = 0;
    for (int i = 0; i < n; i++) {
      int c = s[i] - C;
      if (trie[u].count(c) == 0) trie[u][c] = nodes++;
      u = trie[u][c];
      id[u].insert(pos);
    }
    is_terminal[u].insert(pos);
  }
  void DeleteWord(const string& s, int pos) {
    int n = s.size();
    int u = 0;
    for (int i = 0; i < n; i++) {
      int c = s[i] - C;
      int next_u = trie[u][c];
      id[next_u].erase(pos);
      if (id[next_u].size() == 0) trie[u].erase(c);
      u = next_u;
    }
    is_terminal[u].erase(pos);
  }
  bool Query(const string& s, int l, int r, int t) {
    int n = s.size();
    int u = 0;
    for (int i = 0; i < n; i++) {
      int c = s[i] - C;
      if (trie[u].count(c) == 0) return false;
      u = trie[u][c];
      auto it = id[u].lower_bound(l);
      if (it == id[u].end() || *it > r) return false;
      if (t == 2) {
        it = is_terminal[u].lower_bound(l);
        if (it != is_terminal[u].end() && *it <= r) return true;
      }
    }
    if (t == 2) return false;
    return true;
  }
} trie;

int main(void) {
  ios::sync_with_stdio(0);
  cin.tie(0);
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> words[i];
    trie.AddWord(words[i], i);
  }
  int q;
  cin >> q;
  while (q--) {
    int t;
    cin >> t;
    if (t == 1) {
      int pos;
      cin >> pos;
      pos--;
      trie.DeleteWord(words[pos], pos);
      cin >> words[pos];
      trie.AddWord(words[pos], pos);
    } else {
      int l, r;
      string query;
      cin >> l >> r >> query;
      l--;
      r--;
      if (trie.Query(query, l, r, t)) {
        cout << "Y\n";
      } else {
        cout << "N\n";
      }
    }
  }
  return 0;
}
