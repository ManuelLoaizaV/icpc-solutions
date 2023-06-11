// https://leetcode.com/problems/missing-number/
class Solution {
public:
    int missingNumber(vector<int>& nums) {
        int missing_number = 0;
        int n = (int)nums.size();
        for (int i = 1; i <= n; i++) {
            missing_number ^= (i ^ nums[i - 1]);
        }
        return missing_number;
    }
};