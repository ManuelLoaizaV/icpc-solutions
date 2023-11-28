// https://codeforces.com/contest/1898/problem/F
#include <bits/stdc++.h>

#define debug(x) cout << #x << " = " << x << endl

using namespace std;

typedef long long Long;

const int N = 1e3;
const int INF = 1e7;
const char ENDL = '\n';

const int N_DIRECTIONS = 4;
const int ROW_DIRECTIONS[N_DIRECTIONS] = {-1, 0, 0, 1};
const int COL_DIRECTIONS[N_DIRECTIONS] = {0, -1, 1, 0};
const pair<int, int> E = {-1, -1};

// sps[i][j][k]: Source of the k-th shortest path to grid[i][j]
int shortest_paths[N][N][2];
pair<int, int> shortest_path_sources[N][N][2];
string grid[N];
int n_rows, n_cols;

bool IsValid(int row, int col) {
  return 0 <= row && row < n_rows && 0 <= col && col < n_cols;
}

void BFS(vector<pair<int, int>> sources) {
  for (int i = 0; i < n_rows; i++) {
    for (int j = 0; j < n_cols; j++) {
      for (int k = 0; k < 2; k++) {
        shortest_path_sources[i][j][k] = E;
        shortest_paths[i][j][k] = INF;
      }
    }
  }

  queue<pair<pair<int, int>, int>> tour;  // {cell, k-th}
  for (pair<int, int> source : sources) {
    int row = source.first;
    int col = source.second;
    shortest_path_sources[row][col][0] = source;
    shortest_paths[row][col][0] = 0;
    tour.push({source, 0});
  }

  while (!tour.empty()) {
    pair<pair<int, int>, int> u_k = tour.front();
    tour.pop();

    pair<int, int> u = u_k.first;
    int k = u_k.second;
    int row = u.first;
    int col = u.second;

    for (int i = 0; i < N_DIRECTIONS; i++) {
      int new_row = row + ROW_DIRECTIONS[i];
      int new_col = col + COL_DIRECTIONS[i];
      pair<int, int> v = {new_row, new_col};

      if (!IsValid(new_row, new_col) || grid[new_row][new_col] == '#') continue;
      
      int new_distance = shortest_paths[row][col][k] + 1;
      pair<int, int> source = shortest_path_sources[row][col][k];

      if (new_distance < shortest_paths[new_row][new_col][0]) {
        shortest_paths[new_row][new_col][0] = new_distance;
        shortest_path_sources[new_row][new_col][0] = source;
        tour.push({v, 0});
      } else if (
        source != shortest_path_sources[new_row][new_col][0] &&
        new_distance < shortest_paths[new_row][new_col][1]
      ) {
        shortest_paths[new_row][new_col][1] = new_distance;
        shortest_path_sources[new_row][new_col][1] = source;
        tour.push({v, 1});
      }
    }
  }
}

void Solve(void) {
  cin >> n_rows >> n_cols;
  for (int i = 0; i < n_rows; i++) {
    cin >> grid[i];
  }

  int n_empty_cells = 0;
  pair<int, int> source;

  for (int i = 0; i < n_rows; i++) {
    for (int j = 0; j < n_cols; j++) {
      if (grid[i][j] == 'V') {
        source = {i, j};
      }
      if (grid[i][j] == '.') {
        n_empty_cells++;
      }
    }
  }

  BFS({source});

  int shortest_path = INF;
  vector<pair<int, int>> sources;

  for (int i = 0; i < n_rows; i++) {
    for (int j = 0; j < n_cols; j++) {
      if (
        (i == 0 || i == n_rows - 1 || j == 0 || j == n_cols - 1) &&
        grid[i][j] != '#' &&
        shortest_paths[i][j][0] < INF
      ) {
        sources.push_back({i, j});
        shortest_path = min(shortest_path, shortest_paths[i][j][0]);
      }
    }
  }

  int n_sources = (int)sources.size();
  // Case no exit cells
  if (n_sources == 0) {
    cout << n_empty_cells << ENDL;
    return;
  }

  // Case only one exit cell
  if (n_sources == 1) {
    cout << n_empty_cells - shortest_path << ENDL;
    return;
  }

  vector<vector<int>> shortest_paths_from_source(n_rows, vector<int>(n_cols));
  for (int i = 0; i < n_rows; i++) {
    for (int j = 0; j < n_cols; j++) {
      shortest_paths_from_source[i][j] = shortest_paths[i][j][0];
    }
  }

  BFS(sources);

  int mn = INF;
  for (int i = 0; i < n_rows; i++) {
    for (int j = 0; j < n_cols; j++) {
      if (shortest_paths_from_source[i][j] < INF) {
        int tmp = shortest_paths_from_source[i][j] + shortest_paths[i][j][0] + shortest_paths[i][j][1];
        mn = min(mn, tmp);
      }
    }
  }

  cout << n_empty_cells - mn << ENDL;
}

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int t = 1;
  cin >> t;
  while (t--) Solve();
  return 0;
}