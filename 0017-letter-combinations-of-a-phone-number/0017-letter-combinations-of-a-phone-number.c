#include <stdlib.h>
#include <string.h>

static const char *KEYPAD[10] = {
    "",     // 0
    "",     // 1
    "abc",  // 2
    "def",  // 3
    "ghi",  // 4
    "jkl",  // 5
    "mno",  // 6
    "pqrs", // 7
    "tuv",  // 8
    "wxyz"  // 9
};

static void backtrack(
    const char *digits,
    int len,
    int index,
    char *current,
    char **result,
    int *count
) {
    if (index == len) {
        current[len] = '\0';
        result[*count] = (char *)malloc((len + 1) * sizeof(char));
        strcpy(result[*count], current);
        (*count)++;
        return;
    }

    const char *letters = KEYPAD[digits[index] - '0'];
    int num_letters = (int)strlen(letters);

    for (int i = 0; i < num_letters; i++) {
        current[index] = letters[i];
        backtrack(digits, len, index + 1, current, result, count);
    }
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char **letterCombinations(char *digits, int *returnSize) {
    *returnSize = 0;
    if (digits == NULL || digits[0] == '\0') {
        return NULL;
    }

    int len = (int)strlen(digits);
    int total = 1;
    for (int i = 0; i < len; i++) {
        total *= (int)strlen(KEYPAD[digits[i] - '0']);
    }

    char **result = (char **)malloc((size_t)total * sizeof(char *));
    char *current = (char *)malloc((size_t)(len + 1) * sizeof(char));
    int count = 0;

    backtrack(digits, len, 0, current, result, &count);

    free(current);
    *returnSize = count;
    return result;
}