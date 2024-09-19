class Solution:
    def maxArea(self, height):
        n = len(height)
        R, L = 0, n - 1
        area = -1
        while(R < L):
            if height[R] < height[L]:
                area = max(area, height[R]*(L-R))
                R += 1
            else:
                area = max(area, height[L]*(L-R))
                L -= 1
        return area
    
print(Solution().maxArea(
    [1,8,6,2,5,4,8,3,7]
))