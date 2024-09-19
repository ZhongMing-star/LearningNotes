
class Solution:
    def threeSum(self, nums):
        if len(nums) < 2:
            return []
    
        i = 0
        res = []
        nums.sort()
        while(i<len(nums)):

            if nums[i] >0:
                break

            L, R = i + 1, len(nums) - 1
            while(L < R):
                if (nums[i] + nums[R] + nums[L] == 0):
                    res.append([nums[i], nums[R], nums[L]])
                    while(L < R and nums[L] == nums[L + 1]):
                        L += 1
                    while(L < R and nums[R] == nums[R - 1]):
                        R -= 1
                    L += 1
                    R -= 1
                elif (nums[i] + nums[R] + nums[L] < 0):
                    L += 1
                else:
                    R -= 1

            i += 1
        return res

print(Solution().threeSum(
    [0, 0, 0, 0]
))
