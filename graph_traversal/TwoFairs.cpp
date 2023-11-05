// https://codeforces.com/problemset/problem/1276/B
#include <iomanip>
#include <iostream>
#include <cassert>
#include <utility>
#include <vector>
#define debug(x) cout << #x << " = " << x << ENDL
using namespace std;

typedef long long Long;

const int MAX_N_VERTICES = 200000;
const char ENDL = '\n';

int n_vertices;
int n_edges;

vector<int> adj[MAX_N_VERTICES];
bool used[MAX_N_VERTICES];

void Init() {
    for (int i = 0; i < n_vertices; i++) {
        adj[i].clear();
        used[i] = false;
    }
}

void Add(int from, int to) {
    adj[from].push_back(to);
    adj[to].push_back(from);
}

void DFS(int u, int ignored) {
    used[u] = true;
    for (int v : adj[u]) {
        if (used[v] || v == ignored) continue;
        DFS(v, ignored);
    }
}

void Solve(void) {
    cin >> n_vertices >> n_edges;
    vector<int> fairs(2);
    for (int i = 0; i < 2; i++) {
        cin >> fairs[i];
        fairs[i]--;
    }
    Init();
    for (int i = 0; i < n_edges; i++) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        Add(u, v);
        Add(v, u);
    }

    vector<Long> cnt(2, 0);
    for (int i = 0; i < 2; i++) {
        DFS(fairs[i], -1);
        vector<bool> reached_with_other_fair(n_vertices, false);
        for (int j = 0; j < n_vertices; j++) {
            reached_with_other_fair[j] = used[j];
            used[j] = false;
        }
        DFS(fairs[i], fairs[1 - i]);
        for (int j = 0; j < n_vertices; j++) {
            if (reached_with_other_fair[j] && !used[j]) {
                cnt[i]++;
            }
        }
    }
    Long result = (cnt[0] - 1LL) * (cnt[1] - 1LL);
    cout << result << ENDL;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n_test_cases;
    cin >> n_test_cases;
    while (n_test_cases--) Solve();
    return 0;
}