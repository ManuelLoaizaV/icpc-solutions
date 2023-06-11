// https://codeforces.com/problemset/problem/1045/I
#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

typedef long long Long;

const int ALPHABET_SIZE = 26;
const char a = 'a';

int GetBit(int n, int i) {
    return ((n >> i) & 1);
}

void TurnOn(int& n, int i) {
    n = n | (1 << i);
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;

    unordered_map<int, Long> frequencies;

    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        vector<int> cnt(ALPHABET_SIZE, 0);
        for (char c : s) {
            cnt[c - a]++;
        }
        int mask = 0;
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            int bit = cnt[i] & 1;
            if (bit) {
                TurnOn(mask, i);
            }
        }
        if (frequencies.count(mask) > 0) {
            frequencies[mask]++;
        } else {
            frequencies[mask] = 1;
        }
    }

    vector<int> target_masks;
    target_masks.push_back(0);
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        target_masks.push_back(1 << i);
    }

    Long cnt = 0;
    for (pair<int, Long> mask_frequency: frequencies) {
        int mask = mask_frequency.first;
        Long frequency = mask_frequency.second;
        for (int target_mask: target_masks) {
            int complement = mask ^ target_mask;
            if (frequencies.count(complement) == 0) {
                continue;
            }
            if (mask == complement) {
                cnt += frequency * (frequency - 1LL);
            } else {
                cnt += frequency * frequencies[complement];
            }
        }
    }
    cnt /= 2;
    cout << cnt << '\n';
    return 0;
}