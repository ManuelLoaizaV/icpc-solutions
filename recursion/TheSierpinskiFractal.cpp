// https://acm.ecnu.edu.cn/problem/1430/
#include <iostream>
#include <vector>
using namespace std;

typedef long long Long;

const char SPACE = ' ';
const char BASE = '_';
const char LEFT = '/';
const char RIGHT = '\\';
const char ENDL = '\n';

vector<vector<char>> grid;

void Sierpinski(int row, int col, int dim) {
    if (dim == 1) {
        grid[row][col + 1] = LEFT;
        grid[row][col + 2] = RIGHT;
        grid[row + 1][col] = LEFT;
        grid[row + 1][col + 1] = BASE;
        grid[row + 1][col + 2] = BASE;
        grid[row + 1][col + 3] = RIGHT;
        return;
    }
    Sierpinski(row, col + (1 << (dim - 1)), dim - 1);
    Sierpinski(row + (1 << (dim - 1)), col, dim - 1);
    Sierpinski(row + (1 << (dim - 1)), col + (1 << dim), dim - 1);
}

void Solve(int n) {
    grid = vector<vector<char>>(1 << n, vector<char>(1 << (n + 1), SPACE));
    Sierpinski(0, 0, n);
    for (int i = 0; i < (1 << n); i++) {
        for (int j = 0; j < (1 << (n + 1)); j++) {
            cout << grid[i][j];
        }
        cout << ENDL;
    }
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    while (cin >> n) {
        if (n == 0) break;
        Solve(n);
        cout << ENDL;
    }
    return 0;
}