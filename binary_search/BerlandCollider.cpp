// https://codeforces.com/problemset/problem/24/E
#include <algorithm>
#include <climits>
#include <iomanip>
#include <iostream>
#include <vector>
using namespace std;

typedef long long Long;
typedef long double Double;

const Double EPS = 1e-9;
const int N = 5e5;

int n;
Long x[N][2];

bool Check(Double t) {
    Double max_reached = LLONG_MIN;
    for (int i = 0; i < n; i++) {
        Double reached = x[i][0] + t * x[i][1];
        if (x[i][1] > 0) {
            if (reached > max_reached) {
                max_reached = reached;
            }
        } else if (max_reached >= reached) {
            return true;
        }
    }
    return false;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 2; j++) {
            cin >> x[i][j];
        }
    }
    Double l = 0.0L;
    Double r = 1e9;

    if (!Check(r)) {
        cout << -1 << endl;
        return 0;
    }

    while (r - l >= EPS) {
        Double m = (l + r) / 2;
        if (Check(m)) {
            r = m;
        } else {
            l = m;
        }
    }

    Double min_time = (l + r) / 2;
    cout << fixed << setprecision(12) << min_time << endl;

    return 0;
}