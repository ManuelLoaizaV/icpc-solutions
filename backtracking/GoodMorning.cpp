// https://open.kattis.com/problems/goodmorning
#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

std::vector<std::vector<int>> board{
    {1, 2, 3},
    {4, 5, 6},
    {7, 8, 9},
    {-1, 0, -1}
};

std::set<int> pool;

void Generate(int i, int j, int len, int prefix) {
    if (i >= 4 || j >= 3 || len >= 3 || board[i][j] == -1) return;
    int number = 10 * prefix + board[i][j];
    pool.insert(number);
    Generate(i, j, len + 1, number);
    Generate(i + 1, j, len, prefix);
    Generate(i, j + 1, len, prefix);
}

int main(void) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    Generate(0, 0, 0, 0);

    int t;
    std::cin >> t;
    while (t--) {
        int k;
        std::cin >> k;
        auto lb_it = std::lower_bound(pool.begin(), pool.end(), k);
        if (lb_it == pool.begin()) {
            std::cout << *lb_it << std::endl;
        } else {
            auto prev_it = lb_it;
            --prev_it;
            int prev = *prev_it;
            if (lb_it == pool.end()) {
                std::cout << prev << std::endl;
            } else {
                int lb = *lb_it;
                if (std::abs(k - prev) < std::abs(k - lb)) {
                    std::cout << prev << std::endl;
                } else {
                    std::cout << lb << std::endl;
                }
            }
        }
    }
    return 0;
}