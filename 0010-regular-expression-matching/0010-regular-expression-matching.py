class Solution(object):
    def isMatch(self, s, p):
        """
        :type s: str
        :type p: str
        :rtype: bool
        """
        m, n = len(s), len(p)
        # dp[i][j] means s[0...i-1] matches p[0...j-1]
        dp = [[False] * (n + 1) for _ in range(m + 1)]
        
        # Empty string and empty pattern match
        dp[0][0] = True
        
        # Handle patterns with '*' matching empty string (e.g., a*, a*b*)
        for j in range(2, n + 1):
            if p[j - 1] == '*':
                dp[0][j] = dp[0][j - 2]
                
        for i in range(1, m + 1):
            for j in range(1, n + 1):
                if p[j - 1] == s[i - 1] or p[j - 1] == '.':
                    dp[i][j] = dp[i - 1][j - 1]
                elif p[j - 1] == '*':
                    # Zero occurrences of preceding element
                    dp[i][j] = dp[i][j - 2]
                    # One or more occurrences if preceding element matches s[i-1]
                    prev_char = p[j - 2]
                    if prev_char == s[i - 1] or prev_char == '.':
                        dp[i][j] = dp[i][j] or dp[i - 1][j]
                        
        return dp[m][n] 