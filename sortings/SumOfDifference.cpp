#include <algorithm>
#include <iostream>
#include <vector>

int main(void) {
    int n;
    std::cin >> n;
    std::vector<long long> a(n);
    for (auto& e : a) std::cin >> e;
    std::sort(a.begin(), a.end());
    std::vector<long long> p(n);
    p[0] = a[0];
    for (int i = 1; i < n; ++i) {
        p[i] = p[i - 1] + a[i];
    }
    long long sum{0LL};
    for (long long i = n - 1; i > 0; i--) {
        sum += i * a[i] - p[i - 1];
    }
    std::cout << sum << std::endl;
    return 0;
}