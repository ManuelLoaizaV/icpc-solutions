// https://codeforces.com/problemset/problem/903/C
#include <bits/stdc++.h>
using namespace std;

int main(void) {
    int n;
    cin >> n;
    map<int, int> frequencies;
    for (int i = 0; i < n; i++) {
        int number;
        cin >> number;
        if (frequencies.count(number)) {
            frequencies[number]++;
        } else {
            frequencies[number] = 1;
        }
    }

    int boxes = 0;
    for (auto kv : frequencies) {
        boxes = max(boxes, kv.second);
    }
    cout << boxes << endl;
    return 0;
}