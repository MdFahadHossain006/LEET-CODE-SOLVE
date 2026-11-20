class Solution(object):
    def maxArea(self, height):
        """
        :type height: List[int]
        :rtype: int
        """
        left = 0
        right = len(height) - 1
        max_water = 0

        while left < right:
            width = right - left
            if height[left] < height[right]:
                max_water = max(max_water, height[left] * width)
                left += 1
            else:
                max_water = max(max_water, height[right] * width)
                right -= 1

        return max_water