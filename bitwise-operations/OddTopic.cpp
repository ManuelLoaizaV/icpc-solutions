// https://www.codechef.com/problems/ODTPIC
#include <algorithm>
#include <bitset>
#include <iostream>
#include <vector>
using namespace std;

const int MAX_N = 1e5;
const int MAX_VALUE = 4e3;

bitset<MAX_VALUE + 1> prefixes[MAX_N + 1][2];

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0);

    vector<int> n(2);
    for (int i = 0; i < 2; i++) cin >> n[i];

    int q;
    cin >> q;

    int max_n = *max_element(n.begin(), n.end());
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < max_n; j++) {
            prefixes[j + 1][i] = prefixes[j][i];
            if (j < n[i]) {
                int value;
                cin >> value;
                prefixes[j + 1][i].flip(value);
            }
        }
    }

    while (q--) {
        bitset<MAX_VALUE + 1> segment;
        for (int i = 0; i < 2; i++) {
            int l, r;
            cin >> l >> r;
            segment = segment ^ prefixes[r][i] ^ prefixes[l - 1][i];
        }
        cout << segment.count() << '\n';
    }
    return 0;
}