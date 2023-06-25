// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1863
#include <iostream>
using namespace std;

typedef long long Long;

const Long NINE = 9;
const Long TEN = 10;
const string STRING_ZERO = "0";
const char ZERO = '0';
const char ENDL = '\n';

Long DigitsSum(Long n) {
    if (n < TEN) return n;
    return n % TEN + DigitsSum(n / TEN);
}

Long NineDegree(Long n) {
    if (n % NINE != 0) return -1;
    if (n == NINE) return 1;
    return 1 + NineDegree(DigitsSum(n));
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0);
    string s;
    while (cin >> s) {
        if (s == STRING_ZERO) break;
        Long sum = 0;
        for (char c: s) {
            sum += (c - ZERO);
        }
        Long degree = NineDegree(sum);
        if (degree == -1) {
            cout << s << " is not a multiple of 9." << ENDL;
        } else {
            cout << s << " is a multiple of 9 and has 9-degree " << degree << "." << ENDL;
        }
    }
    return 0;
}