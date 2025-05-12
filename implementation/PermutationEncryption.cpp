// https://open.kattis.com/problems/permutationencryption
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

int main(void) {
    std::string line;
    while (std::getline(std::cin, line)) {
        if (line == "0") break;
        std::istringstream iss(line);
        int n;
        iss >> n;
        std::vector<int> p(n);
        for (auto& e : p) {
            iss >> e;
            --e;
        }
        std::getline(std::cin, line);
        int to_add = (n - line.size() % n) % n;
        while (to_add--) line += ' ';
        std::string encrypted = line;
        int B = line.size() / n;
        for (int b = 0; b < B; ++b) {
            for (int i = 0; i < n; ++i) {
                encrypted[b * n + i] = line[b * n + p[i]];
            }
        }
        std::cout << '\'' << encrypted << '\'' << std::endl;
    }
    return 0;
}
