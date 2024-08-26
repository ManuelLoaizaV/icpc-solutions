// https://codeforces.com/problemset/problem/706/B
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main(void) {
    int n;
    cin >> n;
    vector<int> v(n);
    for (int i = 0; i < n; i++) cin >> v[i];
    sort(v.begin(), v.end());
    int Q;
    cin >> Q;
    for (int q = 0; q < Q; q++) {
        int budget;
        cin >> budget;
        // p(i) = v[i] > budget
        // FFFTTT
        int l = 0;
        int r = n - 1;
        
        // FFFFFF
        if (v[r] <= budget) {
            cout << n << endl;
            continue;
        }

        // TTTTTT
        if (v[l] > budget) {
            cout << 0 << endl;
            continue;
        }

        // FFFTTT
        while (r - l > 1) {
            int m = (l + r) / 2;
            if (v[m] > budget) {
                r = m;
            } else {
                l = m;
            }
        }

        // FT
        cout << r << endl;
    }
    return 0;
}