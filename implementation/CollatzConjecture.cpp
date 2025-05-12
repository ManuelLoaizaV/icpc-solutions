// https://open.kattis.com/problems/collatz
#include <iostream>
#include <unordered_map>
#include <string>

using Long = long long;

void Solve(Long A, Long B) {
    std::unordered_map<Long, Long> A_steps;
    A_steps[A] = 0LL;
    Long C{A};
    Long steps{0LL};
    while (C != 1LL) {
        ++steps;
        if (C & 1) {
            C = 3LL * C + 1LL;
        } else {
            C /= 2LL;
        }
        A_steps[C] = steps;
    }

    steps = 0LL;
    C = B;
    while (!A_steps.contains(C)) {
        ++steps;
        if (C & 1) {
            C = 3LL * C + 1LL;
        } else {
            C /= 2LL;
        }
    }

    std::cout << A << " needs " << A_steps[C] << " steps, "
    << B << " needs " << steps << " steps, "
    << "they meet at " << C << std::endl;
}

int main(void) {
    Long A, B;
    while (std::cin >> A >> B) {
        if (A == 0 && B == 0) {
            break;
        }
        Solve(A, B);
    }
    return 0;
}