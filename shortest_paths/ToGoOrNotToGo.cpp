// https://codeforces.com/contest/1520/problem/G
#include <cassert>
#include <iomanip>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>
#define debug(x) cout << #x << " = " << x << ENDL
using namespace std;

typedef long long Long;
typedef pair<int, int> Pair;

const char ENDL = '\n';
const int N_DIRECTIONS = 4;
const int ROW_DIRECTIONS[N_DIRECTIONS] = {-1, 0, 0, 1};
const int COL_DIRECTIONS[N_DIRECTIONS] = {0, -1, 1, 0};
const Long INF = 41e14;

int n_rows, n_cols;
vector<vector<Long>> grid;
vector<vector<Long>> distances;

void Init() {
    n_rows = (int)grid.size();
    n_cols = (int)grid[0].size();
    distances.resize(n_rows, vector<Long>(n_cols, INF));
}

bool IsValid(int row, int col) {
    return 0 <= row && row < n_rows && 0 <= col && col < n_cols;
}

void BFS(Pair source) {
    for (int i = 0; i < n_rows; i++) {
        for (int j = 0; j < n_cols; j++) {
            distances[i][j] = INF;
        }
    }
    distances[source.first][source.second] = 0;
    queue<Pair> tour;
    tour.push(source);
    while (!tour.empty()) {
        Pair u = tour.front();
        tour.pop();
        int row = u.first;
        int col = u.second;
        for (int i = 0; i < N_DIRECTIONS; i++) {
            int new_row = row + ROW_DIRECTIONS[i];
            int new_col = col + COL_DIRECTIONS[i];
            int new_distance = distances[row][col] + 1;
            if (
                IsValid(new_row, new_col) &&
                grid[new_row][new_col] >= 0 &&
                new_distance < distances[new_row][new_col]
            ) {
                distances[new_row][new_col] = new_distance;
                tour.push({new_row, new_col});
            }
        }
    }
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n_rows >> n_cols;
    Long w;
    cin >> w;
    grid.resize(n_rows, vector<Long>(n_cols));
    Init();
    for (int i = 0; i < n_rows; i++) {
        for (int j = 0; j < n_cols; j++) {
            cin >> grid[i][j];
        }
    }

    BFS({0, 0});

    Long min_distance = INF;
    if (distances[n_rows - 1][n_cols - 1] < INF) {
        min_distance = distances[n_rows - 1][n_cols - 1] * w;
    }

    vector<vector<Long>> from_source = distances;
    Long min_from_source_to_portal = INF;

    BFS({n_rows - 1, n_cols - 1});

    vector<vector<Long>> from_target = distances;
    Long min_from_target_to_portal = INF;

    for (int row = 0; row < n_rows; row++) {
        for (int col = 0; col < n_cols; col++) {
            if (from_source[row][col] < INF && grid[row][col] > 0) {
                min_from_source_to_portal = min(min_from_source_to_portal, from_source[row][col] * w + grid[row][col]);
            }
            if (from_target[row][col] < INF && grid[row][col] > 0) {
                min_from_target_to_portal = min(min_from_target_to_portal, from_target[row][col] * w + grid[row][col]);
            }
        }
    }

    if (min_from_source_to_portal < INF && min_from_target_to_portal < INF) {
        min_distance = min(min_distance, min_from_source_to_portal + min_from_target_to_portal);
    }

    if (min_distance == INF) {
        cout << -1 << ENDL;
    } else {
        cout << min_distance << ENDL;
    }
    return 0;
}
