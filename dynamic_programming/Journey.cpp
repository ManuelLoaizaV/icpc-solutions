#include <iostream>
#include <utility>
#include <vector>
#define FAST_IO ios::sync_with_stdio(0);cin.tie(nullptr)
using namespace std;

typedef long long Long;
typedef pair<int, Long> Pair;

const Long INF = 1e13;
const int N = 5e3;

vector<Pair> adj[N];

int n, m;
Long T;

bool is_done[N][N];
Long dp[N][N];

Long DP(int u, int len) {
  if (len == 0) {
    if (u == n - 1) return 0;
    return INF;
  }
  if (is_done[u][len]) return dp[u][len];
  dp[u][len] = INF;
  int sz = adj[u].size();
  for (int i = 0 ; i < sz; i++) {
    int v = adj[u][i].first;
    Long w = adj[u][i].second;
    dp[u][len] = min(dp[u][len], w + DP(v, len - 1));
  }
  is_done[u][len] = true;
  return dp[u][len];
}

vector<int> ans;
void Reconstruct(int u, int len) {
  ans.push_back(u + 1);
  if (u == n - 1) return;
  int sz = adj[u].size();
  for (int i = 0; i < sz; i++) {
    int v = adj[u][i].first;
    Long w = adj[u][i].second;
    if (w + DP(v, len - 1) == DP(u, len)) {
      Reconstruct(v, len - 1);
      return;
    }
  }
}

int main(void) {
  FAST_IO;
  cin >> n >> m >> T;
  for (int i = 0; i < m; i++) {
    int u, v;
    Long w;
    cin >> u >> v >> w;
    u--;
    v--;
    adj[u].push_back({v, w});
  }

  int k = 0;
  for (int i = 1; i < n; i++) {
    if (DP(0, i) <= T) k = i;
  }

  // Reconstruyo en k
  cout << k + 1 << '\n';
  Reconstruct(0, k);
  int len = ans.size();
  for (int i = 0; i < len; i++) {
    if (i > 0) cout << " ";
    cout << ans[i];
  }
  cout << '\n';
  return 0;
}
