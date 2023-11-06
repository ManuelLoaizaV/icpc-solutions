// https://codeforces.com/problemset/problem/377/A
#include <iomanip>
#include <iostream>
#include <cassert>
#include <utility>
#include <vector>
#define debug(x) cout << #x << " = " << x << ENDL
using namespace std;

typedef long long Long;

const char ENDL = '\n';
const char DOT = '.';

int dx[] = {-1, 0, 0, 1};
int dy[] = {0, -1, 1, 0};
int n_walls, target_n_walls;
vector<vector<bool>> banned;

int n_vertices;
int n_rows, n_cols;

vector<vector<int>> adj;
vector<bool> used;

void Init(void) {
    banned = vector<vector<bool>>(n_rows, vector<bool>(n_cols, true));
    n_vertices = n_rows * n_cols;
    n_walls = 0;
    adj.resize(n_vertices);
    used.resize(n_vertices, false);
}

void Add(int from, int to) {
    adj[from].push_back(to);
}

void DFS(int u) {
    used[u] = true;
    if (n_walls > target_n_walls) {
        int row = u / n_cols;
        int col = u % n_cols;
        banned[row][col] = false;
        n_walls--;
    }
    for (int v : adj[u]) {
        if (used[v]) continue;
        DFS(v);
    }
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n_rows >> n_cols >> target_n_walls;

    Init();

    vector<string> grid(n_rows);
    for (int i = 0; i < n_rows; i++) {
        cin >> grid[i];
    }

    pair<int, int> origin;
    for (int row = 0; row < n_rows; row++) {
        for (int col = 0; col < n_cols; col++) {
            if (grid[row][col] != DOT) continue;
            n_walls++;
            origin = {row, col};
            for (int i = 0; i < 4; i++) {
                int new_row = row + dx[i];
                int new_col = col + dy[i];
                if (
                    0 <= new_row && new_row < n_rows &&
                    0 <= new_col && new_col < n_cols &&
                    grid[new_row][new_col] == DOT
                ) {
                    Add(row * n_cols + col, new_row * n_cols + new_col);
                }
            }
        }
    }

    DFS(origin.first * n_cols + origin.second);

    for (int row = 0; row < n_rows; row++) {
        for (int col = 0; col < n_cols; col++) {
            if (grid[row][col] == DOT && banned[row][col]) {
                cout << "X";
            } else {
                cout << grid[row][col];
            }
        }
        cout << ENDL;
    }
    return 0;
}