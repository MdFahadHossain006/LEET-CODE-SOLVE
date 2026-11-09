class Solution:
    def longestPalindrome(self, s: str) -> str:
        if not s:
            return ""
        
        start, max_len = 0, 0
        
        def expand_from_center(left: int, right: int) -> int:
            while left >= 0 and right < len(s) and s[left] == s[right]:
                left -= 1
                right += 1
            # Return the length of the palindrome
            return right - left - 1

        for i in range(len(s)):
            # Odd length palindromes (e.g., "aba")
            len1 = expand_from_center(i, i)
            # Even length palindromes (e.g., "abba")
            len2 = expand_from_center(i, i + 1)
            
            curr_len = max(len1, len2)
            if curr_len > max_len:
                max_len = curr_len
                # Calculate the starting index of the longest palindrome
                start = i - (curr_len - 1) // 2
                
        return s[start:start + max_len]