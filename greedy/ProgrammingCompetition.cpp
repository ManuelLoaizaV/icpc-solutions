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

const string YES = "YES";
const string NO = "NO";

struct Graph {
  int n_vertices;
  int n_edges;
  vector<vector<int>> adj;
  vector<int> subtree_sizes;

  Graph(int n) {
    n_vertices = n;
    n_edges = 0;
    adj.resize(n_vertices);
    subtree_sizes.resize(n_vertices, 0);
  }

  void AddEdge(int u, int v) {
    adj[u].push_back(v);
    n_edges++;
    assert(n_edges < n_vertices);
  }

  int CalculateSubtreeSize(int u) {
    subtree_sizes[u] = 1;
    for (int v : adj[u]) {
      subtree_sizes[u] += CalculateSubtreeSize(v);
    }
    return subtree_sizes[u];
  }

  int DFS(int u, int free_nodes) {
    if (subtree_sizes[u] == 1) {
      return (1 + free_nodes) / 2;
    }

    int n_descendants = 0;
    int max_child = -1;
    for (int v : adj[u]) {
      if (
        max_child == -1 ||
        subtree_sizes[max_child] < subtree_sizes[v]
      ) {
        max_child = v;
      }
      n_descendants += subtree_sizes[v];
    }

    int cnt = 0;
    if (free_nodes > 0) {
      cnt++;
      free_nodes--;
    }

    int remaining_nodes = n_descendants - subtree_sizes[max_child] + free_nodes;
    if (subtree_sizes[max_child] <= remaining_nodes) {
      cnt += (n_descendants + free_nodes) / 2;
    } else {
      cnt += DFS(max_child, remaining_nodes);
    }
    return cnt;
  }
};

void Solve(void) {
  int n;
  cin >> n;
  Graph graph(n);
  for (int i = 1; i < n; i++) {
    int p;
    cin >> p;
    p--;
    graph.AddEdge(p, i);
  }
  graph.CalculateSubtreeSize(0);
  cout << graph.DFS(0, 0) << ENDL;
}

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int t = 1;
  cin >> t;
  while (t--) Solve();
  return 0;
}


