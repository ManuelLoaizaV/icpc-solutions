//https://codeforces.com/gym/100625/attachments
#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << '\n'

using namespace std;

typedef pair<int, int> Pair;

const int N = 1e6 + 5;
const int INF = 1e9;

vector<Pair> adj[N];
vector<string> g;
vector<int> d[3];
int h, w;

int GetHash(int x, int y) {
  return w * x + y;
}

void BFS(int s, int id) {
  d[id] = vector<int>(h * w + 1, INF);
  d[id][s] = 0;
  deque<Pair> q;
  q.push_back({0, s});
  while (!q.empty()) {
    int u = q.front().second;
    int p = q.front().first;
    q.pop_front();
    if (d[id][u] != p) continue;
    for (Pair e : adj[u]) {
      int v = e.first;
      int we = e.second;
      if (d[id][u] + we < d[id][v]) {
        d[id][v] = d[id][u] + we;
        if (w == 0) {
          q.push_front({d[id][v], v});
        } else {
          q.push_back({d[id][v], v});
        }
      }
    }
  }
}

int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int tt;
  cin >> tt;
  while (tt--) {
    // Leo el input
    cin >> h >> w;
    g = vector<string>(h);
    for (int i = 0; i < h; i++) {
      cin >> g[i];
    }
    // Creo el grafo
    for (int i = 0; i <= h * w; i++) adj[i].clear();
    // Interiores hacia los demas
    for (int i = 0; i < h; i++) {
      for (int j = 0; j < w; j++) {
        if (g[i][j] == '*') continue;
        for (int k = 0; k < 4; k++) {
          int x = i + dx[k];
          int y = j + dy[k];
          if (0 <= x && x < h && 0 <= y && y < w) {
            if (g[x][y] == '*') continue;
            if (g[x][y] == '#') {
              adj[GetHash(i, j)].push_back({GetHash(x, y), 1});
            } else {
              adj[GetHash(i, j)].push_back({GetHash(x, y), 0});
            }
          } else {
            adj[GetHash(i, j)].push_back({h * w, 0});
          }
        }
      }
    }
    // Exterior hacia interiores
    for (int i = 0; i < h; i++) {
      if (g[i][0] == '*') continue;
      if (g[i][0] == '#') {
        adj[h * w].push_back({GetHash(i, 0), 1});
      } else {
        adj[h * w].push_back({GetHash(i, 0), 0});
      }
    }
    for (int i = 0; i < h; i++) {
      if (g[i][w - 1] == '*') continue;
      if (g[i][w - 1] == '#') {
        adj[h * w].push_back({GetHash(i, w - 1), 1});
      } else {
        adj[h * w].push_back({GetHash(i, w - 1), 0});
      }
    }
    for (int j = 0; j < w; j++) {
      if (g[0][j] == '*') continue;
      if (g[0][j] == '#') {
        adj[h * w].push_back({GetHash(0, j), 1});
      } else {
        adj[h * w].push_back({GetHash(0, j), 0});
      }
    }
    for (int j = 0; j < w; j++) {
      if (g[h - 1][j] == '*') continue;
      if (g[h - 1][j] == '#') {
        adj[h * w].push_back({GetHash(h - 1, j), 1});
      } else {
        adj[h * w].push_back({GetHash(h - 1, j), 0});
      }
    }
    // Obtengo las fuentes que son el exterior y los dos prisioneros
    vector<int> sources;
    sources.push_back(h * w);
    for (int i = 0; i < h; i++) {
      for (int j = 0; j < w; j++) {
        if (g[i][j] == '$') {
          sources.push_back(GetHash(i, j));
        }
      }
    }
    // Obtengo la distancia minima de cada fuenta hacia todos los nodos
    for (int i = 0; i < 3; i++) {
      BFS(sources[i], i);
    }
    // Caso base es que se encuentren afuera
    int ans = d[1][h * w] + d[2][h * w];
    for (int i = 0; i < h; i++) {
      for (int j = 0; j < w; j++) {
        if (g[i][j] == '*') continue;
        int cur = 0;
        for (int k = 0; k < 3; k++) {
          cur += d[k][GetHash(i, j)];
        }
        if (g[i][j] == '#') {
          cur -= 2;
        }
        ans = min(ans, cur);
      }
    }
    cout << ans << '\n';
  }
  return 0;
}