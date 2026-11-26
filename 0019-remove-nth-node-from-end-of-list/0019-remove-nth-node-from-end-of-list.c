#include <stdlib.h>

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* removeNthFromEnd(struct ListNode* head, int n) {
    if (head == NULL || n <= 0) {
        return head;
    }

    struct ListNode dummy;
    dummy.val = 0;
    dummy.next = head;

    struct ListNode *fast = &dummy;
    struct ListNode *slow = &dummy;

    // Move fast ahead by n steps so there is an n-node gap
    for (int i = 0; i < n; i++) {
        if (fast->next == NULL) {
            return head;
        }
        fast = fast->next;
    }

    // Advance both pointers until fast reaches the tail node
    while (fast->next != NULL) {
        fast = fast->next;
        slow = slow->next;
    }

    // Remove the nth node from the end and free its memory
    struct ListNode *to_delete = slow->next;
    slow->next = to_delete->next;
    free(to_delete);

    return dummy.next;
}