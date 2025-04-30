// https://open.kattis.com/problems/trafficlights
#include <iostream>
#include <numeric>
#include <vector>

int main(void) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    size_t n;
    std::cin >> n;
    std::vector<long long> R(n), G(n);
    long long m{1LL};
    for (int i{0}; i < n; ++i) {
        std::cin >> R[i] >> G[i];
        m = std::lcm(m, R[i] + G[i]);
    }
    bool found{false};
    long long t{1LL};
    while (t <= m) {
        bool ok = true;
        for (int j{0}; j < n; ++j) {
            long long r{t % (R[j] + G[j])};
            if (r < R[j]) {
                ok = false;
                break;
            }
        }
        if (ok) {
            found = true;
            break;
        }
        ++t;
    }

    if (found) {
        std::cout << t << std::endl;
    } else {
        std::cout << -1 << std::endl;
    }
    return 0;
}