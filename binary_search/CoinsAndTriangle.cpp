// https://www.codechef.com/problems/TRICOIN
#include <iostream>
using namespace std;

typedef long long Long;

int main(void) {
    int t;
    cin >> t;
    while (t--) {
        Long n;
        cin >> n;
        Long l = 1LL;
        Long r = 100000LL;

        while (r - l > 1) {
            Long m = (l + r) / 2;
            if (m * (m + 1) / 2 <= n) {
                l = m;
            } else {
                r = m;
            }
        }

        cout << l << endl;
    }
    return 0;
}