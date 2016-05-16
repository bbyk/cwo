#include <iostream>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;

    ListNode(int x) : val(x), next(NULL) { }
};

class Solution {
public:
    bool isPalindrome(ListNode *head) {
        // trivial cases
        if (NULL == head || NULL == head->next) {
            return true;
        }

        // find the center of the list
        ListNode *slow = head, *fast = head;
        while (NULL != fast->next && NULL != fast->next->next) {
            slow = slow->next;
            fast = fast->next->next;
        }

        slow = slow->next;
        // reverse the other half
        ListNode *prev = NULL;
        while (NULL != slow->next) {
            ListNode *next = slow->next;
            slow->next = prev;
            prev = slow;
            slow = next;
        }

        slow->next = prev;
        fast = head;
        while (NULL != slow) {
            if (slow->val != fast->val) {
                return false;
            }
            slow = slow->next;
            fast = fast->next;
        }

        // compare the halves
        return true;
    }
};

int main() {
    Solution solution;
    ListNode head(1);
    ListNode second(2);
    ListNode third(2);
    ListNode forth(1);

    // 1. trivial case
    cout << "Is palindrome (true): " << solution.isPalindrome(&head) << endl;
    // 2. even number
    head.next = &second;
    cout << "Is palindrome (false): " << solution.isPalindrome(&head) << endl;
    second.next = &third;
    cout << "Is palindrome (false): " << solution.isPalindrome(&head) << endl;
    third.val = 1;
    cout << "Is palindrome (true): " << solution.isPalindrome(&head) << endl;
    third.val = 2;
    third.next = &forth;
    cout << "Is palindrome (true): " << solution.isPalindrome(&head) << endl;
    return 0;
}