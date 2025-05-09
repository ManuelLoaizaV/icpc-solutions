// https://codeforces.com/problemset/problem/844/B
#include <iostream>
#include <vector>

int main(void) {
    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<int>> v(n, std::vector<int>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            std::cin >> v[i][j];
        }
    }
    long long rectangles{0LL};
    for (int i = 0; i < n; ++i) {
        long long black{0LL};
        for (int j = 0; j < m; ++j) {
            if (v[i][j]) black++;
        }
        if (black > 0LL) {
            rectangles += (1LL << black) - 1LL;
        }
        long long white{m - black};
        if (white > 0LL) {
            rectangles += (1LL << white) - 1LL;
        }
    }
    for (int j = 0; j < m; ++j) {
        long long black{0LL};
        for (int i = 0; i < n; ++i) {
            if (v[i][j]) black++;
        }
        if (black > 0) {
            rectangles += (1LL << black) - 1LL;
        }
        long long white{n - black};
        if (white > 0) {
            rectangles += (1LL << white) - 1LL;
        }
    }
    rectangles -= n * m;
    std::cout << rectangles << std::endl;
    return 0;
}