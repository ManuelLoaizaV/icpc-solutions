#include <bits/stdc++.h>
#define FAST_IO ios::sync_with_stdio(0);cin.tie(NULL)
#define debug(x) cout << #x << " = " << x << '\n'
using namespace std;

const int N = 1e5;
bool done[N + 1];
int dp[N + 1];
int mn[N + 1];

int Mex(vector<int>& v) {
  int n = v.size();
  vector<bool> marked(n, false);
  for (int x : v) if (x < n) marked[x] = true;
  for (int i = 0; i < n; i++) if (!marked[i]) return i;
  return n;
}

int Grundy(int pos) {
  //debug(pos);
  if (pos == 0) return 0;
  if (done[pos]) return dp[pos];
  done[pos] = true;
  int cnt = 2;
  vector<int> g;
  while (true) {
    int temp = pos - cnt * (cnt - 1) / 2;
    if (temp <= 0) break;
    if (temp % cnt == 0) {
      int ini = temp / cnt;
      int next_pos = 0;
      for (int i = 0; i < cnt; i++) next_pos ^= Grundy(ini + i);
      g.push_back(next_pos);
      //debug(temp);
      //debug(ini);
      //debug(next_pos);
      //debug(cnt);
      if (next_pos == 0) mn[pos] = min(mn[pos], cnt); 
    }
    cnt++;
  }
  return dp[pos] = Mex(g);
}

int main(void) {
  FAST_IO;
  int n;
  cin >> n;
  for (int i = 0; i <= n; i++) mn[i] = n;
  if (Grundy(n)) {
    cout << mn[n] << '\n';
  } else {
    cout << -1 << '\n';
  }
  return 0;
}
