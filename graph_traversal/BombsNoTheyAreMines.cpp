//https://onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=1594
#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> Pair;

const int INF = 1e9;
const int N = 1e3 + 5;

bool bomb[N][N];
int r, c;
int d[N][N];
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

bool IsValid(Pair p) {
  return 0 <= p.first && p.first < r && 0 <= p.second && p.second < c;
}

void BFS(Pair s) {
  d[s.first][s.second] = 0;
  queue<Pair> q;
  q.push(s);
  while (!q.empty()) {
    Pair u = q.front();
    q.pop();
    for (int i = 0; i < 4; i++) {
      Pair nxt = {u.first + dx[i], u.second + dy[i]};
      if (IsValid(nxt) && d[u.first][u.second] + 1 < d[nxt.first][nxt.second] && !bomb[nxt.first][nxt.second]) {
        d[nxt.first][nxt.second] = d[u.first][u.second] + 1;
        q.push(nxt);
      }
    }
  }
}

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  while (cin >> r >> c) {
    if (r == 0 && c == 0) break;
    for (int i = 0; i < r; i++) {
      for (int j = 0; j < c; j++) {
        d[i][j] = INF;
        bomb[i][j] = false;
      }
    }
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
      int x, m;
      cin >> x >> m;
      for (int j = 0; j < m; j++) {
        int y;
        cin >> y;
        bomb[x][y] = true;
      }
    }
    Pair from, to;
    cin >> from.first >> from.second;
    BFS(from);
    cin >> to.first >> to.second;
    cout << d[to.first][to.second] << '\n';
  }
  return 0;
}