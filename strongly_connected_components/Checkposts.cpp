// Gracias, Osman
#include <bits/stdc++.h>
#define FAST_IO ios::sync_with_stdio(0);cin.tie(NULL)
#define debug(x) cout << #x << " = " << x << '\n'
using namespace std;

typedef long long Long;
typedef pair<Long, Long> Pair;

const Long MOD = 1e9 + 7;
const int N = 1e5;
const Long INF = 1e18;

vector<int> adj[N], rev[N];
stack<int> st;
bool seen[N];
Long cost[N], tag[N], comp;

Long mul(Long a, Long b) {
  return (a * b) % MOD;
}

void DFS1(int u) {
  seen[u] = true;
  for (int v : adj[u]) if (!seen[v]) DFS1(v);
  st.push(u);
}

void DFS2(int u) {
  seen[u] = true;
  tag[u] = comp;
  for (int v : rev[u]) if (!seen[v]) DFS2(v);
}

int main() {
  FAST_IO;
  int n, m;
  cin >> n;
  for (int i = 0; i < n; i++) cin >> cost[i];
  cin >> m;
  for (int i = 0; i < m; i++) {
    int u, v;
    cin >> u >> v;
    u--;
    v--;
    adj[u].push_back(v);
    rev[v].push_back(u);
  }
  for (int i = 0; i < n; i++) if (!seen[i]) DFS1(i);
  memset(seen, false, sizeof(seen));
  while (st.size()) {
    int u = st.top();
    st.pop();
    if (!seen[u]) {
      DFS2(u);
      comp++;
    }
  }
  vector<Pair> mn(comp, {0, INF});
  for (int i = 0; i < n; i++) {
    if (cost[i] < mn[tag[i]].second) {
      mn[tag[i]].first = 1LL;
      mn[tag[i]].second = cost[i];
    } else {
      if (cost[i] == mn[tag[i]].second) {
        mn[tag[i]].first++;
      }
    }
  }
  Pair ans = {0LL, 1LL};
  for (Pair cur : mn) {
    ans.first += cur.second;
    ans.second = mul(ans.second, cur.first);
  }
  cout << ans.first << " " << ans.second << '\n';
  return 0;
}
