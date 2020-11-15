#include <climits>
#include <iostream>
#include <vector>
#define FAST_IO ios::sync_with_stdio(0);cin.tie(NULL)
#define debug(x) cout << #x << " = " << x << '\n'
using namespace std;

const int N = 101;

struct Graph {
  vector<int> rev[N];
  int dp[N];
  bool is_done[N];
  int nodes = 0;

  void Initialize(int new_nodes) {
    for (int i = 0; i <= nodes; i++) {
      rev[i].clear();
      is_done[i] = false;
    }
    nodes = new_nodes;
  }

  void AddEdge(int from, int to) {
    rev[to].push_back(from);
  }

  int DP(int from, const int& source) {
    if (from == source) return 0;
    // Como todos son alcanzables desde source, no coloco otro caso base
    if (is_done[from]) return dp[from];
    dp[from] = INT_MAX;
    for (int to : rev[from]) dp[from] = min(dp[from], -1 + DP(to, source));
    is_done[from] = true;
    return dp[from];
  }

  pair<int, int> GetMax(const int& source) {
    pair<int, int> answer = {INT_MAX, INT_MAX};
    for (int i = 1; i <= nodes; i++) {
      if (DP(i, source) < answer.first) {
        answer.first = DP(i, source);
        answer.second = i;
      }
    }
    answer.first *= (-1);
    return answer;
  }
} graph;

void Solve(int test_case, int n) {
  int source;
  cin >> source;
  graph.Initialize(n);

  int from, to;
  while (cin >> from >> to) {
    if (from == 0 && to == 0) break;
    graph.AddEdge(from, to);
  }
  pair<int, int> answer = graph.GetMax(source);
  printf("Case %d: The longest path from %d has length %d, finishing at %d.\n\n",
      test_case, source, answer.first, answer.second);
}

int main(void) {
  FAST_IO;
  int n;
  int t = 1;
  while (cin >> n) {
    if (n == 0) break;
    Solve(t, n);
    t++;
  }
  return 0;
}
