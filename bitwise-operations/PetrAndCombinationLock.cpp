// https://codeforces.com/problemset/problem/1097/B
#include <iostream>
#include <vector>
using namespace std;

const int CYCLE = 360;

int GetBit(int n, int i) {
    return ((n >> i) & 1);
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    vector<int> rotations(n);
    for (int i = 0; i < n; i++) cin >> rotations[i];
    int n_masks = 1 << n;
    for (int mask = 0; mask < n_masks; mask++) {
        int sum = 0;
        for (int bit = 0; bit < n; bit++) {
            if (GetBit(mask, bit)) {
                sum += rotations[bit];
            } else {
                sum -= rotations[bit];
            }
        }
        if (sum % CYCLE == 0) {
            cout << "YES" << '\n';
            return 0;
        }
    }
    cout << "NO" << '\n';
    return 0;
}