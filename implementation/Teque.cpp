// https://open.kattis.com/problems/teque
#include <iostream>
#include <deque>

int main(void) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int n;
    std::cin >> n;
    std::deque<int> lhs, rhs;
    while (n--) {
        std::string op;
        int x;
        std::cin >> op >> x;
        if (op == "push_back") {
            rhs.push_back(x);
        } else if (op == "push_front") {
            lhs.push_front(x);
        } else if (op == "push_middle") {
            while (rhs.size() > lhs.size()) {
                lhs.push_back(rhs.front());
                rhs.pop_front();
            }
            while (lhs.size() > rhs.size() + 1) {
                rhs.push_front(lhs.back());
                lhs.pop_back();
            }
            lhs.push_back(x);
        } else if (op == "get") {
            if (x < lhs.size()) {
                std::cout << lhs[x] << std::endl;
            } else {
                std::cout << rhs[x - lhs.size()] << std::endl;
            }
        }
    }
    return 0;
}