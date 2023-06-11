// https://codeforces.com/problemset/problem/1466/E
#include <iostream>
#include <vector>
using namespace std;

typedef long long Long;

Long MOD = 1000000007LL;

const int MAX_BITS = 60;
Long powers[MAX_BITS];

Long Sum(Long a, Long b) {
    return (a + b) % MOD;
}

Long Mul(Long a, Long b) {
    return (a * b) % MOD;
}

Long Sub(Long a, Long b) {
    return (a - b + MOD) % MOD;
}

Long GetBit(Long n, Long i) {
    return ((n >> i) & 1LL);
}

void Solve(void) {
    Long n;
    cin >> n;
    vector<Long> x(n);
    Long total_sum = 0LL;
    vector<Long> digit_sums(MAX_BITS, 0LL);
    for (int i = 0; i < n; i++) {
        cin >> x[i];
        for (Long bit = 0; bit < MAX_BITS; bit++) {
            digit_sums[bit] = Sum(digit_sums[bit], GetBit(x[i], bit));
        }
        total_sum = Sum(total_sum, Mul(x[i], 1LL));
    }

    Long expression = 0LL;
    for (Long i = 0; i < n; i++) {
        Long and_sum = 0LL;
        Long or_sum = Sum(Mul(Mul(x[i], 1LL), n), total_sum);
        for (Long bit = 0; bit < MAX_BITS; bit++) {
            Long factor = Mul(GetBit(x[i], bit), Mul(powers[bit], digit_sums[bit]));
            and_sum = Sum(and_sum, factor);
            or_sum = Sub(or_sum, factor);
        }
        Long product = Mul(and_sum, or_sum);
        expression = Sum(expression, product);
    }
    cout << expression << '\n';
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0);
    powers[0] = 1LL;
    for (int bit = 1; bit < MAX_BITS; bit++) {
        powers[bit] = Mul(powers[bit - 1], 2LL);
    }
    Long t;
    cin >> t;
    while (t--) Solve();
    return 0;
}