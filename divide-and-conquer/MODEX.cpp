// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=3671
#include <iostream>
#include <vector>
using namespace std;

typedef long long Long;

Long Mul(Long a, Long b, Long m) {
    return ((a % m) * (b % m)) % m;
}

Long BinPow(Long x, Long y, Long z) {
    if (y == 0) return 1LL;
    Long half = BinPow(x, y / 2, z);
    Long result = Mul(half, half, z);
    if (y & 1) result = Mul(result, x, z);
    return result;
}

void Solve(void) {
    Long x, y, z;
    cin >> x >> y >> z;
    cout << BinPow(x, y, z) << '\n';
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--) Solve();
    cin >> t;
    return 0;
}