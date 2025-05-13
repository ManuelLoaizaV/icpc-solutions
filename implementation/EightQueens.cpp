// https://open.kattis.com/problems/8queens
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

int main(void) {
    std::vector<std::string> board(8);
    for (int i = 0; i < 8; ++i) {
        std::cin >> board[i];
    }
    bool valid{true};
    int cnt{0};
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (board[i][j] != '*') continue;
            ++cnt;
            for (int x = 0; x < 8; ++x) {
                for (int y = 0; y < 8; ++y) {
                    if (x == i && y == j || board[x][y] != '*') continue;
                    if (x == i || y == j || std::abs(i - x) == std::abs(j - y)) {
                        valid = false;
                        break;
                    }
                }
                if (!valid) break;
            }
        }
        if (!valid) break;
    }
    if (cnt != 8) {
        valid = false;
    }
    std::cout << (valid ? "valid" : "invalid") << std::endl;
    return 0;
}