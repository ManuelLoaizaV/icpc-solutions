//https://onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=2051
#include <bits/stdc++.h>

using namespace std;

const int N = 101;
const int dx[4] = {-1, 1, 0, 0};
const int dy[4] = {0, 0, -1, 1};

int g[N][N], cnt[N], n;
bool used[N][N];

bool IsValid(int x, int y) {
  return 0 <= x && x < n && 0 <= y && y < n;
}

void DFS(int x, int y) {
  used[x][y] = true;
  cnt[g[x][y]]++;
  for (int i = 0; i < 4; i++) {
    int new_x = x + dx[i];
    int new_y = y + dy[i];
    if (IsValid(new_x, new_y) && !used[new_x][new_y] && g[x][y] == g[new_x][new_y]) {
      DFS(new_x, new_y);
    }
  }
}

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  while (cin >> n) {
    if (n == 0) break;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        g[i][j] = 0;
        used[i][j] = false;
      }
      cnt[i] = 0;
    }
    string line;
    getline(cin, line);
    for (int i = 1; i < n; i++) {
      getline(cin, line);
      stringstream ss(line);
      int x, y;
      while (ss >> x >> y) {
        x--; y--;
        g[x][y] = i;
      }
    }
    bool ok = true;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        if (!used[i][j]) {
          if (cnt[g[i][j]] == 0) {
            DFS(i, j);
          } else {
            ok = false;
            break;
          }
        }
      }
      if (!ok) break;
    }
    if (ok) {
      for (int i = 0; i < n; i++) {
        if (cnt[i] == n) continue;
        ok = false;
        break;
      }
    }
    cout << (ok ? "good" : "wrong") << '\n';
  }
  return 0;
}