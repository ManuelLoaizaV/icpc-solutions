//https://codeforces.com/problemset/problem/137/D
#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
using namespace std;

const int N = 505;
const int INF = 1e4;

// DP(i, k): minimo costo de convertir la cadena s[0 .. i] en una concatenacion
// de <= k cadenas palindromas
bool done[N][N];
int dp[N][N], c[N][N];

int DP(int i, int k) {
  if (i < 0) {
    if (k >= 0) return 0;
    return INF;
  }
  if (k <= 0) return INF;
  if (done[i][k]) return dp[i][k];
  dp[i][k] = INF;
  for (int j = 0; j <= i; j++) {
    dp[i][k] = min(dp[i][k], c[j][i] + DP(j - 1, k - 1));
  }
  done[i][k] = true;
  return dp[i][k];
}

vector<pair<int, int>> pairs;

void Reconstruct(int i, int k) {
  if (i < 0) return;
  for (int j = 0; j <= i; j++) {
    if (DP(i, k) == c[j][i] + DP(j - 1, k - 1)) {
      pairs.emplace_back(j, i);
      Reconstruct(j - 1, k - 1);
      return;
    }
  }
}

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  string s;
  cin >> s;
  int k;
  cin >> k;
  int n = s.size();
  for (int j = 0; j < n; j++) {
    for (int i = 0; i <= j; i++) {
      c[i][j] = 0;
      int len = j - i + 1;
      int half = len / 2;
      for (int l = 0; l < half; l++) if (s[i + l] != s[j - l]) c[i][j]++;
    }
  }
  cout << DP(n - 1, k) << '\n';
  Reconstruct(n - 1, k);
  reverse(pairs.begin(), pairs.end());
  int m = (int) pairs.size();
  for (int i = 0; i < m; i++) {
    if (i > 0) cout << "+";
    int left = pairs[i].first;
    int right = pairs[i].second;
    int len = right - left + 1;
    int half = len / 2;
    for (int l = 0; l < len; l++) {
      if (l < half) {
        if (s[left + l] != s[right - l]) {
          cout << s[right - l];
        } else {
          cout << s[left + l];
        }
      } else {
        cout << s[left + l];
      }
    }
  }
  cout << '\n';
  return 0;
}
