// https://www.hackerrank.com/contests/tpperu2024/challenges/codigos
#include <bitset>
#include <iostream>
using namespace std;

const int MAX_A = 1024;
const int MAX_N = 200;
const int MAX_K = 126;

bitset<MAX_K> done[MAX_A][MAX_N];
bitset<MAX_K> dp[MAX_A][MAX_N];
int a[MAX_N];

bool DP(int i, int j, int k) {
    if (k == 0) {
        return i == 0;
    }
    if (j < 0) {
        return false;
    }
    if (done[i][j][k]) return dp[i][j][k];
    if (DP(i, j - 1, k) || DP(i ^ a[j], j - 1, k - 1)) dp[i][j].set(k);
    done[i][j].set(k);
    return dp[i][j][k];
}

int main(void) {
    int n, k;
    cin >> n >> k;
    for (int i = 0; i < n; i++) cin >> a[i];

    bitset<MAX_A> found;
    found.set(0);

    for (int i = 0; i < n; i++) {
        bitset<MAX_A> new_found;
        for (int j = 0; j < MAX_A; j++) {
            if (found[j]) {
                new_found.set(j ^ a[i]);
            }
        }
        found |= new_found;
    }

    int nuclear_code = 0;
    for (int i = MAX_A - 1; i > 0; i--) {
        if (found[i]) {
            nuclear_code = i;
            break;
        }
    }

    if (DP(nuclear_code, n - 1, k)) {
        cout << nuclear_code << endl;
    } else {
        cout << -1 << endl;
    }
    return 0;
}