#include <algorithm>

using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

/*

 prev -> 1 -> 2 -> 3 -> 4 -> 5 -> 6 -> 7 -> 8 -> nullptr;

*/

class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        ListNode dummy(0);
        ListNode* prev = &dummy;
        prev->next = head;

        while (prev->next != nullptr && prev->next->next != nullptr) {
            ListNode *first = prev->next, *second = prev->next->next;

            prev->next = second;
            first->next = second->next;
            second->next = first;

            prev = prev->next->next;
        }

        return dummy.next;
    }
};