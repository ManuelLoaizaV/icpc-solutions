// https://codeforces.com/enter?back=%2Fgym%2F382700%2Fproblem%2FK
#include <iostream>
#include <vector>
using namespace std;

typedef long long Long;

const Long INF = 1e7;

Long n_rows, n_cols;
vector<vector<Long>> grid;

// MaxPathSum(row, col):
// Maximum sum of a path from (row, col) to (0, 0)
// with the movements left or up.
Long MaxPathSum(long row, Long col) {
    if (row == 0 && col == 0) return grid[0][0];
    if (row < 0 || col < 0) return -INF;
    return grid[row][col] + max(MaxPathSum(row - 1, col), MaxPathSum(row, col - 1));
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n_rows >> n_cols;
    grid = vector<vector<Long>>(n_rows, vector<Long>(n_cols));
    for (int i = 0; i < n_rows; i++) {
        for (int j = 0; j < n_cols; j++) {
            cin >> grid[i][j];
        }
    }
    cout << MaxPathSum(n_rows - 1, n_cols - 1) << '\n';
    return 0;
}