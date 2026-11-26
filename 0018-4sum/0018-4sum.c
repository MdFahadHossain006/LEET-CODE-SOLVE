#include <stdlib.h>

static int cmp_int(const void *a, const void *b) {
    int x = *(const int *)a;
    int y = *(const int *)b;
    if (x < y) return -1;
    if (x > y) return 1;
    return 0;
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** fourSum(int* nums, int numsSize, int target, int* returnSize, int** returnColumnSizes) {
    *returnSize = 0;
    *returnColumnSizes = NULL;

    if (nums == NULL || numsSize < 4) {
        return NULL;
    }

    qsort(nums, (size_t)numsSize, sizeof(int), cmp_int);

    int capacity = 64;
    int **ans = (int **)malloc((size_t)capacity * sizeof(int *));
    int *col_sizes = (int *)malloc((size_t)capacity * sizeof(int));
    int count = 0;
    long long target_ll = (long long)target;

    for (int i = 0; i < numsSize - 3; i++) {
        if (i > 0 && nums[i] == nums[i - 1]) {
            continue;
        }

        // Pruning for index i
        long long min_i = (long long)nums[i] + nums[i + 1] + nums[i + 2] + nums[i + 3];
        if (min_i > target_ll) {
            break;
        }
        long long max_i = (long long)nums[i] + nums[numsSize - 1] + nums[numsSize - 2] + nums[numsSize - 3];
        if (max_i < target_ll) {
            continue;
        }

        for (int j = i + 1; j < numsSize - 2; j++) {
            if (j > i + 1 && nums[j] == nums[j - 1]) {
                continue;
            }

            // Pruning for index j
            long long min_j = (long long)nums[i] + nums[j] + nums[j + 1] + nums[j + 2];
            if (min_j > target_ll) {
                break;
            }
            long long max_j = (long long)nums[i] + nums[j] + nums[numsSize - 1] + nums[numsSize - 2];
            if (max_j < target_ll) {
                continue;
            }

            int left = j + 1;
            int right = numsSize - 1;

            while (left < right) {
                long long sum = (long long)nums[i] + nums[j] + nums[left] + nums[right];

                if (sum == target_ll) {
                    if (count == capacity) {
                        capacity *= 2;
                        int **new_ans = (int **)realloc(ans, (size_t)capacity * sizeof(int *));
                        int *new_cols = (int *)realloc(col_sizes, (size_t)capacity * sizeof(int));
                        if (!new_ans || !new_cols) {
                            free(new_ans ? new_ans : ans);
                            free(new_cols ? new_cols : col_sizes);
                            *returnSize = 0;
                            return NULL;
                        }
                        ans = new_ans;
                        col_sizes = new_cols;
                    }

                    int *quad = (int *)malloc(4 * sizeof(int));
                    quad[0] = nums[i];
                    quad[1] = nums[j];
                    quad[2] = nums[left];
                    quad[3] = nums[right];

                    ans[count] = quad;
                    col_sizes[count] = 4;
                    count++;

                    int prev_left = nums[left];
                    int prev_right = nums[right];
                    while (left < right && nums[left] == prev_left) {
                        left++;
                    }
                    while (left < right && nums[right] == prev_right) {
                        right--;
                    }
                } else if (sum < target_ll) {
                    left++;
                } else {
                    right--;
                }
            }
        }
    }

    *returnSize = count;
    *returnColumnSizes = col_sizes;
    return ans;
}