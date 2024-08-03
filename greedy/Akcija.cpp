// https://open.kattis.com/problems/akcija
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

typedef long long Long;

int main(void) {
    int n;
    cin >> n;
    vector<Long> v(n);
    for (int i = 0; i < n; i++) cin >> v[i];
    sort(v.begin(), v.end());
    Long min_price = 0LL;
    int k = (n + 2LL) / 3LL;
    for (int b = 0; b < k; b++) {
        for (int i = 0; i < 2; i++) {
            int pos = n - 1 - i - 3 * b;
            if (pos >= 0) {
                min_price += v[pos];
            }
        }
    }
    cout << min_price << endl;
    return 0;
}