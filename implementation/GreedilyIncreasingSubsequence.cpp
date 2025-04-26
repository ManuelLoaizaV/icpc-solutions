// https://open.kattis.com/problems/greedilyincreasing
#include <iostream>
#include <vector>

int main(void) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int n;
    std::cin >> n;
    std::vector<int> v(n);
    for (int i = 0; i < n; i++) std::cin >> v[i];
    std::vector<int> gis{v[0]};
    for (int i = 1; i < n; i++) {
        if (v[i] > gis.back()) {
            gis.push_back(v[i]);
        }
    }
    size_t n_gis= gis.size();
    std::cout << n_gis << std::endl;
    for (size_t i = 0; i < n_gis; i++) {
        if (i > 0) std::cout << ' ';
        std::cout << gis[i];
    }
    std::cout << std::endl;
    return 0;
}