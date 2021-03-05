//https://codeforces.com/problemset/problem/29/C
#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> Pair;

const int N = 1e5 + 5;

vector<int> adj[N];
int parent[N];

void DFS(int u, int p) {
  parent[u] = p;
  for (int v : adj[u]) if (v != p) DFS(v, u);
}

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n;
  vector<Pair> p(n);
  set<int> uni;
  for (int i = 0; i < n; i++) {
    cin >> p[i].first >> p[i].second;
    uni.insert(p[i].first);
    uni.insert(p[i].second);
  }
  map<int, int> go, inv;
  int sz = 0;
  for (auto it : uni) {
    go[it] = sz;
    inv[sz] = it;
    sz++;
  }
  vector<int> freq(sz, 0);
  for (int i = 0; i < n; i++) {
    adj[go[p[i].first]].push_back(go[p[i].second]);
    adj[go[p[i].second]].push_back(go[p[i].first]);
    freq[go[p[i].first]]++;
    freq[go[p[i].second]]++;
  }
  vector<int> ends;
  for (int i = 0; i < sz; i++) {
    if (freq[i] == 1) {
      ends.push_back(i);
    }
  }
  DFS(ends[0], -1);
  int cur = ends[1];
  vector<int> ans;
  while (cur != -1) {
    ans.push_back(inv[cur]);
    cur = parent[cur];
  }
  for (int i = 0; i < sz; i++) {
    if (i > 0) cout << " ";
    cout << ans[i];
  }
  cout << '\n';
  return 0;
}