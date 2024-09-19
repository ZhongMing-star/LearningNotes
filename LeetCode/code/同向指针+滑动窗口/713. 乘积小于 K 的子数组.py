class Solution:
    def numSubarrayProductLessThanK(self, nums, k):
        
        if k <=1:
            return 0
        prod, count, L = 1, 0, 0
        for index, num in enumerate(nums):
            prod *= num 
            while(prod>= k):
                prod /= nums[L]
                L += 1
            count += index - L + 1
        return count

print(Solution().numSubarrayProductLessThanK(
    nums = [1,2,3], k = 0
))

            