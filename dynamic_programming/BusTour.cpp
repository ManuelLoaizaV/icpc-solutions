//https://open.kattis.com/problems/bustour
#include <iostream>
#include <queue>
#include <utility>
#include <vector>
using namespace std;

typedef long long Long;
typedef pair<int, Long> Pair;

int GetBit(int mask, int bit) {
  return (mask >> bit) & 1LL;
}

void TurnOn(int& mask, int bit) {
  mask = mask | (1 << bit);
}

void TurnOff(int& mask, int bit) {
  mask = mask & (~(1 << bit));
}

const Long INF = 1e18;
const int N = 20;
const int MAX_N = 18;

struct Graph {
  vector<Pair> adj[N];
  Long d[N][N];

  void Clear(int n) {
    for (int i = 0; i < n; i++) {
      adj[i].clear();
    }
  }

  void AddEdge(int u, int v, Long w) {
    adj[u].push_back({v, w});
    adj[v].push_back({u, w});
  }

  void Dijkstra(int s, int n) {
    for (int i = 0; i < n; i++) d[s][i] = INF;
    d[s][s] = 0;
    priority_queue<Pair, vector<Pair>, greater<Pair>> pq;
    pq.push({0, s});
    while (!pq.empty()) {
      Pair path = pq.top();
      int u = path.second;
      pq.pop();
      if (d[s][u] != path.first) continue;
      for (auto e : adj[u]) {
        int v = e.first;
        Long w = e.second;
        if (d[s][u] + w < d[s][v]) {
          d[s][v] = d[s][u] + w;
          pq.push({d[s][v], v});
        }
      }
    }
  }
} g;

int hotels;
bool is_done[1 << MAX_N][N][2];
Long dp[1 << MAX_N][N][2];

void Initialize(int n) {
  int mx = 1 << (n - 2);
  for (int i = 0; i < mx; i++)
    for (int j = 0; j < n; j++)
      for (int k = 0; k < 2; k++)
        is_done[i][j][k] = false;
}

Long DP(int mask, int last, int src) {
  int aux = mask;
  TurnOff(aux, last);
  if (aux == 0) return g.d[(src == 0) ? 0 : (hotels + 1)][last + 1];
  if (is_done[mask][last][src]) return dp[mask][last][src];
  dp[mask][last][src] = INF;
  for (int i = 0; i < hotels; i++) {
    if (GetBit(aux, i)) dp[mask][last][src] = min(dp[mask][last][src], g.d[last + 1][i + 1] + DP(aux, i, src));
  } 
  is_done[mask][last][src] = true;
  return dp[mask][last][src];
}

void Solve(int n, int m) {
  Initialize(n);
  g.Clear(n);
  for (int i = 0; i < m; i++) {
    int u, v;
    Long w;
    cin >> u >> v >> w;
    g.AddEdge(u, v, w);
  }
  for (int i = 0; i < n; i++) g.Dijkstra(i, n);
  Long ans = INF;
  if (n == 3) {
    ans = 2 * (g.d[0][1] + g.d[1][2]);
    cout << ans << '\n';
    return;
  }
  hotels = n - 2;
  int mx = 1 << hotels;
  int cnt = hotels / 2;
  vector<int> req_nodes(cnt);
  vector<int> rem_nodes(hotels - cnt);
  for (int mask = 0; mask < mx; mask++) {
    if (__builtin_popcount(mask) == cnt) {
      int req = mask;
      int rem = (mx - 1) ^ (req);
      int i, j;
      i = j = 0;
      for (int k = 0; k < hotels; k++) {
        if (GetBit(req, k)) req_nodes[i++] = k;
        if (GetBit(rem, k)) rem_nodes[j++] = k;
      }
      Long going_cost, coming_cost;
      going_cost = coming_cost = INF;
      for (i = 0; i < cnt; i++) {
        int u = req_nodes[i];
        for (j = 0; j < hotels - cnt; j++) {
          int v = rem_nodes[j];
          going_cost = min(going_cost, DP(req, u, 0) + g.d[u + 1][v + 1] + DP(rem, v, 1));
          coming_cost = min(coming_cost, DP(req, u, 1) + g.d[u + 1][v + 1] + DP(rem, v, 0));
        }
      }
      Long tmp = going_cost + coming_cost;
      ans = min(ans, tmp);
    }
  }
  cout << ans << '\n';
}

int main(void) {
  ios::sync_with_stdio(0);
  cin.tie(nullptr);
  int t = 0;
  int n, m;
  while (cin >> n >> m) {
    t++;
    cout << "Case " << t << ": ";
    Solve(n, m);
  }
  return 0;
}
