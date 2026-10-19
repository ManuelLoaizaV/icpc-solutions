// https://atcoder.jp/contests/abc216/tasks/abc216_e
#include <bits/stdc++.h>
using namespace std;

typedef long long Long;

Long GetSatisfaction(const vector<Long>& A, Long K, const Long T) {
    Long satisfaction = 0LL;
    Long at_least = 0;
    for (int i = 0; i < A.size(); i++) {
        if (A[i] >= T) {
            at_least++;
        }
        if (A[i] <= T) continue;
        Long consume = min(A[i] - T, K);
        K -= consume;
        satisfaction += A[i] * (A[i] + 1LL) / 2LL;
        satisfaction -= (A[i] - consume) * (A[i] - consume + 1LL) / 2LL;
        if (K == 0) return satisfaction;
    }
    satisfaction += min(K, at_least) * T;
    return satisfaction;
}

bool Check(const vector<Long>& A, const Long K, const Long T) {
    Long steps = 0LL;
    for (int i = 0; i < A.size(); i++) {
        if (A[i] <= T) continue;
        steps += A[i] - T;
        if (steps > K) return false;
    }
    return steps + 1 <= K;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0);
    Long N, K;
    cin >> N >> K;
    vector<Long> A(N);
    Long mx = 0LL;
    for (int i = 0; i < N; i++) {
        cin >> A[i];
        mx = max(mx, A[i]);
    }
    sort(A.begin(), A.end(), std::greater<Long>());

    if (K == 0) {
        cout << 0 << endl;
        return 0;
    }

    // TTTT
    if (Check(A, K, 1LL)) {
        cout << GetSatisfaction(A, K, 1LL) << endl;
        return 0;
    }

    // TTFF
    Long L = mx;
    Long R = 1LL;
    while (L - R > 1) {
        Long M = (L + R) / 2;
        if (Check(A, K, M)) {
            L = M;
        } else {
            R = M;
        }
    }
    cout << GetSatisfaction(A, K, L) << endl;

    return 0;
}