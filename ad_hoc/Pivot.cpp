// https://open.kattis.com/problems/pivot
#include <climits>
#include <iostream>
#include <vector>
using namespace std;

int main(void) {
    int n;
    cin >> n;
    vector<int> v(n);
    for (int i = 0; i < n; i++) cin >> v[i];
    vector<bool> prefix(n, false), suffix(n, false);
    int mx = INT_MIN;
    for (int i = 0; i < n; i++) {
        prefix[i] = v[i] >= mx;
        mx = max(mx, v[i]);
    }
    int mn = INT_MAX;
    for (int i = n - 1; i >= 0; i--) {
        suffix[i] = v[i] <= mn;
        mn = min(mn, v[i]);
    }
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        if (prefix[i] && suffix[i]) cnt++;
    }
    cout << cnt << endl;
    return 0;
}