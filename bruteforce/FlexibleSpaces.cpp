// https://open.kattis.com/problems/flexible
#include <iostream>
#include <vector>

int main(void) {
    int W, P;
    std::cin >> W >> P;
    std::vector<bool> walls(W + 1, false);
    walls[0] = walls[W] = true;
    for (int i = 0; i < P; ++i) {
        int x;
        std::cin >> x;
        walls[x] = true;
    }
    bool first_time = true;
    for (int i = 1; i <= W; ++i) {
        bool ok = false;
        for (int j = 0; j + i <= W; ++j) {
            if (walls[j] && walls[j + i]) {
                ok = true;
                break;
            }
        }
        if (ok) {
            if (first_time) {
                first_time = false;
            } else {
                std::cout << ' ';
            }
            std::cout << i;
        }
    }
    if (!first_time) {
        std::cout << std::endl;
    }
    return 0;
}