// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=2307
#include <iostream>
using namespace std;

typedef long long Long;

const Long TEN = 10;

// Recursive
Long DigitsSum(Long n) {
    if (n < TEN) return n;
    Long last_digit = n % TEN;
    return last_digit + DigitsSum(n / TEN);
}

// Iterative
// Long DigitsSum(Long n) {
//     Long sum = 0;
//     while (n > 0) {
//         Long last_digit = n % TEN;
//         sum += last_digit;
//         n /= TEN;
//     }
//     return sum;
// }

Long g(Long n) {
    if (n < TEN) return n;
    return g(DigitsSum(n));
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0);
    Long n;
    while (cin >> n) {
        if (n == 0) break;
        cout << g(n) << '\n';
    }
    return 0;
}