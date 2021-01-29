//https://codeforces.com/problemset/problem/770/C
#include <iostream>
#include <vector>
using namespace std;

const int N = 1e5;

bool has_cycle = false;
vector<int> answer;

struct Graph {
  vector<int> adj[N];
  int in[N], out[N], timer;

  void Clear(int n) {
    for (int i = 0; i < n; i++) {
      in[i] = out[i] = 0;
    }
    timer = 0;
  }

  void AddEdge(int u, int v) {
    adj[u].push_back(v);
  }

  void DFS(int u) {
    in[u] = ++timer;
    for (int v : adj[u]) {
      if (in[v] == 0) {  // tree edge
        DFS(v);
      } else if (out[v] == 0) {  // back edge
        has_cycle = true;
      }
    }
    out[u] = ++timer;
    answer.push_back(u);
  }
} graph;

int main(void) {
  ios::sync_with_stdio(0);
  cin.tie(nullptr);
  int n, k;
  cin >> n >> k;
  vector<int> main_courses(k);
  for (int i = 0; i < k; i++) {
    cin >> main_courses[i];
    main_courses[i]--;
  }
  graph.Clear(n);
  for (int i = 0; i < n; i++) {
    int t;
    cin >> t;
    while (t--) {
      int previous;
      cin >> previous;
      previous--;
      graph.AddEdge(i, previous);
    }
  }
  for (int course : main_courses) {
    if (graph.in[course] == 0) graph.DFS(course);
  }
  if (has_cycle) {
    cout << -1 << '\n';
  } else {
    int len = answer.size();
    cout << len << '\n';
    for (int i = 0; i < len; i++) {
      if (i > 0) cout << " ";
      cout << answer[i] + 1;
    }
    cout << '\n';
  }
  return 0;
}
