#include <bits/stdc++.h>
#define FAST_IO ios::sync_with_stdio(0);cin.tie(NULL)
using namespace std;

typedef pair<string, string> Pair;

map<string, bool> dic;
map<string, bool> done;
map<string, int> dp;

int Mex(vector<int>& v) {
  int n = v.size();
  vector<bool> marked(n, false);
  for (int x : v) if (x < n) marked[x] = true;
  for (int i = 0; i < n; i++) if (!marked[i]) return i;
  return n;
}

int Grundy(string pos) {
  int sz = pos.size();
  if (sz == 0) return 0;
  if (done[pos]) return dp[pos];
  done[pos] = true;
  vector<Pair> moves;
  for (int i = 0; i < sz; i++) {
    for (int j = i; j < sz; j++) {
      string mid = pos.substr(i, j - i + 1);
      if (dic.count(mid) > 0) {
        Pair next_pos = {"", ""};
        if (i > 0) next_pos.first = pos.substr(0, i);
        if (j < sz - 1) next_pos.second = pos.substr(j + 1, sz - 1 - j);
        moves.push_back(next_pos);
      }
    }
  }
  vector<int> g;
  for (Pair move : moves) g.push_back(Grundy(move.first) ^ Grundy(move.second));
  return dp[pos] = Mex(g);
}

void Initialize() {
  dic.clear();
  done.clear();
  dp.clear();
}

void Solve() {
  Initialize();
  string s, aux;
  cin >> s;
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> aux;
    dic[aux] = true;
  }
  if (Grundy(s)) cout << "Teddy" << '\n';
  else cout << "Tracy" << '\n';
}

int main() {
  FAST_IO;
  int t;
  cin >> t;
  while (t--) Solve();
  return 0;
}
