// https://www.spoj.com/problems/BBIN/
#include <iostream>
#include <vector>
using namespace std;

int main(void) {
    int n, Q;
    cin >> n >> Q;
    
    vector<int> v(n);
    for (int i = 0; i < n; i++) cin >> v[i];
    
    for (int q = 0; q < Q; q++) {
        int target;
        cin >> target;

        int l = 0;
        int r = n - 1;

        // p(i) = a[i] >= target
        
        // FFFFFF
        if (v[r] < target) {
            cout << -1 << endl;
            continue;
        }

        // TTTTTT
        if (v[l] >= target) {
            if (v[l] == target) {
                cout << l << endl;
            } else {
                cout << -1 << endl;
            }
            continue;
        }
        
        // FFFTTT
        while (r - l > 1) {
            int m = (l + r) / 2;
            if (v[m] >= target) {
                r = m;
            } else {
                l = m;
            }
        }

        // FT
        if (v[r] == target) {
            cout << r << endl;
        } else {
            cout << -1 << endl;
        }
    }
    return 0;
}