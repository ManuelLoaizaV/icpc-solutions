#include <climits>
#include <iostream>
#include <queue>
#include <vector>
#define FAST_IO ios::sync_with_stdio(0);cin.tie(NULL)
#define x first
#define y second
using namespace std;

typedef pair<int, int> Pair;

bool IsValid(Pair pos, int n, int m) {
  return (0 <= pos.x && pos.x < n && 0 <= pos.y && pos.y < m);
}

void Solve(void) {
  int n, m;
  cin >> n >> m;
  vector<vector<int>> a(n, vector<int> (m, 0));

  int maximum = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      cin >> a[i][j];
      maximum = max(maximum, a[i][j]);
    }
  }

  vector<vector<int>> dist(n, vector<int> (m, INT_MAX));
  vector<vector<bool>> is_done(n, vector<bool> (m, false));
  
  queue<Pair> tour;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (a[i][j] == maximum) {
        dist[i][j] = 0;
        is_done[i][j] = true;
        tour.push({i, j});
      }
    }
  }

  while (!tour.empty()) {
    Pair from = tour.front();
    tour.pop();
    for (int i = -1; i < 2; i++) {
      for (int j = -1; j < 2; j++) {
        if (i == 0 && j == 0) continue;
        Pair to = {from.x + i, from.y + j};
        if (IsValid(to, n, m) && !is_done[to.x][to.y]) {
          dist[to.x][to.y] = dist[from.x][from.y] + 1;
          is_done[to.x][to.y] = true;
          tour.push(to);
        }
      }
    } 
  }

  int ans = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      ans = max(ans, dist[i][j]);
    }
  }
  cout << ans << '\n';
}

int main(void) {
  FAST_IO;
  int t;
  cin >> t;
  while (t--) Solve();
  return 0;
}
