// https://open.kattis.com/problems/secretmessage
#include <iostream>
#include <vector>

int MinSize(const std::string& s) {
    int L{1};
    int R{100};
    if (s.size() <= 1) return 1;
    while (R - L > 1) {
        int M = (L + R) / 2;
        if (s.size() <= M * M) {
            R = M;
        } else {
            L = M;
        }
    }
    return R;
}

void Solve(void) {
    std::string s;
    std::cin >> s;
    int K = MinSize(s);
    std::vector<std::vector<char>> g(K, std::vector<char>(K, '*'));

    for (int i = 0; i < s.size(); ++i) {
        int x = i / K;
        int y = i % K;
        g[y][K - 1 - x] = s[i];
    }

    std::string t;
    for (int i = 0; i < K; ++i) {
        for (int j = 0; j < K; ++j) {
            if (g[i][j] == '*') {
                continue;
            }
            t += g[i][j];
        }
    }
    std::cout << t << std::endl;
}

int main(void) {
    int N;
    std::cin >> N;
    while (N--) Solve();
    return 0;
}