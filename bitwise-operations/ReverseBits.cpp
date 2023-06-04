// https://leetcode.com/problems/reverse-bits/
class Solution {
public:
    const int BITS = 32;

    int GetBit(uint32_t n, int i) {
        return ((n >> i) & 1);
    }

    void TurnOn(uint32_t& n, int i) {
        n |= (1 << i);
    }

    uint32_t reverseBits(uint32_t n) {
        uint32_t reversed_number = 0;
        for (int i = 0; i < BITS; i++) {
            int position = BITS - 1 - i;
            if (GetBit(n, i)) {
                TurnOn(reversed_number, position);
            }
        }
        return reversed_number;
    }
};