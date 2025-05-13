// https://open.kattis.com/problems/toilet
#include <iostream>
#include <string>

int main(void) {
    std::string preferences;
    std::cin >> preferences;

    int n = (int)preferences.size();

    std::string p{preferences};
    int changes{0};
    for (int i = 1; i < n; ++i) {
        if (p[i] != p[i - 1]) {
            ++changes;
        }
        if (p[i] != 'U') {
            ++changes;
        }
        p[i] = 'U';
    }
    std::cout << changes << std::endl;

    p = preferences;
    changes = 0;
    for (int i = 1; i < n; ++i) {
        if (p[i] != p[i - 1]) {
            ++changes;
        }
        if (p[i] != 'D') {
            ++changes;
        }
        p[i] = 'D';
    }
    std::cout << changes << std::endl;

    p = preferences;
    changes = 0;
    for (int i = 1; i < n; ++i) {
        if (p[i] != p[i - 1]) {
            ++changes;
        }
    }
    std::cout << changes << std::endl;
    return 0;
}