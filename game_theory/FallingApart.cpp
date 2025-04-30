// https://open.kattis.com/problems/fallingapart
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
    std::sort(v.begin(), v.end());
    bool alice{true};
    int bob_sum{0};
    int alice_sum{0};
    for (int i = n - 1; i >= 0; --i) {
        if (alice) {
            alice_sum += v[i];
        } else {
            bob_sum += v[i];
        }
        alice = !alice;
    }
    std::cout << alice_sum << ' ' << bob_sum << std::endl;
    return 0;
}