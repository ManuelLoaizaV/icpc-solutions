// https://open.kattis.com/problems/bijele
#include <iostream>
#include <vector>
using namespace std;

int main(void) {
    vector<int> target = {1, 1, 2, 2, 2, 8};
    for (int i = 0; i < 6; i++) {
        int cnt;
        cin >> cnt;
        if (i > 0) cout << ' ';
        cout << target[i] - cnt;
    }
    cout << endl;
    return 0;
}