// https://cses.fi/problemset/task/2205
#include <iostream>
#include <vector>
using namespace std;

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;

    vector<int> gray_code;
    gray_code.push_back(0);

    for (int i = 0; i < n; i++) {
        int k = (int)gray_code.size();
        for (int j = k - 1; j >= 0; j--) {
            gray_code.push_back(gray_code[j] ^ (1 << i));
        }
    }

    for (int code : gray_code) {
        for (int i = 0; i < n; i++) {
            cout << ((code >> i) & 1);
        }
        cout << endl;
    }

    return 0;
}