class Solution(object):
    def generateParenthesis(self, n):
        """
        :type n: int
        :rtype: List[str]
        """
        result = []

        def backtrack(current, open_count, close_count):
            # Base case: 2 * n characters placed
            if len(current) == 2 * n:
                result.append("".join(current))
                return

            # Choice 1: Add '(' if we still have open parentheses available
            if open_count < n:
                current.append("(")
                backtrack(current, open_count + 1, close_count)
                current.pop()

            # Choice 2: Add ')' only if it won't exceed open parentheses
            if close_count < open_count:
                current.append(")")
                backtrack(current, open_count, close_count + 1)
                current.pop()

        backtrack([], 0, 0)
        return result