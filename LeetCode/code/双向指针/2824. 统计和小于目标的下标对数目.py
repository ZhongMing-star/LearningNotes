# 解法1 
# class Solution:
#     def countPairs(self, nums, target):
#         count, n = 0, len(nums)
#         nums.sort()
#         for i in range(0, n):
#             for j in range(i+1, n):
#                 if (nums[i] + nums[j]) < target:
#                     count += 1
#                 else:
#                     break
#         return count

# 解法2 
class Solution:
    def countPairs(self, nums, target):
        count, n = 0, len(nums)
        nums.sort()
        for i in range(0, n):
            for j in range(n-1, i, -1):
                if (nums[i] + nums[j] < target):
                    count += j - i 
                    break
        return count 

print(Solution().countPairs(
    nums = [-5,0,-7,-1,9,8,-9,9], target = -14
))