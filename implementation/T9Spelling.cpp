// https://open.kattis.com/problems/t9spelling
#include <iostream>
#include <map>
#include <string>

int main(void) {
    std::map<char, std::string> actions;
    for (char c = 'a'; c <= 'z'; c++) {
        int d = (int)c - (int)'a';
        if (c >= 't') --d;
        int n = 2 + d / 3;
        std::string s;
        int t = d % 3 + 1;
        if (c == 's') {
            n = 7;
            t = 4;
        }
        if (c == 'z') {
            n = 9;
            t = 4;
        }
        for (int i = 0; i < t; ++i) s += std::to_string(n);
        actions[c] = s;
    }
    actions[' '] = '0';

    std::string line;
    int T;
    std::getline(std::cin, line);
    T = std::stoi(line);
    for (int t = 1; t <= T; ++t) {
        std::getline(std::cin, line);
        std::cout << "Case #" << t << ": ";
        for (int i = 0; i < line.size(); ++i) {
            if (i > 0 && actions[line[i]].front() == actions[line[i - 1]].front()) {
                std::cout << ' ';
            }
            std::cout << actions[line[i]];
        }
        std::cout << std::endl;
    }
    return 0;
}