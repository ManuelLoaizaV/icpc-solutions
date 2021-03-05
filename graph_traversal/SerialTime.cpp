//https://codeforces.com/problemset/problem/60/B/
#include <bits/stdc++.h>

using namespace std;

typedef tuple<int, int, int> Trio;

const int N = 15;
const int INF = 1e9;

int dx[6] = {0, 0, 0, 0, 1, -1};
int dy[6] = {0, 0, 1, -1, 0, 0};
int dz[6] = {1, -1, 0, 0, 0, 0};

int d[N][N][N];

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int k, n, m;
  cin >> k >> n >> m;
  vector<vector<string>> s(k, vector<string>(n));
  for (int i = 0; i < k; i++) {
    for (int j = 0; j < n; j++) {
      cin >> s[i][j];
    }
  }
  int x, y;
  cin >> x >> y;
  x--; y--;
  Trio ini = {0, x, y};
  for (int i = 0; i < k; i++) {
    for (int j = 0; j < n; j++) {
      for (int l = 0; l < m; l++) {
        d[i][j][l] = INF;
      }
    }
  }
  d[get<0>(ini)][get<1>(ini)][get<2>(ini)] = 1;
  queue<Trio> q;
  q.push(ini);
  while (!q.empty()) {
    Trio u = q.front();
    q.pop();
    for (int i = 0; i < 6; i++) {
      Trio v = {get<0>(u) + dx[i], get<1>(u) + dy[i], get<2>(u) + dz[i]};
      if (0 <= get<0>(v) && get<0>(v) < k &&
          0 <= get<1>(v) && get<1>(v) < n &&
          0 <= get<2>(v) && get<2>(v) < m &&
          s[get<0>(v)][get<1>(v)][get<2>(v)] == '.' &&
          d[get<0>(u)][get<1>(u)][get<2>(u)] + 1 < d[get<0>(v)][get<1>(v)][get<2>(v)]) {
        d[get<0>(v)][get<1>(v)][get<2>(v)] = d[get<0>(u)][get<1>(u)][get<2>(u)] + 1;
        q.push(v);
      }
    }
  }
  int cnt = 0;
  for (int i = 0; i < k; i++) {
    for (int j = 0; j < n; j++) {
      for (int l = 0; l < m; l++) {
        if (d[i][j][l] < INF) {
          cnt++;
        }
      }
    }
  }
  cout << cnt << '\n';
  return 0;
}