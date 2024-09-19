class Solution:
    def findMin(self, nums):
        left, right = 0, len(nums) - 1
        while(left < right):
            mid = (left + right)//2
            if nums[mid] < nums[right]:
                right = mid
            else:
                left += 1
        return nums[left]
       