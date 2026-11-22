// https://codeforces.com/contest/2288/problem/B1
#include <bits/stdc++.h>
using namespace std;

typedef long long Long;

const int MAX_X = 100;
const int MAX_Y = 100;
const int MAX_M = 50;

int dp[MAX_X + 1][MAX_Y + 1][MAX_M];
bool done[MAX_X + 1][MAX_Y + 1][MAX_M];
int X, Y, M;
string s;

int DP(int x, int y, int i) {
    if (i == M) return x + y;
    if (done[x][y][i]) return dp[x][y][i];
    dp[x][y][i] = x + y;
    if (s[i] == '-') {
        if (x > 0) {
            dp[x][y][i] = max(
                dp[x][y][i],
                DP(x - 1, y, i + 1)
            );
        }
        if (y > 0) {
            dp[x][y][i] = max(
                dp[x][y][i],
                DP(x + 1, y - 1, i + 1)
            );
        }
    } else {
        if (x > 0) {
            dp[x][y][i] = max(
                dp[x][y][i],
                DP(x - 1, y + 1, i + 1)
            );
        }
        if (y > 0) {
            dp[x][y][i] = max(
                dp[x][y][i],
                DP(x, y + 1, i + 1)
            );
        }
    }
    done[x][y][i] = true;
    return dp[x][y][i];
}

void Solve(void) {
    cin >> X >> Y >> M >> s;
    for (int i = 0; i <= X + M; i++) {
        for (int j = 0; j <= Y + M; j++) {
            for (int k = 0; k < M; k++) {
                done[i][j][k] = false;
            }
        }
    }
    cout << DP(X, Y, 0) << endl;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t = 1;
    cin >> t;
    while (t--) Solve();
    return 0;
}