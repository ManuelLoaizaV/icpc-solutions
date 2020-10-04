#include <bits/stdc++.h>
#define FAST_IO ios::sync_with_stdio(0);cin.tie(NULL)
using namespace std;

const int N = 1e5;
bool done[N + 1];
int dp[N + 1];
vector<int> take;

int BinPow(int a, int b) {
  if (b == 0) return 1;
  int pot = BinPow(a, b / 2);
  int ans = pot * pot;
  if (b & 1) ans *= a;
  return ans;
}

int Mex(vector<int>& v) {
  int n = v.size();
  vector<bool> marked(n, false);
  for (int i : v) if (i < n) marked[i] = true;
  for (int i = 0; i < n; i++) if (!marked[i]) return i;
  return n;
}

int Grundy(int pos) {
  if (pos == 0) return 0;
  if (done[pos]) return dp[pos];
  vector<int> moves;
  for (int delta : take) {
    int next_pos = pos - delta;
    if (next_pos >= 0) moves.push_back(next_pos);
  }
  vector<int> g;
  for (int next_pos : moves) g.push_back(Grundy(next_pos));
  done[pos] = true;
  return dp[pos] = Mex(g);
}

void Solve() {
  int n;
  cin >> n;
  vector<int> a;
  a.resize(n);
  for (int i = 0; i < n; i++) cin >> a[i];
  int ans = 0;
  for (int i = 0; i < n; i++) ans ^= Grundy(a[i]);
  if (ans) cout << "Little Chef" << '\n';
  else cout << "Head Chef" << '\n';
}

void Precalculate() {
  for (int i = 1; i <= 6; i++) take.push_back(BinPow(i, i));
  Grundy(N);
}

int main() {
  FAST_IO;
  Precalculate();
  int t;
  cin >> t;
  while (t--) Solve();
  return 0;
}
