//https://codeforces.com/problemset/problem/734/E
#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << '\n'
using namespace std;

typedef long long Long;

const int N = 2e5;

vector<int> adj[N], new_adj[N];
int color[N];
int component[N];
int number_components;
bool is_used[N];

void DFS(int u, int c) {
  is_used[u] = true;
  component[u] = c;
  for (int v : adj[u]) {
    if (!is_used[v]) {
      if (color[u] == color[v]) {
        DFS(v, c);
      } else {
        number_components++;
        DFS(v, number_components);
      }
    }
  }
}

int depth[N];
void FindDiameter(int u, int h) {
  is_used[u] = true;
  depth[u] = h;
  for (int v : new_adj[u]) if (!is_used[v]) FindDiameter(v, h + 1);
}

int main(void) {
  ios::sync_with_stdio(0);
  cin.tie(nullptr);
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) cin >> color[i];
  for (int i = 0; i < n - 1; i++) {
    int u, v;
    cin >> u >> v;
    u--;
    v--;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  number_components = 0;
  DFS(0, 0);
  for (int i = 0; i < n; i++) {
    for (int v : adj[i]) {
      if (component[i] != component[v]) {
        new_adj[component[i]].push_back(component[v]);
      }
    }
  }
  number_components++;
  for (int i = 0; i < number_components; i++) is_used[i] = false;
  FindDiameter(0, 0);
  int maximum = 0;
  int left = 0;
  for (int i = 0; i < number_components; i++) {
    if (depth[i] > maximum) {
      maximum = depth[i];
      left = i;
    }
  }
  for (int i = 0; i < number_components; i++) is_used[i] = false;
  FindDiameter(left, 0);
  maximum = 0;
  for (int i = 0; i < number_components; i++) maximum = max(maximum, depth[i]);
  cout << (maximum + 1) / 2 << '\n';
  return 0;
}
