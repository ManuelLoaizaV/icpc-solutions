//https://open.kattis.com/problems/gameofcards
#include <bits/stdc++.h>
#include <unistd.h>
#define FAST_IO ios::sync_with_stdio(0);cin.tie(NULL)
#define all(v) (v).begin(),(v).end()
using namespace std;

typedef long long Long;
typedef long double Double;
typedef unsigned long long ULong;
typedef pair<Long, Long> Pair;

const int N = 1e3;
const Long INF = 1e18;
const Double EPS = 1e-9;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
Long random(Long a, Long b) { return uniform_int_distribution<Long> (a, b) (rng); }

vector<int> pile;
int k;
bool is_done[N];
int dp[N];

int Mex(const vector<int>& v) {
  int n = v.size();
  vector<bool> marked(n, false);
  for (int x : v) if (x < n) marked[x] = true;
  for (int x = 0; x < n; x++) if (!marked[x]) return x;
  return n;
}

int Grundy(int pos) {
  if (pos == -1) return 0;
  if (is_done[pos]) return dp[pos];
  is_done[pos] = true;
  int remove = min(k, pos);
  vector<int> moves;
  for (int take = 0; take <= remove; take++) {
    int move = (pos - take) - pile[pos - take];
    if (move >= -1) moves.push_back(move);
  }
  vector<int> g;
  for (auto next_pos : moves) g.push_back(Grundy(next_pos));
  return dp[pos] = Mex(g);
}

void Solve(void) {
  int p;
  cin >> p >> k;
  int g = 0;
  for (int i = 0; i < p; i++) {
    pile.clear();
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
      is_done[i] = false;
      int card;
      cin >> card;
      pile.push_back(card);
    }
    g ^= Grundy(n - 1);
  }
  if (g == 0) {
    cout << "Bob will win." << '\n';
  } else {
    cout << "Alice can win." << '\n';
  }
}

int main(void) {
  FAST_IO;
  int t = 1;
  //cin >> t;
  while (t--) Solve();
  return 0;
}

