#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <utility>
#include <vector>
#define FAST_IO ios::sync_with_stdio(0);cin.tie(NULL)
using namespace std;

typedef long long Long;
typedef pair<int, int> Pair;
typedef pair<Long, Pair> Edge;

const int N = 6666;
const Long MOD = 747474747LL;
vector<Edge> edges;

Long mul(Long a, Long b) {
  return ((a * b) % MOD);
}

Long distance(vector<Long>& v1, vector<Long>& v2, int d) {
  Long answer = 0LL;
  for (int i = 0; i < d; i++) {
    Long delta = v1[i] - v2[i];
    answer += (delta * delta);
  }
  return answer;
}

struct DisjointSets {
  int parent[N], size[N];
  
  void make_set(int u) {
    parent[u] = u;
    size[u] = 1;
  }

  void build(int n) {
    for (int i = 0; i < n; i++) make_set(i);
  }

  int find(int u) {
    if (u == parent[u]) {
      return u;
    } else {
      return (parent[u] = find(parent[u]));
    }
  }

  void join(int u, int v) {
    u = find(u);
    v = find(v);
    if (u != v) {
      if (size[u] > size[v]) swap(u, v);
      parent[u] = v;
      size[v] += size[u];
    }
  }

  bool same_set(int u, int v) {
    return (find(u) == find(v));
  }
} dsu;

Long MST(int n) {
  Long answer = 1LL;
  dsu.build(n);
  sort(edges.begin(), edges.end());
  for (Edge edge : edges) {
    Long w = edge.first;
    int u = edge.second.first;
    int v = edge.second.second;
    if (!dsu.same_set(u, v)) {
      dsu.join(u, v);
      w *= (-1);
      w %= MOD;
      answer = mul(answer, w);
    }
  }
  return answer;
}

void Solve(void) {
  int n, d;
  cin >> n >> d;
  vector<vector<Long>> points;
  for (int i = 0; i < n; i++) {
    vector<Long> current;
    for (int j = 0; j < d; j++) {
      Long x;
      cin >> x;
      current.push_back(x);
    }
    points.push_back(current);
  }
  edges.clear();
  for (int i = 0; i < n - 1; i++) {
    for (int j = i + 1; j < n; j++) {
      Long w = distance(points[i], points[j], d);
      if (w == 0) continue;
      edges.push_back({-w, {i, j}});
    }
  }
  Long answer = MST(n);
  cout << answer << '\n';
}

int main(void) {
  FAST_IO;
  int t;
  cin >> t;
  while (t--) Solve();
  return 0;
}
