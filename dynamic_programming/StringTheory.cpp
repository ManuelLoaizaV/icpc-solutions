// https://open.kattis.com/problems/string
#include <iostream>
#include <vector>
using namespace std;

const int M = 10099;
const int K = 85;

int k;
int m;
int prefix_sums[M];
bool done[M][K + 1][2];
bool dp[M][K + 1][2];
vector<bool> quotations;

int CountQuotations(int l, int r) {
    int cnt = prefix_sums[r];
    if (l > 0) cnt -= prefix_sums[l - 1];
    return cnt;
}

// Let k > 1. Then DP computes whether quotations[index..m-1] is valid
// given that last block of quotations has length 'previous' and we are currently 'descending'.
bool DP(int index, int previous, bool descending) {
    if (index == m) return previous == k && !descending;
    if (previous == k && !descending) return false;
    
    if (done[index][previous - 1][descending]) return dp[index][previous - 1][descending];
    dp[index][previous - 1][descending] = false;

    if (!quotations[index]) {
        dp[index][previous - 1][descending] = DP(index + 1, previous, descending);
    } else {
        if (descending) {
            if (previous > 2) {
                int last = min(m - 1, index + previous - 2);
                int cnt = CountQuotations(index, last);
                if (cnt == previous - 1)
                    dp[index][previous - 1][descending] |= DP(last + 1, previous - 1, true);
            } else {
                if (index < m - 1 && quotations[index + 1])
                    dp[index][previous - 1][descending] |= DP(index + 2, 1, false);
                if (index < m - 2 && !quotations[index + 1] && quotations[index + 2])
                    dp[index][previous - 1][descending] |= DP(index + 3, 1, false);
            }
        } else {
            int last = min(m - 1, index + previous);
            int cnt = CountQuotations(index, last);
            if (cnt == previous + 1 && previous <= k - 1)
                dp[index][previous - 1][descending] |= DP(last + 1, previous + 1, false);

            if (previous == 1) {
                if (index < m - 1 && quotations[index + 1])
                    dp[index][previous - 1][descending] |= DP(index + 2, 1, false);
                if (index < m - 2 && !quotations[index + 1] && quotations[index + 2])
                    dp[index][previous - 1][descending] |= DP(index + 3, 1, false);
            } else {
                last = min(m - 1, index + previous - 1);
                cnt = CountQuotations(index, last);
                if (cnt == previous)
                    dp[index][previous - 1][descending] |= DP(last + 1, previous, true);
            }
        }
    }

    done[index][previous - 1][descending] = true;
    return dp[index][previous - 1][descending];
}

int main(void) {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    for (int i = 0; i < n; i++) {
        if (i > 0) {
            quotations.push_back(false);
        }
        for (int j = 0; j < a[i]; j++) {
            quotations.push_back(true);
        }
    }

    m = (int)quotations.size();
    for (int i = 0; i < m; i++) {
        if (i > 0) prefix_sums[i] = prefix_sums[i - 1];
        if (quotations[i]) prefix_sums[i]++;
    }

    int max_k = 0;
    for (k = K; k > 0; k--) {
        if (k > 1) {
            for (int i = 0; i < m; i++) {
                for (int j = 0; j <= k; j++) {
                    for (int p = 0; p < 2; p++) {
                        done[i][j][p] = false;
                    }
                }
            }
        }
        if (k == 1 && prefix_sums[m - 1] == 2 || k > 1 && DP(0, k + 1, true)) {
            max_k = k;
            break;
        }
    }

    if (max_k > 0) {
        cout << max_k << endl;
    } else {
        cout << "no quotation" << endl;
    }
    return 0;
}