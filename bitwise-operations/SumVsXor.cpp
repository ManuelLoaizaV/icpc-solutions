#include <iostream>
using namespace std;

typedef long long Long;

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0);
    Long n;
    cin >> n;
    if (n == 0) {
        cout << 1 << endl;
        return 0;
    }

    int n_zeros = 0;
    while (n > 0) {
        int last_bit = n & 1;
        if (last_bit == 0) {
            n_zeros++;
        }
        n >>= 1;
    }

    cout << (1LL << n_zeros) << endl;
    return 0;
}