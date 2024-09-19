class Solution:
    def threeSumClosest(self, nums, target):
        i = 0
        res = []
        nums.sort()
        min_value = 1e9
        while(i < len(nums)-2):
            L, R = i + 1, len(nums) - 1
            while(L < R):
                temp_sum = nums[i] + nums[L] + nums[R]

                if abs(temp_sum - target) < min_value:
                    min_value = abs(temp_sum - target)
                    res = temp_sum
                
                if temp_sum - target > 0:
                    R -= 1
                elif temp_sum - target < 0:
                    L += 1
                else:
                    return temp_sum

            i += 1
        return res

print(Solution().threeSumClosest(
    [-1,2,1,-4], 1
))