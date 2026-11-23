#include <stdlib.h>
#include <string.h>

int longestValidParentheses(char* s) {
    int n = (int)strlen(s);
    if (n == 0) return 0;

    int* stack = (int*)malloc((size_t)(n + 1) * sizeof(int));
    int top = -1;
    stack[++top] = -1; // Base boundary index

    int max_len = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] == '(') {
            stack[++top] = i;
        } else {
            top--; // Pop matching '(' or previous boundary
            if (top == -1) {
                stack[++top] = i; // New invalid boundary
            } else {
                int len = i - stack[top];
                if (len > max_len) {
                    max_len = len;
                }
            }
        }
    }

    free(stack);
    return max_len;
}