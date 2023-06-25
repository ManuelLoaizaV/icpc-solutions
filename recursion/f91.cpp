// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1637
#include <iostream>
using namespace std;

typedef long long Long;

Long f91(Long n) {
    if (n >= 101) {
        return n - 10;
    }
    return f91(f91(n + 11));
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0);
    Long n;
    while (cin >> n) {
        if (n == 0) break;
        cout << "f91(" << n << ") = " << f91(n) << '\n';
    }
    return 0;
}