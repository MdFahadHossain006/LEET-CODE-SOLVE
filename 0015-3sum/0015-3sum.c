#include <stdlib.h>

static int compare_ints(const void* a, const void* b) {
    int x = *(const int*)a;
    int y = *(const int*)b;
    if (x < y) return -1;
    if (x > y) return 1;
    return 0;
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** threeSum(int* nums, int numsSize, int* returnSize, int** returnColumnSizes) {
    *returnSize = 0;
    *returnColumnSizes = NULL;

    if (nums == NULL || numsSize < 3) {
        return NULL;
    }

    qsort(nums, (size_t)numsSize, sizeof(int), compare_ints);

    int capacity = 64;
    int** result = (int**)malloc((size_t)capacity * sizeof(int*));
    int* col_sizes = (int*)malloc((size_t)capacity * sizeof(int));
    if (result == NULL || col_sizes == NULL) {
        free(result);
        free(col_sizes);
        return NULL;
    }

    for (int i = 0; i < numsSize - 2; i++) {
        // Since nums is sorted, no triplet can start with a positive number and sum to 0
        if (nums[i] > 0) {
            break;
        }

        // Skip duplicate first elements
        if (i > 0 && nums[i] == nums[i - 1]) {
            continue;
        }

        int left = i + 1;
        int right = numsSize - 1;

        while (left < right) {
            long long sum = (long long)nums[i] + (long long)nums[left] + (long long)nums[right];

            if (sum == 0) {
                if (*returnSize == capacity) {
                    capacity *= 2;
                    int** new_result = (int**)realloc(result, (size_t)capacity * sizeof(int*));
                    int* new_cols = (int*)realloc(col_sizes, (size_t)capacity * sizeof(int));
                    if (new_result == NULL || new_cols == NULL) {
                        free(new_result ? new_result : result);
                        free(new_cols ? new_cols : col_sizes);
                        return NULL;
                    }
                    result = new_result;
                    col_sizes = new_cols;
                }

                int* triplet = (int*)malloc(3 * sizeof(int));
                if (triplet == NULL) {
                    return NULL;
                }
                triplet[0] = nums[i];
                triplet[1] = nums[left];
                triplet[2] = nums[right];

                result[*returnSize] = triplet;
                col_sizes[*returnSize] = 3;
                (*returnSize)++;

                left++;
                right--;

                // Skip duplicate left and right values
                while (left < right && nums[left] == nums[left - 1]) {
                    left++;
                }
                while (left < right && nums[right] == nums[right + 1]) {
                    right--;
                }
            } else if (sum < 0) {
                left++;
            } else {
                right--;
            }
        }
    }

    // Shrink arrays to exact *returnSize (or free if empty)
    if (*returnSize == 0) {
        free(result);
        free(col_sizes);
        *returnColumnSizes = NULL;
        return NULL;
    }

    int** trimmed_result = (int**)realloc(result, (size_t)(*returnSize) * sizeof(int*));
    int* trimmed_cols = (int*)realloc(col_sizes, (size_t)(*returnSize) * sizeof(int));
    result = trimmed_result ? trimmed_result : result;
    col_sizes = trimmed_cols ? trimmed_cols : col_sizes;

    *returnColumnSizes = col_sizes;
    return result;
}