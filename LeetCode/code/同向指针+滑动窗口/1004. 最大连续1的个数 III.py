class Solution:
    def longestOnes(self, nums, k):
        left, max_length, used_k = 0, 0, 0
        for right, x in enumerate(nums):
            used_k += 1 - x
            while used_k > k:
                used_k -= 1 - nums[left]
                left += 1
            max_length = max(max_length, right - left + 1)
        return max_length

print(Solution().longestOnes(
    nums = [0,0,1,1,0,0,1,1,1,0,1,1,0,0,0,1,1,1,1], k = 3
))