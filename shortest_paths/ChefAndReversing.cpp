#include <iostream>
#include <deque>
#include <vector>
#define FAST_IO ios::sync_with_stdio(0);cin.tie(NULL)
using namespace std;

typedef pair<int, int> Pair;

const int N = 1e5 + 1;
const int INF = 1e6;

vector<Pair> adj[N];
int dist[N];
bool is_done[N];

int BFS_01(int nodes) {
  for (int i = 0; i <= nodes; i++) {
    dist[i] = INF;
    is_done[i] = false;
  }

  dist[1] = 0;
  is_done[1] = true;
  deque<int> tour;
  tour.push_back(1);
  
  while (!tour.empty()) {
    int from = tour.front();
    tour.pop_front();
    for (Pair edge : adj[from]) {
      int to = edge.first;
      int w = edge.second;
      if (dist[from] + w < dist[to]) {
        dist[to] = dist[from] + w;
        is_done[to] = true;
        if (w == 0) {
          tour.push_front(to);
        } else {
          tour.push_back(to);
        }
      }
    }
  }

  if (is_done[nodes]) return dist[nodes];
  return -1;
}

int main(void) {
  FAST_IO;
  int n, m;
  cin >> n >> m;
  while (m--) {
    int from, to;
    cin >> from >> to;
    adj[from].push_back({to, 0});
    adj[to].push_back({from, 1});
  }
  cout << BFS_01(n) << '\n';
  return 0;
}
