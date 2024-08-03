// https://codeforces.com/problemset/problem/373/A
#include <iostream>
#include <vector>
using namespace std;

int main(void) {
    int k;
    cin >> k;
    vector<string> s(4);
    for (int i = 0; i < 4; i++) cin >> s[i];

    vector<int> cnt(9, 0);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (s[i][j] == '.') continue;
            cnt[s[i][j] - '1']++;
        }
    }
    for (int i = 0; i < 9; i++) {
        if (cnt[i] > 2 * k) {
            cout << "NO" << endl;
            return 0;
        }
    }
    cout << "YES" << endl;
    return 0;
}