#include <climits>
#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <vector>
#define FAST_IO ios::sync_with_stdio(0);cin.tie(NULL)
using namespace std;

typedef unsigned long long Long;
typedef pair<Long, Long> Pair;

Long Random(void) {
  Long r = rand() % LONG_MAX + 1LL;
  Long l = rand() % LONG_MAX + 1LL;
  Long ans = (l << 30LL) + r;
  return ans;
}

map<Pair, Pair> h;

Pair Add(Pair a, Pair b) {
  return make_pair(a.first + b.first, a.second + b.second);
}

struct Graph {
  vector<int> parent;
  vector<vector<int>> adj;

  Graph(int n) {
    parent.resize(n);
    adj.resize(n, vector<int> ());
    parent[0] = -1;
  }

  void AddEdge(int u, int v) {
    adj[u].push_back(v);
    adj[v].push_back(u);
    parent[v] = u;
  }

  void Initialize(const string& s) {
    int cnt, cur;
    cnt = cur = 0;
    int len = s.size();
    for (int i = 0; i < len; i++) {
      if (s[i] == '0') {
        cnt++;
        AddEdge(cur, cnt);
        cur = cnt;
      } else {
        cur = parent[cur];
      }
    }
  }

  Pair GetHash(int u, int p) {
    Pair ans = make_pair(0LL, 0LL);
    int len = adj[u].size();
    for (int i = 0; i < len; i++) {
      int v = adj[u][i];
      if (v != p) ans = Add(ans, GetHash(v, u));
    }
    if (h.count(ans) > 0) return h[ans];
    h[ans] = make_pair(Random(), Random());
    return h[ans];
  }
};

int Count(const string& s) {
  int cnt = 0;
  int len = s.size();
  for (int i = 0; i < len; i++) if (s[i] == '0') cnt++;
  return cnt;
}

void Solve(void) {
  string s1, s2;
  cin >> s1 >> s2;

  Graph t1(Count(s1) + 1);
  t1.Initialize(s1);

  Graph t2(Count(s2) + 1);
  t2.Initialize(s2);
  
  if (t1.GetHash(0, -1) == t2.GetHash(0, -1)) {
    cout << "same" << '\n';
  } else {
    cout << "different" << '\n';
  }
}

int main(void) {
  FAST_IO;
  h[make_pair(0LL, 0LL)] = make_pair(Random(), Random());
  int t;
  cin >> t;
  while (t--) Solve();
  return 0;
}
