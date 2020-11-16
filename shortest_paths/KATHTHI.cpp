#include <deque>
#include <iostream>
#include <string>
#include <vector>
#define FAST_IO ios::sync_with_stdio(0);cin.tie(NULL)
#define x first
#define y second
using namespace std;

typedef pair<int, int> Pair;

const int N = 1e3;
const int INF = 2e6;

int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

string map[N];
int dist[N][N];

void Initialize(int n, int m) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      dist[i][j] = INF;
    }
  }
}

bool IsValid(Pair pos, int n, int m) {
  return (0 <= pos.x && pos.x < n && 0 <= pos.y && pos.y < m);
}

void Solve(void) {
  int n, m;
  cin >> n >> m;
  Initialize(n, m);
  for (int i = 0; i < n; i++) cin >> map[i];

  Pair start = {0, 0};
  dist[0][0] = 0;
  deque<Pair> tour;
  tour.push_back(start);
  
  while (!tour.empty()) {
    Pair from = tour.front();
    tour.pop_front();
    for (int i = 0; i < 4; i++) {
      Pair to = {from.x + dx[i], from.y + dy[i]};
      if (IsValid(to, n, m)) {
        int w = (map[from.x][from.y] != map[to.x][to.y]);
        int new_dist = dist[from.x][from.y] + w;
        if (new_dist < dist[to.x][to.y]) {
          dist[to.x][to.y] = new_dist;
          if (w == 0) {
            tour.push_front(to);
          } else {
            tour.push_back(to);
          }
        }
      }
    }
  }

  cout << dist[n - 1][m - 1] << '\n';
}

int main(void) {
  FAST_IO;
  int t;
  cin >> t;
  while (t--) Solve();
  return 0;
}
