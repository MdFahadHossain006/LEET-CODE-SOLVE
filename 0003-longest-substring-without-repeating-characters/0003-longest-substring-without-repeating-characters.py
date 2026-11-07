class Solution:
    def lengthOfLongestSubstring(self, s: str) -> int:
        char_index_map = {}
        max_len = 0
        left = 0
        
        for right in range(len(s)):
            char = s[right]
            
            # If the character is already in the window, shift the left pointer 
            # to one position past its previous occurrence.
            if char in char_index_map and char_index_map[char] >= left:
                left = char_index_map[char] + 1
                
            # Update the character's latest position and compute max length
            char_index_map[char] = right
            max_len = max(max_len, right - left + 1)
            
        return max_len 