// https://open.kattis.com/problems/restaurant
#include <iostream>

using namespace std;

void Solve(int n_lines) {
    int take_pile = 0;
    int drop_pile = 0;
    while (n_lines > 0) {
        string instruction;
        int n_plates;
        std::cin >> instruction >> n_plates;
        if (instruction == "DROP") {
            drop_pile += n_plates;
            std::cout << "DROP 2 " << n_plates << std::endl;
        } else if (instruction == "TAKE") {
            int n_take = std::min(n_plates, take_pile);
            if (n_take > 0) {
                std::cout << "TAKE 1 " << n_take << std::endl;
                take_pile -= n_take;
                n_plates -= n_take;
            }
            if (n_plates > 0) {
                std::cout << "MOVE 2->1 " << drop_pile << std::endl;
                take_pile += drop_pile;
                drop_pile = 0;
                std::cout << "TAKE 1 " << n_plates << std::endl;
                take_pile -= n_plates;
            }
        }
        n_lines--;
    }
}

int main(void) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int n;
    bool first_time = true;
    while (std::cin >> n) {
        if (n == 0) break;
        if (first_time) {
            first_time = false;
        } else {
            std::cout << std::endl;
        }
        Solve(n);
    }
    return 0;
}