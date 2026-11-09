class Solution(object):
    def myAtoi(self, s):
        """:type s: str
        :rtype: int
        """
        if not s:
            return 0
        
        # Step 1: Remove leading whitespaces
        s = s.lstrip()
        if not s:
            return 0
        
        # Step 2: Check for sign
        sign = 1
        start = 0
        if s[0] == '-':
            sign = -1
            start = 1
        elif s[0] == '+':
            start = 1
            
        # Step 3: Convert digits
        res = 0
        for i in range(start, len(s)):
            if not s[i].isdigit():
                break
            res = res * 10 + int(s[i])
            
        # Apply sign
        res *= sign
        
        # Step 4: Handle 32-bit signed integer overflow limits
        INT_MIN, INT_MAX = -2**31, 2**31 - 1
        if res < INT_MIN:
            return INT_MIN
        if res > INT_MAX:
            return INT_MAX
            
        return res