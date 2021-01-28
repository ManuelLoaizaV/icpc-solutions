//https://codeforces.com/problemset/problem/1263/D
#include <iostream>
#include <set>
using namespace std;

const int N = 3e5;
const int ALPHABET = 26;

struct DisjointSets {
  int parent[N];
  int size[N];
  void MakeSet(int u) {
    parent[u] = u;
    size[u] = 1;
  }
  void Build(int n) { for (int i = 0; i < n; i++) MakeSet(i); }
  int Find(int u) {
    if (parent[u] == u) return u;
    return (parent[u] = Find(parent[u]));
  }
  void Join(int u, int v) {
    u = Find(u);
    v = Find(v);
    if (u != v) {
      if (size[u] > size[v]) swap(u, v);
      parent[u] = v;
      size[v] += size[u];
    }
  }
  bool SameSet(int u, int v) { return Find(u) == Find(v); }
  int GetSize(int u) { return size[Find(u)]; }
} dsu;


int main(void) {
  ios::sync_with_stdio(0);
  cin.tie(nullptr);
  int n;
  cin >> n;
  dsu.Build(n + ALPHABET);
  for (int i = 0; i < n; i++) {
    string s;
    cin >> s;
    for (char chr : s) {
      int c = chr - 'a';
      dsu.Join(c, ALPHABET + i);
    }
  }
  set<int> uni;
  for (int i = 0; i < n; i++) uni.insert(dsu.Find(i + ALPHABET));
  cout << uni.size() << '\n';
  return 0;
}
