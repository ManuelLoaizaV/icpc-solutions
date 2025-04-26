// https://open.kattis.com/problems/baloni
#include <iostream>
#include <vector>

const int N = 1000000;

int cnt[N + 2];

int main(void) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int n;
    std::cin >> n;
    int min_arrows = 0;
    for (int i = 0; i < n; i++) {
        int h;
        std::cin >> h;
        if (cnt[h + 1] > 0) {
            cnt[h + 1]--;
        } else {
            min_arrows++;
        }
        cnt[h]++;
    }
    std::cout << min_arrows << std::endl;
    return 0;
}