// https://usaco.org/index.php?page=viewproblem2&cpid=694
#include <bits/stdc++.h>
using namespace std;

map<char, int> char_to_int{{'H', 0}, {'P', 1}, {'S', 2}};
vector<int> defeats{2, 0, 1};

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0);
    freopen("hps.in", "r", stdin);
    freopen("hps.out", "w", stdout);
    int N, K;
    cin >> N >> K;
    vector<int> rival(N);
    for (int i = 0; i < N; i++) {
        char r;
        cin >> r;
        rival[i] = char_to_int[r];
    }

    vector<vector<vector<int>>> dp(2, vector<vector<int>>(3, vector<int>(K + 1, 0)));
    for (int game = N - 1; game >= 0; game--) {
        for (int last = 0; last < 3; last++) {
            for (int k = 0; k <= K; k++) {
                dp[0][last][k] = (int)(defeats[last] == rival[game]) + dp[1][last][k];
                if (k > 0) {
                    for (int current = 0; current < 3; current++) {
                        if (current == last) continue;
                        dp[0][last][k] = max(
                            dp[0][last][k], 
                            (int)(defeats[current] == rival[game]) + dp[1][current][k - 1]
                        );
                    }
                }
            }
        }
        dp[1] = dp[0];
    }

    int max_wins = 0;
    for (int i = 0; i < 3; i++) {
        max_wins = max(max_wins, dp[0][i][K]);
    }
    cout << max_wins << endl;
    return 0;
}