#include <algorithm>
#include <iostream>
#include <queue>
#include <unordered_set>
#include <vector>
#define FAST_IO ios::sync_with_stdio(0);cin.tie(NULL)
using namespace std;

const int N = 3e3 + 1;
const int INF = 1e5;

typedef long long Long;
typedef pair<int, int> Pair;

unordered_set<Long> is_cursed;
//bool adj[N][N];
vector<int> adj[N];
int dist[N][N];
int parent[N][N];

Long GetHash(Long a, Long b, Long c) {
  return (a * N * N + b * N + c);
}

int main(void) {
  FAST_IO;
  int n, m, k;
  cin >> n >> m >> k;
  while (m--) {
    int from, to;
    cin >> from >> to;
    //adj[from][to] = adj[to][from] = true;
    adj[from].push_back(to);
    adj[to].push_back(from);
  }

  while (k--) {
    Long a, b, c;
    cin >> a >> b >> c;
    is_cursed.insert(GetHash(a, b, c));
  }

  for (int i = 0; i <= n; i++)
    for (int j = 0; j <= n; j++)
      dist[i][j] = INF;

  dist[0][1] = 0;
  queue<Pair> tour;
  tour.push({0, 1});

  while (!tour.empty()) {
    Pair from = tour.front();
    int prev = from.first;
    int cur = from.second;
    tour.pop();

    for (int to : adj[cur]) {
      Long triplet = GetHash(prev, cur, to);
      if (is_cursed.count(triplet)) continue;
      int new_dist = dist[prev][cur] + 1;

      if (new_dist < dist[cur][to]) {
        dist[cur][to] = new_dist;
        parent[cur][to] = prev;
        tour.push({cur, to});
      }
    }
  }

  Pair current = {-1, -1};
  int minimum = INF;
  for (int from = 0; from <= n; from++) {
    if (dist[from][n] < minimum) {
      current = {from, n};
      minimum = dist[from][n];
    }
  }
  if (current.first == -1) {
    cout << -1 << '\n';
  } else {
    vector<int> answer;
    while (current.first != 0) {
      answer.push_back(current.second);
      Pair prev = {parent[current.first][current.second], current.first};
      current = prev;
    }
    answer.push_back(current.second);
    reverse(answer.begin(), answer.end());

    int len = answer.size();
    cout << len - 1 << '\n';
    for (int i = 0; i < len; i++) {
      if (i > 0) cout << " ";
      cout << answer[i];
    }
    cout << '\n';
  }
  return 0;
}
