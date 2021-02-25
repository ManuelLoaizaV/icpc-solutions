//https://codeforces.com/problemset/problem/817/E
#include <bits/stdc++.h>
using namespace std;

const int N = 2700000 + 1;  // total de caracteres + 1
const int ALPHABET = 2;
const int C = (int)'0';
const int L = 27;

struct Trie {
  map<int, int> trie[N];
  int cnt[N];
  bool is_terminal[N];
  int nodes = 1;
  void Clear(void) {
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
  bool IsWord(const string& s) {
    int n = s.size();
    int u = 0;
    for (int i = 0; i < n; i++) {
      int c = s[i] - C;
      if (trie[u].count(c) == 0) return false;
      u = trie[u][c];
    }
    return is_terminal[u];
  }
  int Count(const string& p, const string& l) {
    int n = p.size();
    int u = 0;
    int ans = 0;
    for (int i = 0; i < n; i++) {
      int p_i = p[i] - C;
      int l_i = l[i] - C;
      if (l_i == 1) {
        if (p_i == 1) {
          if (trie[u].count(1) > 0) ans += cnt[trie[u][1]];
          if (trie[u].count(0) > 0) {
            u = trie[u][0];
          } else {
            return ans;
          }
        } else {
          if (trie[u].count(0) > 0) ans += cnt[trie[u][0]];
          if (trie[u].count(1) > 0) {
            u = trie[u][1];
          } else {
            return ans;
          }
        }
      } else {
        if (p_i == 1) {
          if (trie[u].count(1) > 0) {
            u = trie[u][1];
          } else {
            return ans;
          }
        } else {
          if (trie[u].count(0) > 0) {
            u = trie[u][0];
          } else {
            return ans;
          }
        }
      }
    }
    return ans;
  }
} trie;

string IntToString(int n) {
  string ans = "";
  for (int i = 0; i < L; i++) {
    ans += char(C + (n & 1));
    n >>= 1;
  }
  reverse(ans.begin(), ans.end());
  return ans;
}

int main(void) {
  ios::sync_with_stdio(0);
  cin.tie(0);
  trie.Clear();
  int q;
  cin >> q;
  while (q--) {
    int event;
    cin >> event;
    if (event == 1) {
      int p;
      cin >> p;
      trie.AddWord(IntToString(p));
    } else if (event == 2) {
      int p;
      cin >> p;
      trie.DeleteWord(IntToString(p));
    } else {
      int p, l;
      cin >> p >> l;
      cout << trie.Count(IntToString(p), IntToString(l)) << '\n';
    }
  }
  return 0;
}
