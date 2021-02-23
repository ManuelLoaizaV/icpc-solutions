// https://codeforces.com/gym/101628/problem/K
// MLE en caso 10, sin embargo, la estructura es correcta
#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
using namespace std;

const int C = (int) 'a';
const int N = 1e5;
const int ALPHABET = 26;
const map<int, int> E;

struct Trie {
  //vector<map<int, int>> trie;
  //vector<int> cnt;
  //vector<bool> is_terminal;
  map<int, map<int, int>> trie;
  map<int, int> cnt;
  map<int, bool> is_terminal;
  int nodes = 1;
  void Build(void) {
    trie.clear();
    cnt.clear();
    is_terminal.clear();
    //trie.push_back(E);
    //cnt.push_back(0);
    //is_terminal.push_back(false);
    trie[0] = E;
    cnt[0] = 0;
    is_terminal[0] = false;
    nodes = 1;
  }
  void AddWord(const string& s) {
    int n = s.size();
    int u = 0;
    for (int i = 0; i < n; i++) {
      int c = s[i] - C;
      if (trie[u].count(c) == 0) {
        //trie[u][c] = nodes++;
        //trie.push_back(E);
        //cnt.push_back(0);
        //is_terminal.push_back(false);
        trie[u][c] = nodes;
        trie[nodes] = E;
        cnt[nodes] = 0;
        is_terminal[nodes] = false;
        nodes++;
      }
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
      if (cnt[next_u] == 0) trie[u].erase(c);
      u = next_u;
    }
    is_terminal[u] = false;
  }
  bool IsPrefix(const string& s) {
    int n = s.size();
    int u = 0;
    for (int i = 0; i < n; i++) {
      int c = s[i] - C;
      if (trie[u].count(c) == 0) return false;
      u = trie[u][c];
    }
    return true;
  }
  bool ExistPrefixOf(const string& s) {
    int n = s.size();
    int u = 0;
    for (int i = 0; i < n; i++) {
      int c = s[i] - C;
      if (trie[u].count(c) == 0) return false;
      u = trie[u][c];
      if (is_terminal[u]) return true;
    }
    return false;
  }
} trie;

struct SegmentTree {
  Trie tree[2 * N];
  void Build(int id, int tl, int tr) {
    tree[id].Build();
    if (tl == tr) return;
    int tm = (tl + tr) / 2;
    int left = id + 1;
    int right = id + 2 * (tm - tl + 1);
    Build(left, tl, tm);
    Build(right, tm + 1, tr);
  }
  void DeleteWord(int pos, const string& s, int id, int tl, int tr) {
    tree[id].DeleteWord(s);
    if (tl == tr) return;
    int tm = (tl + tr) / 2;
    int left = id + 1;
    int right = id + 2 * (tm - tl + 1);
    if (pos <= tm) {
      DeleteWord(pos, s, left, tl, tm);
    } else {
      DeleteWord(pos, s, right, tm + 1, tr);
    }
  }
  void AddWord(int pos, const string& s, int id, int tl, int tr) {
    tree[id].AddWord(s);
    if (tl == tr) return;
    int tm = (tl + tr) / 2;
    int left = id + 1;
    int right = id + 2 * (tm - tl + 1);
    if (pos <= tm) {
      AddWord(pos, s, left, tl, tm);
    } else {
      AddWord(pos, s, right, tm + 1, tr);
    }
  }
  bool Query2(int l, int r, const string& s, int id, int tl, int tr) {
    if (l <= tl && tr <= r) return tree[id].ExistPrefixOf(s);
    int tm = (tl + tr) / 2;
    int left = id + 1;
    int right = id + 2 * (tm - tl + 1);
    if (r <= tm) return Query2(l, r, s, left, tl, tm);
    if (tm < l) return Query2(l, r, s, right, tm + 1, tr);
    return Query2(l, r, s, left, tl, tm) || Query2(l, r, s, right, tm + 1, tr);
  }
  bool Query3(int l, int r, const string& s, int id, int tl, int tr) {
    if (l <= tl && tr <= r) return tree[id].IsPrefix(s);
    int tm = (tl + tr) / 2;
    int left = id + 1;
    int right = id + 2 * (tm - tl + 1);
    if (r <= tm) return Query3(l, r, s, left, tl, tm);
    if (tm < l) return Query3(l, r, s, right, tm + 1, tr);
    return Query3(l, r, s, left, tl, tm) || Query3(l, r, s, right, tm + 1, tr);
  }
} st;

string words[N];

int main(void) {
  ios::sync_with_stdio(0);
  cin.tie(0);
  int n;
  cin >> n;
  st.Build(1, 0, n - 1);
  for (int i = 0; i < n; i++) {
    cin >> words[i];
    st.AddWord(i, words[i], 1, 0, n - 1);
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
      st.DeleteWord(pos, words[pos], 1, 0, n - 1);
      cin >> words[pos];
      st.AddWord(pos, words[pos], 1, 0, n - 1);
    } else if (t == 2) {
      int l, r;
      string query;
      cin >> l >> r >> query;
      if (st.Query2(l - 1, r - 1, query, 1, 0, n - 1)) {
        cout << "Y\n";
      } else {
        cout << "N\n";
      }
    } else {
      int l, r;
      string query;
      cin >> l >> r >> query;
      if (st.Query3(l - 1, r - 1, query, 1, 0, n - 1)) {
        cout << "Y\n";
      } else {
        cout << "N\n";
      }
    }
  }
  return 0;
}
