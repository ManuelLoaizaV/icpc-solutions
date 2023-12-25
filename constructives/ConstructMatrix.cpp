// https://codeforces.com/contest/1917/problem/E
#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl

using namespace std;

typedef long long Long;

const int N = 1000;
const Long INF = 1e18;
const char ENDL = '\n';
const string YES = "Yes";
const string NO = "No";

int grid[N][N];

void Print(int n) {
  cout << YES << ENDL;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (j > 0) cout << " ";
      cout << grid[i][j];
    }
    cout << ENDL;
  }
}

void Solve(void) {
  int n, k;
  cin >> n >> k;

  // Reset the matrix
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      grid[i][j] = 0;
    }
  }

  if (k == 0) {
    Print(n);
    return;
  }

  if (k & 1) {
    cout << NO << ENDL;
    return;
  }

  if (k == 2 || k == (n * n - 2)) {
    if (n == 2) {
      grid[0][0] = grid[0][1] = 1;
      Print(n);
    } else {
      cout << NO << ENDL;
    }
    return;
  }

  if (k % 4 == 0) {
    for (int i = 0; i < n; i += 2) {
      if (k == 0) break;
      for (int j = 0; j < n; j += 2) {
        if (k == 0) break;
        grid[i][j] = 1;
        grid[i][j + 1] = 1;
        grid[i + 1][j] = 1;
        grid[i + 1][j + 1] = 1;
        k -= 4;
      }
    }
    Print(n);
    return;
  }

  assert(k %  4 == 2);
  grid[0][0] = 1;
  grid[0][1] = 1;
  grid[1][0] = 1;
  grid[1][2] = 1;
  grid[2][1] = 1;
  grid[2][2] = 1;
  k -= 6;

  for (int i = 0; i < n; i += 2) {
    if (k == 0) break;
    for (int j = 0; j < n; j += 2) {
      if (k == 0) break;
      if (i < 4 && j < 4) continue;
      grid[i][j] = 1;
      grid[i][j + 1] = 1;
      grid[i + 1][j] = 1;
      grid[i + 1][j + 1] = 1;
      k -= 4;
    }
  }

  if (k > 0) {
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
        grid[i][j] ^= 1;
      }
    }
  }

  Print(n);
}

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int t = 1;
  cin >> t;
  while (t--) Solve();
  return 0;
}