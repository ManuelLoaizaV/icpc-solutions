// https://cses.fi/problemset/task/2165
#include <iostream>
#include <utility>
#include <vector>
using namespace std;

vector<pair<int, int>> moves;

void Solve(int disks, int source, int target, int tmp) {
    if (disks == 1) {
        moves.push_back(make_pair(source, target));
    } else {
        Solve(disks - 1, source, tmp, target);
        moves.push_back(make_pair(source, target));
        Solve(disks - 1, tmp, target, source);
    }
}

int main(void) {
    int n;
    cin >> n;
    Solve(n, 1, 3, 2);
    
    int n_moves = (int)moves.size();
    cout << n_moves << endl;
    for (int i = 0; i < n_moves; i++) {
        cout << moves[i].first << ' ' << moves[i].second << endl;
    }
    return 0;
}