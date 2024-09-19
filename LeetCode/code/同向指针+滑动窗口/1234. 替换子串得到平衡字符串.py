from collections import Counter


class Solution:
    def balancedString(self, s):
        count, n = Counter(s), len(s)
        m = n // 4

        if all(count[x] == m for x in 'QWER'):
            return 0
        
        min_length, left = 1e9, 0
        for right, x in enumerate(s):
            count[x] -= 1
            while(all(count[i] <= m for i in 'QWER')):
                min_length = min(min_length, right - left + 1)
                count[s[left]] +=1
                left += 1
        return min_length


print(Solution().balancedString(
    'QWER'
))                
            