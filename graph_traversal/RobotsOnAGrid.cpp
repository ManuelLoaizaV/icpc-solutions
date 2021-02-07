//https://www.spoj.com/problems/ROBOTGRI/en/
#include <bits/stdc++.h>
using namespace std;

typedef long long Long;

const int N = 1e3;
const Long MOD = (1LL << 31) - 1LL;

int n;
string s[N];

Long dp[N][N];
bool is_done[N][N];
bool is_possible = false;

Long Add(Long a, Long b) { return (a + b) % MOD; }

bool IsValid(int i, int j) {
  return 0 <= i && i < n && 0 <= j && j < n && s[i][j] != '#';
}

Long DP(int i, int j) {
  if (!IsValid(i, j)) return 0;
  if (i == n - 1 && j == n - 1) {
    is_possible = true;
    return 1LL;
  }
  if (is_done[i][j]) return dp[i][j];
  dp[i][j] = Add(DP(i + 1, j), DP(i, j + 1));
  is_done[i][j] = true;
  return dp[i][j];
}

bool is_used[N][N];
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

void DFS(int i, int j) {
  is_used[i][j] = true;
  for (int k = 0; k < 4; k++) {
    int new_x = i + dx[k];
    int new_y = j + dy[k];
    if (IsValid(new_x, new_y) && !is_used[new_x][new_y]) DFS(new_x, new_y);
  }
}

int main(void) {
  ios::sync_with_stdio(0);
  cin.tie(nullptr);
  cin >> n;
  for (int i = 0; i < n; i++) cin >> s[i];
  Long answer = DP(0, 0);
  if (is_possible) {
    cout << answer << '\n';
  } else {
    DFS(0, 0);
    if (is_used[n - 1][n - 1]) {
      cout << "THE GAME IS A LIE\n";
    } else {
      cout << "INCONCEIVABLE\n";
    }
  }
  return 0;
}
