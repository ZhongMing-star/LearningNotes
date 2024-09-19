class Solution:
    def minOperations(self, nums, x):
        temp_sum, n  = 0, len(nums)

        min_length, temp_sum = 1e9, 0
        for right, num in enumerate(nums):
            left = 0
            copy_temp = temp_sum
            while( n - left - 1 > right and copy_temp < x):
                copy_temp += nums[n - left - 1]
                left += 1
            
            if copy_temp == x:
                min_length = min(min_length, right + left)

            temp_sum += num
            if temp_sum > x :
                break
            if temp_sum == x:
                return min(right + 1, min_length)
        return min_length if min_length != 1e9 else -1

print(Solution().minOperations(
    # nums = [8828,9581,49,9818,9974,9869,9991,10000,10000,10000,9999,9993,9904,8819,1231,6309], x = 134365
    nums=[1,1,3,2,5], x=5
))
            
