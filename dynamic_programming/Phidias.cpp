// https://dmoj.ca/problem/ioi04p4
#include <bits/stdc++.h>
using namespace std;

const int MAX_W = 600;
vector<pair<int, int>> plates;
int dp[MAX_W + 1][MAX_W + 1];
bool done[MAX_W + 1][MAX_W + 1];

int DP(int w, int h) {
    if (w == 0 || h == 0) return 0;
    if (done[w][h]) return dp[w][h];
    dp[w][h] = 0;
    for (int i = 0; i < plates.size(); i++) {
        auto [w_i, h_i] = plates[i];
        if (w_i > w || h_i > h) continue;
        dp[w][h] = max(
            dp[w][h],
            w_i * h_i + max(
                DP(w - w_i, h_i) + DP(w, h - h_i),
                DP(w_i, h - h_i) + DP(w - w_i, h)
            )
        );
    }
    done[w][h] = true;
    return dp[w][h];
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int W, H;
    cin >> W >> H;
    int N;
    cin >> N;
    plates.resize(N);
    for (int i = 0; i < N; i++) {
        cin >> plates[i].first >> plates[i].second;
        done[plates[i].first][plates[i].second] = true;
        dp[plates[i].first][plates[i].second] = plates[i].first * plates[i].second;
    }
    int min_wasted = W * H - DP(W, H);
    cout << min_wasted << endl;
    return 0;
}