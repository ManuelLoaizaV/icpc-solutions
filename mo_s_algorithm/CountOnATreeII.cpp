#include <algorithm>
#include <iostream>
#include <map>
#include <vector>
#define FAST_IO ios::sync_with_stdio(0);cin.tie(nullptr)
using namespace std;

const int N = 4e4;
const int SZ = 200;

vector<int> adj[N], tour;
int timer, depth[N], in[N], out[N], freq_w[N], freq[N], w[N], anc[N][32 - __builtin_clz(N)];

void DFS(int u) {
  in[u] = timer++;
  tour.push_back(u);
  for (int v : adj[u]) {
    if (v != anc[u][0]) {
      anc[v][0] = u;
      depth[v] = depth[u] + 1;
      DFS(v);
    }
  }
  out[u] = timer++;
  tour.push_back(u);
}

void Precalculate(int n, int root = 0) {
  anc[root][0] = -1;
  depth[root] = 0;
  timer = 0;
  DFS(root);
  for (int j = 1; (1 << j) < n; j++) {
    for (int i = 0; i < n; i++) {
      if (anc[i][j - 1] != -1) {
        anc[i][j] = anc[anc[i][j - 1]][j - 1];
      } else {
        anc[i][j] = -1;
      }
    }
  }
}

bool IsAncestor(int u, int v) {
  return (in[u] <= in[v] && out[u] >= out[v]);
}

int LCA(int u, int v) {
  if (IsAncestor(u, v)) return u;
  int bits = 31 - __builtin_clz(depth[u]);
  for (int i = bits; i >= 0; i--) {
    if (anc[u][i] != -1 && !IsAncestor(anc[u][i], v)) u = anc[u][i];
  }
  return anc[u][0];
}

struct Query {
  int id, l, r, u, v;

  Query() {} 
  Query(int id, int l, int r, int u, int v) : id(id), l(l), r(r), u(u), v(v) {}
  
  bool operator < (const Query& other) const {
    int block = l / SZ;
    int other_block = other.l / SZ;
    if (block != other_block) return (block < other_block);
    return (r > other.r);
  }
};

struct Mo {
  void Add(int id, int& ans) {
    freq[id]++;
    if (freq[id] == 2) {
      freq_w[w[id]]--;
      if (freq_w[w[id]] == 0) ans--;
    } else {
      freq_w[w[id]]++;
      if (freq_w[w[id]] == 1) ans++;
    }
  }
  
  void Delete(int id, int& ans) {
    freq[id]--;
    if (freq[id] == 1) {
      freq_w[w[id]]++;
      if (freq_w[w[id]] == 1) ans++;
    } else {
      freq_w[w[id]]--;
      if (freq_w[w[id]] == 0) ans--;
    }
  }
  
  vector<int> Build(const vector<int>& a, vector<Query>& q) {
    sort(q.begin(), q.end());
    vector<int> ans(q.size());
    int l = 0;
    int r = -1;
    int acc = 0;
    for (int i = 0; i < q.size(); i++) {
      if (q[i].u == q[i].v) {
        ans[q[i].id] = 1;
        continue;
      }
      while (r < q[i].r) Add(a[++r], acc);
      while (l > q[i].l) Add(a[--l], acc);
      while (r > q[i].r) Delete(a[r--], acc);
      while (l < q[i].l) Delete(a[l++], acc);
      if (!IsAncestor(q[i].u, q[i].v)) {
        int lca = LCA(q[i].u, q[i].v);
        Add(lca, acc);
        ans[q[i].id] = acc;
        Delete(lca, acc);
      } else {
        Add(q[i].u, acc);
        ans[q[i].id] = acc;
        Delete(q[i].u, acc);
      }
    }
    return ans;
  }
} mo;

int main(void) {
  FAST_IO;
  int n, m;
  cin >> n >> m;
  map<int, int> uni;
  for (int i = 0; i < n; i++) {
    cin >> w[i];
    uni[w[i]] = 0;
  }
  int cnt = 0;
  for (auto it : uni) {
    uni[it.first] = cnt;
    cnt++;
  }
  for (int i = 0; i < n; i++) w[i] = uni[w[i]];

  for (int i = 0; i < n - 1; i++) {
    int u, v;
    cin >> u >> v;
    u--;
    v--;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  Precalculate(n);

  vector<Query> queries;
  for (int i = 0; i < m; i++) {
    int u, v;
    cin >> u >> v;
    u--;
    v--;
    if (in[v] < in[u]) swap(u, v);
    queries.push_back(Query(i, in[u] + 1, in[v], u, v));
  }
  vector<int> ans = mo.Build(tour, queries);
  for (int x : ans) cout << x << '\n';
  return 0;
}
