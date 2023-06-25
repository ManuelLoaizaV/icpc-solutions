// https://codeforces.com/enter?back=%2Fgym%2F382700%2Fproblem%2FI
#include <iostream>
using namespace std;

typedef long long Long;

// Number of ways to reach l from r
// with steps 1, 2 and 3.
// If l = r, there is one way.
// If l > r, there aren't any ways.
Long Ways(Long l, Long r) {
    if (l == r) return 1LL;
    if (l > r) return 0LL;
    Long ways = 0;
    for (Long step = 1; step <= 3; step++) {
        ways += Ways(l, r - step);
    }
    return ways;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0);
    Long l, r;
    cin >> l >> r;
    cout << Ways(l, r) << '\n';
    return 0;
}