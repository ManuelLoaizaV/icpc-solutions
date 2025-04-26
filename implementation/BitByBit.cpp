// https://open.kattis.com/problems/bitbybit
#include <algorithm>
#include <iostream>
#include <vector>

void Solve(int n) {
    std::vector<int> bits(32, -1);
    while (n > 0) {
        std::string instruction;
        std::cin >> instruction;
        if (instruction == "CLEAR") {
            int i;
            std::cin >> i;
            bits[i] = 0;
        } else if (instruction == "SET") {
            int i;
            std::cin >> i;
            bits[i] = 1;
        } else if (instruction == "OR") {
            int i, j;
            std::cin >> i >> j;
            if (bits[i] == 1 || bits[j] == 1) {
                bits[i] = 1;
            } else if (bits[i] == 0) {
                bits[i] = bits[j];
            }
        } else if (instruction == "AND") {
            int i, j;
            std::cin >> i >> j;
            if (bits[i] == 0 || bits[j] == 0) {
                bits[i] = 0;
            } else if (bits[i] == 1) {
                bits[i] = bits[j];
            }
        }
        n--;
    }
    std::reverse(bits.begin(), bits.end());
    for (const auto& bit : bits) {
        if (bit == -1) {
            std::cout << '?';
        } else {
            std::cout << bit;
        }
    }
    std::cout << std::endl;
}

int main(void) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int n;
    while (std::cin >> n) {
        if (n == 0) break;
        Solve(n);
    }
    return 0;
}