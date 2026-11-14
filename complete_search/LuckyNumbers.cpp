// https://open.kattis.com/problems/luckynumber
#include <iostream>
#include <vector>

std::vector<int> number;

int Solve(int i, int n) {
    if (i == n) return 1;
    int from{0};
    if (i == 0) ++from;
    int cnt{0};
    int sum{0};
    for (int j{0}; j < i; ++j) {
        sum = (10 * sum + number[j]) % (i + 1);
    }
    for (int d{from}; d <= 9; ++d) {
        if ((10 * sum + d) % (i + 1) != 0) continue;
        number[i] = d;
        cnt += Solve(i + 1, n);
    }
    return cnt;
}

int main(void) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int n;
    std::cin >> n;
    number.resize(n);
    std::cout << Solve(0, n) << std::endl;
    return 0;
}