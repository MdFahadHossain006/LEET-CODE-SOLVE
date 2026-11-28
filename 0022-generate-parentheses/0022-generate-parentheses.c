#include <stdlib.h>
#include <string.h>

static void backtrack(
    int n,
    int open,
    int close,
    char* current,
    int pos,
    char*** result,
    int* count,
    int* capacity
) {
    if (pos == 2 * n) {
        if (*count == *capacity) {
            *capacity *= 2;
            *result = (char**)realloc(*result, (*capacity) * sizeof(char*));
        }
        current[pos] = '\0';
        (*result)[*count] = (char*)malloc((2 * n + 1) * sizeof(char));
        strcpy((*result)[*count], current);
        (*count)++;
        return;
    }

    if (open < n) {
        current[pos] = '(';
        backtrack(n, open + 1, close, current, pos + 1, result, count, capacity);
    }

    if (close < open) {
        current[pos] = ')';
        backtrack(n, open, close + 1, current, pos + 1, result, count, capacity);
    }
}

char** generateParenthesis(int n, int* returnSize) {
    int capacity = 16;
    int count = 0;
    char** result = (char**)malloc(capacity * sizeof(char*));
    char* current = (char*)malloc((2 * n + 1) * sizeof(char));

    backtrack(n, 0, 0, current, 0, &result, &count, &capacity);

    free(current);
    *returnSize = count;
    return result;
}