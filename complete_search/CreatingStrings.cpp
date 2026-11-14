// https://cses.fi/problemset/task/1622/
#include <bits/stdc++.h>
using namespace std;

map<char, int> frequencies;
vector<string> permutations;

string permutation;

void Backtrack(int i, int n) {
    if (i == n) {
        permutations.push_back(permutation);
        return;
    }
    for (auto p : frequencies) {
        char c = p.first;
        int cnt = p.second;
        if (cnt > 0) {
            permutation += c;
            frequencies[c]--;
            Backtrack(i + 1, n);
            permutation.pop_back();
            frequencies[c]++;
        }
    }
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0);
    string s;
    cin >> s;
    for (char c : s) {
        if (frequencies.count(c)) {
            frequencies[c]++;
        } else {
            frequencies[c] = 1;
        }
    }

    Backtrack(0, s.size());

    cout << permutations.size() << endl;
    for (int i = 0; i < permutations.size(); i++) {
        cout << permutations[i] << endl;
    }
    return 0;
}