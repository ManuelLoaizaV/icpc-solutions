// https://atcoder.jp/contests/abc164/tasks/abc164_c
#include <bits/stdc++.h>
using namespace std;

int main(void) {
    int n;
    cin >> n;
    set<string> words;
    for (int i = 0; i < n; i++) {
        string word;
        cin >> word;
        words.insert(word);
    }
    cout << words.size() << endl;
    return 0;
}
