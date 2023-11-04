// https://codeforces.com/problemset/problem/623/A
#include <iomanip>
#include <iostream>
#include <cassert>
#include <utility>
#include <vector>
using namespace std;

const char ENDL = '\n';
const char A = 'a';

int n_vertices, n_edges;

vector<vector<int>> adj;
vector<int> labels;
vector<int> degrees;
int cnt[3];

void Init() {
    adj.resize(n_vertices);
    labels.resize(n_vertices, -1);
    degrees.resize(n_vertices, 0);
}

void Add(int from, int to) {
    adj[from].push_back(to);
    adj[to].push_back(from);
    degrees[from]++;
    degrees[to]++;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n_vertices >> n_edges;
    Init();
    for (int i = 0; i < n_edges; i++) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        Add(u, v);
    }

    // Label all 'b' nodes
    for (int i = 0; i < n_vertices; i++) {
        if (degrees[i] == n_vertices - 1) {
            labels[i] = 1;
            cnt[1]++;
        }
    }

    // Label all 'a' and 'c' nodes
    for (int color = 0; color < 3; color += 2) {
        for (int i = 0; i < n_vertices; i++) {
            if (labels[i] == -1) {
                labels[i] = color;
                cnt[color] = 1;
                for (int neighbor : adj[i]) {
                    if (labels[neighbor] != -1) continue;
                    labels[neighbor] = color;
                    cnt[color]++;
                }
                break;
            }
        }
    }

    bool ok = true;

    for (int i = 0; i < n_vertices; i++) {
        if (labels[i] == -1) {
            ok = false;
            break;
        }
    }

    if (!ok) {
        cout << "No" << ENDL;
        return 0;
    }

    for (int i = 0; i < n_vertices; i++) {
        if (labels[i] == 1) continue;
        if (degrees[i] < cnt[labels[i]] + cnt[1] - 1) {
            ok = false;
            break;
        }
        int ban = labels[i] ^ 2;
        for (int neighbor : adj[i]) {
            if (labels[neighbor] == ban) {
                ok = false;
                break;
            }
        }
        if (!ok) break;
    }

    if (ok) {
        cout << "Yes" << ENDL;
        for (int i = 0; i < n_vertices; i++) {
            char c = (char)((int)A + labels[i]);
            cout << c;
        }
        cout << ENDL;
    } else {
        cout << "No" << ENDL;
    }
    return 0;
}