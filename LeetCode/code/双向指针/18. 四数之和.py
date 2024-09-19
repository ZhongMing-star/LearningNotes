class Solution:
    def fourSum(self, nums, target):
        res = []
        nums_length = len(nums)

        nums.sort()
        for i in range(0, nums_length):
            if (i > 0 and nums[i] == nums[i-1]):
                continue

            for j in range(i+1, nums_length):
                if (j > i + 1 and j + 1 <= nums_length - 1 and  nums[j] == nums[j-1]):
                    continue

                R = j + 1
                L = nums_length - 1
                while(R < L):
                    temp_sum = nums[i] + nums[j] + nums[R] + nums[L]
                    if temp_sum == target:
                        res.append([nums[i], nums[j], nums[R], nums[L]])

                        while(R < L and nums[R] == nums[R+1]):
                            R += 1
                        R += 1
                        
                        while(R < L and nums[L] == nums[L-1]):
                            L -= 1
                        L -= 1

                    elif temp_sum < target:
                        while(R < L and nums[R] == nums[R+1]):
                            R += 1
                        R += 1
                    else:
                        while(R<L and nums[L] == nums[L-1]):
                            L -= 1
                        L -= 1
        return res 

print(
    Solution().fourSum(
        [2, 2, 2, 2, 2], target=8
    )
)