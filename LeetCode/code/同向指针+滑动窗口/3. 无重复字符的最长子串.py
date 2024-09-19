class Solution:
    def lengthOfLongestSubstring(self, s):

        max_length, L = -1, 0
        for right, x in enumerate(s):
            while(x in s[L:right]):
                L += 1
            max_length = max(max_length, right - L + 1)
        return max_length
    
print(Solution().lengthOfLongestSubstring(
    'abcabcbb'
))