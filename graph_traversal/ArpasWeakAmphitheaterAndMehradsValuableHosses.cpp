#include <iostream>
#include <vector>
using namespace std;

typedef long long Long;

const int INF = 1e9;
const int N = 1e3;

Long weights[N];
Long beauties[N];

vector<int> components[N];
int current_component;

struct Graph {
  vector<int> adj[N];
  int in[N], out[N], timer;  // DFS
  void Clear(int n) {
    for (int i = 0; i < n; i++) {
      adj[i].clear();
      in[i] = out[i] = 0;
    }
    timer = 0;
  }
  void AddEdge(int u, int v) {
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  void DFS(int u) {
    in[u] = ++timer;
    components[current_component].push_back(u);
    for (int v : adj[u]) {
      if (in[v] == 0) DFS(v);
    }
    out[u] = ++timer;
  }
} g;

struct Element {
  Long weight, beauty, nxt;
};
vector<Element> elements;

Long dp[2 * N][N + 1];
bool is_done[2 * N][N + 1];

Long DP(Long pos, Long rem) {
  if (pos == elements.size()) return 0;
  if (is_done[pos][rem]) return dp[pos][rem];
  dp[pos][rem] = DP(pos + 1, rem);
  if (rem - elements[pos].weight >= 0) dp[pos][rem] = max(dp[pos][rem], elements[pos].beauty + DP(pos + elements[pos].nxt, rem - elements[pos].weight));
  is_done[pos][rem] = true;
  return dp[pos][rem];
}

int main(void) {
  ios::sync_with_stdio(0);
  cin.tie(nullptr);
  Long n, m, w;
  cin >> n >> m >> w;
  for (int i = 0; i < n; i++) cin >> weights[i];
  for (int i = 0; i < n; i++) cin >> beauties[i];
  for (int i = 0; i < m; i++) {
    int u, v;
    cin >> u >> v;
    u--;
    v--;
    g.AddEdge(u, v);
  }
  current_component = 0;
  for (int i = 0; i < n; i++) {
    if (g.in[i] == 0) {
      g.DFS(i);
      current_component++;
    }
  }
  for (int i = 0; i < current_component; i++) {
    Long weight_sum = 0;
    Long beauty_sum = 0;
    Long len = components[i].size();
    for (Long j = 0; j < len; j++) {
      int current = components[i][j];
      elements.push_back({weights[current], beauties[current], len + 1 - j});
      weight_sum += weights[current];
      beauty_sum += beauties[current];
    }
    elements.push_back({weight_sum, beauty_sum, 1LL});
  }
  cout << DP(0, w) << '\n';
  return 0;
}
