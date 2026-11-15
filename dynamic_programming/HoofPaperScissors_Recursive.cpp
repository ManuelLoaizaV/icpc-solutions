// https://usaco.org/index.php?page=viewproblem2&cpid=694
#include <bits/stdc++.h>
using namespace std;

const int N = 100000;
const int K = 20;
const int M = 3;

int rival[N];
int dp[M][K + 1][N];
bool done[M][K + 1][N];

map<char, int> char_to_int{{'H', 0}, {'P', 1}, {'S', 2}};
vector<int> defeats{2, 0, 1};
int n;

int DP(int last, int switches, int game) {
    if (game == n) return 0;
    if (done[last][switches][game]) return dp[last][switches][game];
    dp[last][switches][game] = (int)(defeats[last] == rival[game]) + DP(last, switches, game + 1);
    if (switches > 0) {
        for (int current = 0; current < M; current++) {
            if (current == last) continue;
            dp[last][switches][game] = max(
                dp[last][switches][game], 
                (int)(defeats[current] == rival[game]) + DP(current, switches - 1, game + 1)
            );
        }
    }
    done[last][switches][game] = true;
    return dp[last][switches][game];
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0);
    freopen("hps.in", "r", stdin);
    freopen("hps.out", "w", stdout);
    int k;
    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        char r;
        cin >> r;
        rival[i] = char_to_int[r];
    }
    int max_wins = 0;
    for (int i = 0; i < 3; i++) {
        max_wins = max(max_wins, DP(i, k, 0));
    }
    cout << max_wins << endl;
    return 0;
}