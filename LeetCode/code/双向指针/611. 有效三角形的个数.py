class Solution:
    def triangleNumber(self, nums):
        n = len(nums)
        nums.sort()
        count = 0

        for i in range(n - 2):
            for j in range(i+1, n - 1):
                for k in range(j+1, n):
                    if (nums[i] + nums[j] > nums[k]):
                        count += 1
                    if (nums[i] + nums[j] <= nums[k]):
                        break
        return count
    
print(Solution().triangleNumber(
    nums = [2,2,3,4]
))


