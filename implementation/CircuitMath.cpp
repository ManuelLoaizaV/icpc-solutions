// https://open.kattis.com/problems/circuitmath
#include <cassert>
#include <cctype>
#include <iostream>
#include <sstream>
#include <stack>
#include <vector>

int main(void) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    std::string line;
    std::getline(std::cin, line);
    int n{std::stoi(line)};

    std::getline(std::cin, line);
    std::stringstream ss(line);
    std::vector<bool> v(n);
    for (int i = 0; i < n; ++i) {
        char c;
        ss >> c;
        v[i] = c == 'T';
    }

    std::getline(std::cin, line);
    ss = std::stringstream(line);
    char c;
    std::stack<bool> s;
    while (ss >> c) {
        if (std::isalpha(c)) {
            s.push(v[(int)c - (int)'A']);
            continue;
        }
        bool last{s.top()};
        s.pop();
        if (c == '-') {
            s.push(!last);
            continue;
        }
        bool prev{s.top()};
        s.pop();
        if (c == '+') {
            s.push(last || prev);
        } else if (c == '*') {
            s.push(last && prev);
        } else {
            assert(false);
        }
    }
    
    std::cout << (s.top() ? 'T' : 'F') << std::endl;
    return 0;
}