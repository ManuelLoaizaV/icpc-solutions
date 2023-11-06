// https://codeforces.com/problemset/problem/1303/C
#include <iomanip>
#include <iostream>
#include <cassert>
#include <utility>
#include <vector>
#define debug(x) cout << #x << " = " << x << ENDL
using namespace std;

typedef long long Long;

const char ENDL = '\n';
const char A = 'a';
const int ALPHABET_SIZE = 26;

int n_vertices;

bool adj[ALPHABET_SIZE][ALPHABET_SIZE];
bool found[ALPHABET_SIZE];
bool used[ALPHABET_SIZE];
int degrees[ALPHABET_SIZE];
vector<int> order;

void Init(void) {
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        found[i] = false;
        used[i] = false;
        degrees[i] = 0;
        for (int j = 0; j < ALPHABET_SIZE; j++) {
            adj[i][j] = false;
        }
    }
    order.clear();
}

void Add(char from, char to) {
    adj[from - A][to - A] = true;
    adj[to - A][from - A] = true;
}

void DFS(int u) {
    used[u] = true;
    order.push_back(u);
    for (int v = 0; v < ALPHABET_SIZE; v++) {
        if (!adj[u][v] || used[v]) continue;
        DFS(v);
    }
}

void Solve(void) {
    Init();
    string s;
    cin >> s;
    int n = (int)s.size();
    for (char c : s) {
        found[c - A] = true;
    }
    for (int i = 0; i < n - 1; i++) {
        Add(s[i], s[i + 1]);
    }
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        for (int j = 0; j < ALPHABET_SIZE; j++) {
            if (adj[i][j]) {
                degrees[i]++;
            }
        }
    }
    if (n == 1) {
        cout << "YES" << ENDL;
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            char c = (char)((int)A + i);
            cout << c;
        }
        cout << ENDL;
        return;
    }

    DFS(s[0] - A);
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (found[i] == used[i]) continue;
        cout << "NO" << ENDL;
        return;
    }

    vector<int> ends;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (degrees[i] > 2) {
            cout << "NO" << ENDL;
            return;
        } else if (degrees[i] == 1) {
            ends.push_back(i);
        }
        used[i] = false;
    }

    if ((int)ends.size() != 2) {
        cout << "NO" << ENDL;
        return;
    }

    order.clear();
    DFS(ends[0]);
    cout << "YES" << ENDL;
    for (int i : order) {
        char c = (char)((int)A + i);
        cout << c;
    }
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (found[i]) continue;
        char c = (char)((int)A + i);
        cout << c;
    }
    cout << ENDL;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n_test_cases;
    cin >> n_test_cases;
    while (n_test_cases--) Solve();
    return 0;
}