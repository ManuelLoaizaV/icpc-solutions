// https://codeforces.com/problemset/problem/4/C
#include <bits/stdc++.h>
using namespace std;

int main(void) {
    int n;
    cin >> n;
    map<string, int> frequencies;
    for (int i = 0; i < n; i++) {
        string word;
        cin >> word;
        if (frequencies.count(word)) {
            cout << word << frequencies[word] << endl;
            frequencies[word]++;
        } else {
            cout << "OK" << endl;
            frequencies[word] = 1;
        }
    }
    return 0;
}