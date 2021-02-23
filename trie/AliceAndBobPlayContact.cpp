// UVA - Alice and Bob play Contact
#include <bits/stdc++.h>
using namespace std;

typedef long long Long;

const int C = (int)'a';
const int N = 1e6 + 1;  // total de caracteres + 1
const int ALPHABET = 26;

struct Trie {
  int trie[N][ALPHABET];
  int cnt[N];
  int nodes = 1;
  void Clear(void) {
    for (int i = 0; i < nodes; i++) {
      for (int j = 0; j < ALPHABET; j++) trie[i][j] = 0;
      cnt[i] = 0;
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
  }
  int Query(const string& s) {
    int n = s.size();
    int u = 0;
    int ans = 0;
    int mx = n;
    for (int i = 0; i < n; i++) {
      int c = s[i] - C;
      if (trie[u][c] == 0) return ans;
      u = trie[u][c];
      mx = min(mx, cnt[u]);
      ans++;
      mx--;
      if (mx == 0) return ans;
    }
    return ans;
  }
} bob;

void Solve(int n, int m) {
  bob.Clear();
  vector<string> a(n);
  for (int i = 0; i < n; i++) cin >> a[i];
  for (int i = 0; i < m; i++) {
    string b;
    cin >> b;
    bob.AddWord(b);
  }
  Long ans = 0;
  for (int i = 0; i < n; i++) {
    ans += (Long)bob.Query(a[i]);
  }
  cout << ans << '\n';
}

int main(void) {
  ios::sync_with_stdio(0);
  cin.tie(0);
  int n, m;
  while (cin >> n >> m) Solve(n, m);
  return 0;
}
