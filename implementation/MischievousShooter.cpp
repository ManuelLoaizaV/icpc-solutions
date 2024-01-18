// https://codeforces.com/contest/1921/problem/G
#include <bits/stdc++.h>

#ifndef ONLINE_JUDGE
#define debug(x) cerr << "[" << #x << "]: " << x << endl
#else
#define debug(x) 69
#endif

using namespace std;

typedef long long Long;
typedef long double Double;
typedef pair<Long, Long> Pair;

const int N = 1e6;
const Long MOD = 998244353LL;
const Long INF = 1e18;
const Double PI = acos(-1);
const Double EPS = 1e-9;

const char A = 'a';
const char ZERO = '0';
const char ENDL = '\n';
const char TARGET = '#';

const string YES = "YES";
const string NO = "NO";

int MaxRD(const vector<vector<char>>& field, int k) {
  int n = (int)field.size();
  int m = (int)field[0].size();
  int mx = 0;
  vector<vector<int>> u_cnt(n, vector<int>(m, 0));
  vector<vector<int>> ur_cnt(n, vector<int>(m, 0));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (i > 0) {
        u_cnt[i][j] = u_cnt[i - 1][j];
        if (j < m - 1) ur_cnt[i][j] = ur_cnt[i - 1][j + 1];
      }
      if (field[i][j] == TARGET) {
        u_cnt[i][j]++;
        ur_cnt[i][j]++;
      }
    }
  }
  int tmp = 0;
  for (int i = 0; i <= min(n - 1, k); i++) {
    for (int j = min(k - i, m - 1); j >= 0; j--) {
      if (field[i][j] == TARGET) tmp++;
    }
  }
  int row = 0;
  int col = 0;
  while (row < n) {
    mx = max(mx, tmp);
    if (row & 1) {
      if (col == 0) {
        for (int j = min(k, m - 1); j >= 0; j--) {
          if (field[row][j] == TARGET) tmp--;
        }
        int next_row = min(row + k + 1, n - 1);
        int next_col = col + (k + 1) - (next_row - row);
        if (next_col < m) tmp += ur_cnt[next_row][next_col];
        if (col + k + 1 < m) tmp -= ur_cnt[row][col + k + 1];
        row++;
      } else {
        int last_row = min(row + k, n - 1);
        tmp += u_cnt[last_row][col - 1];
        if (row > 0) tmp -= u_cnt[row - 1][col - 1];
        int prev_col = (col - 1) + (k + 1) - (last_row - row);
        if (prev_col < m) tmp -= ur_cnt[last_row][prev_col];
        if (row - 1 >= 0 && col + k + 1 < m) tmp += ur_cnt[row - 1][col + k + 1];
        col--;
      }
    } else {
      if (col == m - 1) {
        if (row + k + 1 < n && field[row + k + 1][col] == TARGET) tmp++;
        if (field[row][col] == TARGET) tmp--;
        row++;
      } else {
        int last_row = min(row + k, n - 1);
        tmp -= u_cnt[last_row][col];
        if (row > 0) tmp += u_cnt[row - 1][col];
        int next_col = col + (k + 1) - (last_row - row);
        if (next_col < m) tmp += ur_cnt[last_row][next_col];
        if (row - 1 >= 0 && col + k + 2 < m) tmp -= ur_cnt[row - 1][col + k + 2];
        col++;
      }
    }
  }
  return mx;
}

void RotateCW(vector<vector<char>>& field) {
  int n = (int)field.size();
  int m = (int)field[0].size();
  vector<vector<char>> rotated_field(m, vector<char>(n));
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      rotated_field[j][n - 1 - i] = field[i][j];
  field = rotated_field;
}

void Solve(void) {
  int n, m, k;
  cin >> n >> m >> k;
  vector<vector<char>> field(n, vector<char>(m));
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      cin >> field[i][j];
  int mx = 0;
  for (int i = 0; i < 4; i++) {
    mx = max(mx, MaxRD(field, k));
    if (i < 3) RotateCW(field);
  } 
  cout << mx << ENDL;
}

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int t = 1;
  cin >> t;
  while (t--) Solve();
  return 0;
}