class Solution:
    def trap(self, height):
        n = len(height)
        R, L, min_value, = 0, n-1, 1e9
        max_R, max_L = height[R], height[L]
        area_sum = 0
        while(R < L):
            max_R = max(max_R, height[R])
            max_L = max(max_L, height[L])
            if max_R < max_L:
                area_sum += max_R - height[R]
                R += 1
            else:
                area_sum += max_L - height[L]
                L -= 1
        return area_sum

# class Solution:
#     def trap(self, height) -> int:
#         max_left, max_right = height.copy(), height.copy()
#         n = len(height)

#         for i in range(1, n):
#             max_left[i]  = max(max_left[i-1], height[i-1])
        
#         for i in range(n-2, -1, -1):
#             max_right[i] = max(max_right[i+1], height[i+1])

#         res = 0
#         for i in range(n):
#             min_value = min(max_left[i], max_right[i])
#             if min_value > height[i]:
#                 res += min_value - height[i]
#         return res 


print(Solution().trap(
    [0,1,0,2,1,0,1,3,2,1,2,1]
))