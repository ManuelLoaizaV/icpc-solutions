// https://open.kattis.com/problems/plantingtrees
#include <algorithm>
#include <iostream>
#include <vector>

int main(void) {
    long long n;
    std::cin >> n;
    std::vector<long long> v(n);
    for (auto& e : v) std::cin >> e;
    std::sort(v.begin(), v.end());
    long long mx{0LL};
    long long mn{n};
    for (long long i = 0LL; i < n; i++) {
        mx = std::max(mx, v[i] - i);
    }
    mn += mx;
    std::cout << mn + 1LL << std::endl;
    return 0;
}
