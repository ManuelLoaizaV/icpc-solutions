//https://codeforces.com/problemset/problem/827/A
#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << '\n'
using namespace std;

const int MAX_N = 2e6; 

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n;
  vector<string> s(n);
  vector<vector<int>> pos(n);
  vector<pair<int, int>> len_pos;
  for (int i = 0; i < n; i++) {
    cin >> s[i];
    int cnt;
    cin >> cnt;
    for (int j = 0; j < cnt; j++) {
      int x;
      cin >> x;
      x--;
      pos[i].push_back(x);
    }
    len_pos.push_back({(int) s[i].size(), i});
  }
  sort(len_pos.begin(), len_pos.end());
  reverse(len_pos.begin(), len_pos.end());
  vector<char> ans(MAX_N, '$');
  set<int> rem;
  for (int i = 0; i < MAX_N; i++) rem.insert(i);
  for (int i = 0; i < n; i++) {
    int id = len_pos[i].second;
    int len = len_pos[i].first;
    //debug(id);
    //debug(len);
    for (int p : pos[id]) {
      auto it = rem.lower_bound(p);
      if (it == rem.end()) continue;
      int ini = *it;
      //debug(p);
      //debug(ini);
      if (ini >= p + len) continue;
      for (int j = ini; j < p + len; j++) {
        if (ans[j] != '$') break;
        rem.erase(j);
        ans[j] = s[id][j - p];
      }
    }
  }
  int last = -1;
  for (int i = 0; i < MAX_N; i++) if (ans[i] != '$') last = i;
  for (int i = 0; i <= last; i++) cout << (ans[i] == '$' ? 'a' : ans[i]);
  cout << '\n';
  return 0;
}
