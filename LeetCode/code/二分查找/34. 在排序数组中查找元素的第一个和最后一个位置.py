class Solution:
    def searchRange(self, nums, target):
        left, right = 0, len(nums) -1
        while(left <= right):
            mid =  (left + right) // 2
            if nums[mid] == target:
                l, r = mid, mid
                while(l > 0): 
                    if nums[l-1] == target: l -= 1
                    else : break
                while(r < len(nums) - 1) :
                    if nums[r+1] == target: r += 1
                    else : break
                return (l, r)
            elif nums[mid] < target:
                left = mid + 1
            else:
                right = mid - 1
        return (-1, -1)

print(Solution().searchRange(
    nums = [1], target = 1
))