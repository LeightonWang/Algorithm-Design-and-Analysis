/*
Can be improved using priority queue. This is the O(n^2) DP version.
*/

#include <bits/stdc++.h>
using namespace std;

vector<int> longestDescending(vector<int>& nums) {
    int n = nums.size();
    vector<int> dp(n);
    for (int i = 0; i < n; i++) {
        dp[i] = 1;
        for (int j = 0; j < i; j++) {
            if (nums[j] > nums[i]) {
                if (dp[j] + 1 > dp[i])
                    dp[i] = dp[j] + 1;
            }
        }
    }

    return dp;
}


int main() {
    int n;
    cin >> n;
    vector<int> nums(n);
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    vector<int> res = longestDescending(nums);
    for (int i = 0; i < n; i++)
        cout << res[i] << ' ';

    return 0;
}