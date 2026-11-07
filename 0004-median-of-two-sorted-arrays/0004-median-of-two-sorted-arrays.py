class Solution:
    def findMedianSortedArrays(self, nums1: list[int], nums2: list[int]) -> float:
        # Ensure nums1 is the smaller array to minimize the binary search range
        if len(nums1) > len(nums2):
            nums1, nums2 = nums2, nums1
            
        m, n = len(nums1), len(nums2)
        low, high = 0, m
        half_len = (m + n + 1) // 2
        
        while low <= high:
            i = (low + high) // 2
            h = half_len
            j = half_len - i
            
            # Boundaries for partitions
            left_1 = float('-inf') if i == 0 else nums1[i - 1]
            right_1 = float('inf') if i == m else nums1[i]
            
            left_2 = float('-inf') if j == 0 else nums2[j - 1]
            right_2 = float('inf') if j == n else nums2[j]
            
            # Check if we have partitioned correctly
            if left_1 <= right_2 and left_2 <= right_1:
                # If total elements are odd
                if (m + n) % 2 == 1:
                    return float(max(left_1, left_2))
                # If total elements are even
                return (max(left_1, left_2) + min(right_1, right_2)) / 2.0
            elif left_1 > right_2:
                high = i - 1  # Move too far right in nums1, shift left
            else:
                low = i + 1   # Move too far left in nums1, shift right