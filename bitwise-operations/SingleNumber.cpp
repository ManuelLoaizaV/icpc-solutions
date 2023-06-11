// https://leetcode.com/problems/single-number/
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int nums_xor = 0;
        for (int num: nums) {
            nums_xor ^= num;
        }
        return nums_xor;
    }
};