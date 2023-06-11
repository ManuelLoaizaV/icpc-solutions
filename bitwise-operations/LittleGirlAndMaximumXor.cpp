// https://codeforces.com/problemset/problem/276/D
#include <iostream>
#include <vector>
#define debug(x) cout << #x << " = " << x << '\n'
using namespace std;

typedef unsigned long long Long;

const int MAX_SIZE = 64;

int GetBit(Long n, int i) {
    return ((n >> i) & 1);
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0);
    vector<Long> v(2);
    for (int i = 0; i < 2; i++) cin >> v[i];

    int digits = MAX_SIZE - min(__builtin_clzl(v[0]), __builtin_clzl(v[1]));
    Long max_xor = 0;
    for (int i = digits - 1; i >= 0; i--) {
        vector<int> bits(2);
        for (int j = 0; j < 2; j++) bits[j] = GetBit(v[j], i);
        if (bits[0] == 0 && bits[1] == 1) {
            max_xor = (1LL << (i + 1)) - 1;
            break;
        }
    }
    cout << max_xor << '\n';
    return 0;
}