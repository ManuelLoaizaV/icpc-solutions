// https://open.kattis.com/problems/rockpaperscissors
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

int main(void) {
    std::string line;
    bool first_time{true};
    while (std::getline(std::cin, line)) {
        if (line == "0") break;
        if (first_time) {
            first_time = false;
        } else {
            std::cout << std::endl;
        }
        std::istringstream iss(line);
        int n, k;
        iss >> n >> k;
        std::vector<int> wins(n, 0);
        std::vector<int> losses(n, 0);
        int n_games = k * n * (n - 1) / 2;
        for (int g = 0; g < n_games; ++g) {
            std::getline(std::cin, line);
            iss = std::istringstream(line);
            int u, v;
            std::string au, av;
            iss >> u >> au >> v >> av;
            --u;
            --v;
            if (
                au == "rock" && av == "scissors" ||
                au == "scissors" && av == "paper" ||
                au == "paper" && av == "rock"
            ) {
                ++wins[u];
                ++losses[v];
            }
            if (
                av == "rock" && au == "scissors" ||
                av == "scissors" && au == "paper" ||
                av == "paper" && au == "rock"
            ) {
                ++wins[v];
                ++losses[u];
            }
        }
        for (int i = 0; i < n; ++i) {
            int total = wins[i] + losses[i];
            if (total == 0) {
                std::cout << "-" << std::endl;
            } else {
                auto ratio = (long double)wins[i] / total;
                std::cout << std::fixed << std::setprecision(3) << ratio << std::endl;
            }
        }
    }
    return 0;
}