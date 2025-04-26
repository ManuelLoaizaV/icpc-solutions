// https://open.kattis.com/problems/hothike
#include <algorithm>
#include <iostream>
#include <vector>

int main(void) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int n;
    std::cin >> n;
    std::vector<int> v(n);
    for (auto& e : v) std::cin >> e;
    int m = 1;
    for (int i = 2; i < n - 1; i++) {
        if (
            std::max(v[i - 1], v[i + 1])
            < std::max(v[m - 1], v[m + 1])
        ) {
            m = i;
        }
    }
    int min_max = std::max(v[m - 1], v[m + 1]);
    std::cout << m << " " << min_max << std::endl;
    return 0;
}