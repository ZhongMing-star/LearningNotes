class Solution:
    def minSubArrayLen(self, target, nums) -> int:
        n = len(nums)
        ans = n + 1
        s = 0
        left = 0
        for right, x in enumerate(nums):
            s += x
            while(s - nums[left] >= target):
                s -= nums[left]
                left += 1
            if s >= target:
                ans = min(ans, right - left + 1)
        return ans if ans != n+1 else 0
        
    
print(Solution().minSubArrayLen(
    target = 11, nums =[1,2,3,4,5]
))
