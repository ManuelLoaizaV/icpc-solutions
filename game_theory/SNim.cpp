//https://open.kattis.com/problems/snim
#include <bits/stdc++.h>
#include <unistd.h>
#define FAST_IO ios::sync_with_stdio(0);cin.tie(NULL)
#define all(v) (v).begin(),(v).end()
using namespace std;

typedef long long Long;
typedef long double Double;
typedef unsigned long long ULong;
typedef pair<Long, Long> Pair;

const int N = 1e4 + 10;

vector<int> s;
bool is_used[N];
int dp[N];

int Mex(const vector<int>& v) {
  int n = v.size();
  vector<bool> marked(n, false);
  for (int x : v) if (x < n) marked[x] = true;
  for (int x = 0; x < n; x++) if (!marked[x]) return x;
  return n;
}

int Grundy(int pos) {
  if (pos == 0) return 0;
  if (is_used[pos]) return dp[pos];
  is_used[pos] = true;
  vector<int> moves;
  for (int move : s) if (pos - move >= 0) moves.push_back(pos - move);
  vector<int> g;
  for (int next_pos : moves) g.push_back(Grundy(next_pos));
  return dp[pos] = Mex(g);
}

void Solve(void) {
  int n;
  cin >> n;
  int g = 0;
  for (int i = 0; i < n; i++) {
    int h;
    cin >> h;
    g ^= Grundy(h);
  }
  if (g == 0) {
    cout << "L";
  } else {
    cout << "W";
  }
}

int main(void) {
  FAST_IO;
  int k;
  cin >> k;
  for (int i = 0; i < k; i++) {
    int move;
    cin >> move;
    s.push_back(move);
  }
  int t;
  cin >> t;
  while (t--) Solve();
  cout << '\n';
  return 0;
}

