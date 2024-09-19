class Solution:
    def search(self, nums, target):

        if target not in nums:
            return -1

        left, right = 0, len(nums) - 1
        while(left <= right):
            mid = (left + right) // 2

            if target == nums[mid]:
                break

            if (nums[mid] < nums[0]) :
                if nums[mid] < target:
                    right -= 1
                else:
                    right = mid - 1
            else:
                if nums[mid] < target:
                    left += 1
                else:
                    left = mid + 1
        return mid

print(Solution().search(
    nums = [0, 1], target = 1
))