//https://www.spoj.com/problems/SUBXOR/
#include <bits/stdc++.h>
using namespace std;

typedef long long Long;

const int N = 3e6 + 1;  // total de caracteres + 1
const int ALPHABET = 2;
const int C = (int)'0';
const int L = 20;

struct Trie {
  map<int, int> trie[N];
  Long cnt[N];
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
  Long Count(const string& s, const string& k) {
    int n = s.size();
    int u = 0;
    Long ans = 0;
    for (int i = 0; i < n; i++) {
      int c = s[i] - C;
      int d = k[i] - C;
      if (d == 1) {
        if (c == 1) {
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
        if (c == 1) {
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
  if (n == 0) {
    for (int i = 0; i < L; i++) ans += '0';
  } else {
    for (int i = 0; i < L; i++) {
      if (n & 1) {
        ans += '1';
      } else {
        ans += '0';
      }
      n >>= 1;
    }
    reverse(ans.begin(), ans.end());
  }
  return ans;
}

void Solve(void) {
  trie.Clear();
  int n, k;
  cin >> n >> k;
  vector<int> a(n);
  for (int i = 0; i < n; i++) cin >> a[i];
  int pref = 0;
  Long ans = 0;
  trie.AddWord(IntToString(pref));
  string string_k = IntToString(k);
  for (int i = 0; i < n; i++) {
    pref ^= a[i];
    string current = IntToString(pref);
    ans += trie.Count(current, string_k);
    trie.AddWord(current);
  }
  cout << ans << '\n';
}

int main(void) {
  ios::sync_with_stdio(0);
  cin.tie(0);
  int t;
  cin >> t;
  while (t--) Solve();
  return 0;
}
