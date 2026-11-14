// https://codeforces.com/problemset/problem/581/D
#include <bits/stdc++.h>
using namespace std;

vector<pair<int, int>> logos;
vector<pair<int, int>> candidate;
vector<int> permutation(3);
int len;
const int N = 175;
char board[N][N];

bool Solve(void) {
    for (int i = 0; i < len; i++) {
        for (int j = 0; j < len; j++) {
            board[i][j] = '.';
        }
    }

    if (candidate[0].first > len || candidate[0].second > len) {
        return false;
    }

    for (int i = 0; i < candidate[0].first; i++) {
        for (int j = 0; j < candidate[0].second; j++) {
            board[i][j] = (char)((int)'A' + permutation[0]);
        }
    }

    if (candidate[0].second == len) {
        if (candidate[1].second > len || candidate[1].first + candidate[0].first > len) {
            return false;
        }
        for (int i = 0; i < candidate[1].first; i++) {
            for (int j = 0; j < candidate[1].second; j++) {
                board[candidate[0].first + i][j] = (char)((int)'A' + permutation[1]);
            }
        }
    } else {
        if (candidate[0].second + candidate[1].second > len || candidate[1].first > len) {
            return false;
        }
        for (int i = 0; i < candidate[1].first; i++) {
            for (int j = 0; j < candidate[1].second; j++) {
                board[i][candidate[0].second + j] = (char)((int)'A' + permutation[1]);
            }
        }
    }

    pair<int, int> third_start;
    bool found = false;
    for (int i = 0; i < len; i++) {
        for (int j = 0; j < len; j++) {
            if (board[i][j] == '.') {
                third_start = {i, j};
                found = true;
                break;
            }
        }
        if (found) {
            break;
        }
    }

    if (third_start.first + candidate[2].first > len || third_start.second + candidate[2].second > len) {
        return false;
    }

    for (int i = 0; i < candidate[2].first; i++) {
        for (int j = 0; j < candidate[2].second; j++) {
            if (board[third_start.first + i][third_start.second + j] != '.') {
                return false;
            }
            board[third_start.first + i][third_start.second + j] = (char)((int)'A' + permutation[2]);
        }
    }

    cout << len << endl;
    for (int i = 0; i < len; i++) {
        for (int j = 0; j < len; j++) {
            cout << board[i][j];
        }
        cout << endl;
    }

    return true;
}

int isqrt(int n) {
    if (n <= 0) return 0;
    int r = sqrt(n);
    while ((r + 1) * (r + 1) <= n) r++;
    while (r * r > n) r--;
    return r;
}

int main(void) {
    int area = 0;
    for (int i = 0; i < 3; i++) {
        int x, y;
        cin >> x >> y;
        logos.emplace_back(x, y);
        area += x * y;
    }

    len = isqrt(area);
    if (len * len != area) {
        cout << -1 << endl;
        return 0;
    }

    iota(permutation.begin(), permutation.end(), 0);

    do {
        for (int m = 0; m < 8; m++) {
            candidate.clear();
            for (int i = 0; i < 3; i++) {
                if ((m >> i) & 1) {
                    candidate.emplace_back(logos[permutation[i]].first, logos[permutation[i]].second);
                } else {
                    candidate.emplace_back(logos[permutation[i]].second, logos[permutation[i]].first);
                }
            }
            if (Solve()) {
                return 0;
            }
        }
    } while (next_permutation(permutation.begin(), permutation.end()));

    cout << -1 << endl;
    return 0;
}