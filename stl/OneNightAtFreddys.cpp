// https://codeforces.com/contest/2207/problem/B
#include <bits/stdc++.h>
using namespace std;

void Solve(void) {
    int N, M, L;
    cin >> N >> M >> L;
    queue<int> a;
    for (int i = 0; i < N; i++) {
        int x;
        cin >> x;
        a.push(x);
    }
    multiset<int> towers;
    for (int t = 1; t <= L; t++) {
        int target_size = (int)a.size() + 1;
        if (towers.size() < target_size && towers.size() < M) {
            towers.insert(1);
        } else {
            int min_tower = *towers.begin();
            towers.erase(towers.begin());
            towers.insert(min_tower + 1);
        }
        if (!a.empty() && a.front() == t) {
            towers.erase(std::prev(towers.end()));
            a.pop();
        }
    }
    int x = 0;
    if (!towers.empty()) {
        x = *towers.rbegin();;
    }
    cout << x << endl;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) Solve();
    return 0;
}