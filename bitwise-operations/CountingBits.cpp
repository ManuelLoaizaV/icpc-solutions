// https://leetcode.com/problems/counting-bits/
class Solution {
public:
    vector<int> countBits(int n) {
        vector<int> bits;
        for (int i = 0; i <= n; i++) {
            bits.push_back(__builtin_popcount(i));
        }
        return bits;
    }
};