// https://cses.fi/problemset/task/1624/
#include <bits/stdc++.h>
using namespace std;

string board[8];
long long n_solutions = 0;
bool row_used[8];
bool diag_used[16];
bool antidiag_used[16];

void Backtrack(int col) {
    if (col == 8) {
        n_solutions++;
        return;
    }
    for (int row = 0; row < 8; row++) {
        if (
            board[row][col] == '.' &&
            !row_used[row] &&
            !diag_used[row + col] &&
            !antidiag_used[row + (7 - col)]
        ) {
            row_used[row] = true;
            diag_used[row + col] = true;
            antidiag_used[row + (7 - col)] = true;
            Backtrack(col + 1);
            row_used[row] = false;
            diag_used[row + col] = false;
            antidiag_used[row + (7 - col)] = false;
        }
    }
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0);
    for (int i = 0; i < 8; i++) {
        cin >> board[i];
    }
    Backtrack(0);
    cout << n_solutions << endl; 
    return 0;
}