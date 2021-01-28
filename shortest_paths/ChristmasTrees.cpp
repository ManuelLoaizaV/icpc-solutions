//https://codeforces.com/problemset/problem/1283/D
#include <iostream>
#include <map>
#include <queue>
#include <utility>
#include <vector>
using namespace std;

typedef long long Long;


Long BFS(const vector<int>& trees, vector<int>& people, int m) {
  map<int, Long> d;
  queue<int> tour;
  for (int tree : trees) {
    d[tree] = 0;
    tour.push(tree);
  }
  Long sum = 0;
  int cnt = 0;
  while (cnt < m) {
    int u = tour.front();
    Long distance = d[u];
    tour.pop();
    for (int delta = -1; delta < 2; delta += 2) {
      int v = u + delta;
      if (d.count(v) == 0) {
        Long new_distance = distance + 1LL;
        d[v] = new_distance;
        tour.push(v);
        people.push_back(v);
        sum += new_distance;
        cnt++;
      }
      if (cnt == m) break;
    }
  }
  return sum;
}

int main(void) {
  ios::sync_with_stdio(0);
  cin.tie(nullptr);
  int n, m;
  cin >> n >> m;
  vector<int> trees(n), people;
  for (int i = 0; i < n; i++) cin >> trees[i];
  cout << BFS(trees, people, m) << '\n';
  for (int i = 0; i < m; i++) {
    if (i > 0) cout << " ";
    cout << people[i];
  }
  cout << '\n';
  return 0;
}
