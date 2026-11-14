// https://usaco.org/index.php?page=viewproblem2&cpid=965&lang=en
#include <bits/stdc++.h>
using namespace std;

int main(void) {
    freopen("lineup.in", "r", stdin);
    freopen("lineup.out", "w", stdout);
    vector<string> cows{
        "Beatrice",
        "Belinda",
        "Bella",
        "Bessie",
        "Betsy",
        "Blue",
        "Buttercup",
        "Sue"
    };
    sort(cows.begin(), cows.end());
    map<string, int> cow_to_int;
    for (int i = 0; i < cows.size(); i++) {
        cow_to_int[cows[i]] = i;
    }

    int N;
    cin >> N;

    vector<pair<int, int>> neighbors;
    for (int i = 0; i < N; i++) {
        string X, Y, Z;
        cin >> X >> Z >> Z >> Z >> Z >> Y;
        neighbors.emplace_back(cow_to_int[X], cow_to_int[Y]);
    }

    vector<int> permutation(cows.size());
    iota(permutation.begin(), permutation.end(), 0);

    do {
        bool ok = true;
        for (auto ii : neighbors) {
            int x = ii.first;
            int y = ii.second;
            bool found = false;
            for (int i = 0; i < permutation.size() - 1; i++) {
                if (
                    permutation[i] == x && permutation[i + 1] == y ||
                    permutation[i] == y && permutation[i + 1] == x
                ) {
                    found = true;
                    break;
                }
            }
            if (!found) {
                ok = false;
                break;
            }
        }
        if (ok) {
            for (int i = 0; i < cows.size(); i++) {
                cout << cows[permutation[i]] << endl;
            }
            break;
        }
    } while (next_permutation(permutation.begin(), permutation.end()));
    return 0;
}