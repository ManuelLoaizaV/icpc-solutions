//https://open.kattis.com/problems/bachetsgame
#include <bits/stdc++.h>
#include <unistd.h>
#define FAST_IO ios::sync_with_stdio(0);cin.tie(NULL)
#define all(v) (v).begin(),(v).end()
using namespace std;

typedef int Long;
typedef long double Double;
typedef unsigned long long ULong;
typedef pair<Long, Long> Pair;

const int N = 1e6;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
Long random(Long a, Long b) { return uniform_int_distribution<Long> (a, b) (rng); }

vector<Long> moves;
bool is_done[N + 1];
bool dp[N + 1];

bool IsWinning(Long pos) {
  if (pos == 0) return false;
  if (is_done[pos]) return dp[pos];
  is_done[pos] = true;
  for (Long move : moves) {
    Long next_pos = pos - move;
    if (next_pos >= 0 && !IsWinning(next_pos)) return dp[pos] = true;
  }
  return dp[pos] = false;
}

void Solve(Long n, Long m) {
  for (int i = 0; i <= n; i++) is_done[i] = false;
  moves.clear();
  for (int i = 0; i < m; i++) {
    Long move;
    cin >> move;
    moves.push_back(move);
  }
  if (IsWinning(n)) {
    cout << "Stan wins" << '\n';
  } else {
    cout << "Ollie wins" << '\n';
  }
}

int main(void) {
  FAST_IO;
  Long n, m;
  while (cin >> n >> m) Solve(n, m);
  return 0;
}

