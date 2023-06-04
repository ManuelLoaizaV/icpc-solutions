// https://leetcode.com/problems/add-binary/
class Solution {
public:
    const char ZERO = '0';
    const char ONE = '1';
    string addBinary(string a, string b) {
        vector<string> numbers = {a, b};
        int n = max((int)a.size(), (int)b.size());
        for (int i = 0; i < 2; i++) {
            reverse(numbers[i].begin(), numbers[i].end());
            while ((int)numbers[i].size() < n) {
                numbers[i] += ZERO;
            }
        }
        string sum;
        int carry = 0;
        for (int i = 0; i < n; i++) {
            int digit = carry;
            for (int j = 0; j < 2; j++) {
                digit += (numbers[j][i] - ZERO);
            }
            sum += (char)(ZERO + (digit & 1));
            carry = digit >> 1;
        }
        if (carry > 0) {
            sum += ONE;
        }
        reverse(sum.begin(), sum.end());
        return sum;
    }
};