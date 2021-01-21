//https://www.spoj.com/problems/ADFRUITS/
#include <iostream>
#include <string>
using namespace std;

typedef long long Long;

const int N = 100;

string s, t;
int n, m;
bool is_done[N + 1][N + 1];
int dp[N + 1][N + 1];

Long DP(int i, int j) {
  if (i == n && j == m) return 0;
  if (is_done[i][j]) return dp[i][j];
  if (i == n) {
    dp[i][j] = 1 + DP(i, j + 1);
  } else {
    if (j == m) {
      dp[i][j] = 1 + DP(i + 1, j);
    } else {
      if (s[i] == t[j]) {
        dp[i][j] = 1 + DP(i + 1, j + 1);
      } else {
        dp[i][j] = 1 + min(DP(i + 1, j), DP(i, j + 1));
      }
    }
  }
  is_done[i][j] = true;
  return dp[i][j];
}

void Reconstruct(int i, int j) {
  if (i == n && j == m) return;
  if (i == n) {
    cout << t[j];
    Reconstruct(i, j + 1);
  } else {
    if (j == m) {
      cout << s[i];
      Reconstruct(i + 1, j);
    } else {
      if (s[i] == t[j]) {
        cout << s[i];
        Reconstruct(i + 1, j + 1);
      } else {
        if (DP(i, j) == 1 + DP(i + 1, j)) {
          cout << s[i];
          Reconstruct(i + 1, j);
        } else {
          cout << t[j];
          Reconstruct(i, j + 1);
        }
      }
    }
  }
}

void Solve(void) {
  n = s.size();
  m = t.size();
  for (int i = 0; i <= n; i++)
    for (int j = 0; j <= m; j++)
      is_done[i][j] = false;
  Reconstruct(0, 0);
  cout << '\n';
}

int main(void) {
  ios::sync_with_stdio(0);
  cin.tie(nullptr);
  while (cin >> s >> t) Solve();
  return 0;
}
