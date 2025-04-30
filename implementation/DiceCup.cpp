// https://open.kattis.com/problems/dicecup
#include <algorithm>
#include <iostream>
#include <vector>

int main(void) {
    int n, m;
    std::cin >> n >> m;
    std::vector<int> freq(n + m + 1);
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            ++freq[i + j];
        }
    }
    int mx = *std::max_element(freq.begin(), freq.end());
    for (int i = 2; i <= n + m; ++i) {
        if (freq[i] == mx) {
            std::cout << i << std::endl;
        }
    }
    return 0;
}