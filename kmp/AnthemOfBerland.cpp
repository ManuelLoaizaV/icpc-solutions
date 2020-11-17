#include <iostream>
#include <string>
#include <vector>
#define FAST_IO ios::sync_with_stdio(0);cin.tie(NULL)
using namespace std;

const int ALPHABET = 26;

string s, t;
vector<int> pi;
vector<vector<int>> go;
vector<vector<int>> dp;
vector<vector<bool>> is_done;

void CalculatePi(void) {
  int n = s.size();
  pi.resize(n, 0);
  for (int i = 1; i < n; i++) {
    int j = pi[i - 1];
    while (j > 0 && s[i] != s[j]) j = pi[j - 1];
    if (s[i] == s[j]) j++;
    pi[i] = j;
  }
}

void CalculateAutomata(void) {
  int n = s.size();
  go.resize(n + 1, vector<int> (ALPHABET, 0));
  go[0][s[0] - 'a'] = 1;
  for (int pos = 1; pos <= n; pos++) {
    for (int chr = 0; chr < ALPHABET; chr++) {
      if (pos < n && chr == (s[pos] - 'a')) {
        go[pos][chr] = pos + 1;
      } else {
        go[pos][chr] = go[pi[pos - 1]][chr];
      }
    }
  }
}

int DP(int i, int node) {
  if (i == t.size()) return (node == s.size());
  if (is_done[i][node]) return dp[i][node];
  dp[i][node] = (node == s.size());
  if (t[i] == '?') {
    int next_dp = 0;
    for (int chr = 0; chr < ALPHABET; chr++)
      next_dp = max(next_dp, DP(i + 1, go[node][chr]));
    dp[i][node] += next_dp;
  } else {
    dp[i][node] += DP(i + 1, go[node][t[i] - 'a']);
  }
  is_done[i][node] = true;
  return dp[i][node];
}

int main(void) {
  FAST_IO;
  cin >> t >> s;
  CalculatePi();
  CalculateAutomata();

  dp.resize(t.size(), vector<int> (s.size() + 1, 0));
  is_done.resize(t.size(), vector<bool> (s.size() + 1, false));
  cout << DP(0, 0) << '\n';
  return 0;
}
