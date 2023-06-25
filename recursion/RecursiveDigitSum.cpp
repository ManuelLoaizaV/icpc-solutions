// https://www.hackerrank.com/contests/being-zero/challenges/recursive-digit-sum
#include <iostream>
using namespace std;

typedef long long Long;

const char ZERO = '0';
const char ENDL = '\n';
const Long TEN = 10;

Long DigitsSum(Long n) {
    if (n < TEN) return n;
    return n % TEN + DigitsSum(n / TEN);
}

Long SuperDigit(Long n) {
    if (n < 10) return n;
    return SuperDigit(DigitsSum(n));
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0);
    string n;
    Long k;
    cin >> n >> k;
    Long sum = 0;
    for (char c: n) {
        sum += (c - ZERO);
    }
    sum *= k;
    cout << SuperDigit(sum) << ENDL;
    return 0;
}