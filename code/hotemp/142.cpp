#include <iostream>
#include <unordered_set>

using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    ListNode* detectCycle(ListNode* head) {
        if (head == nullptr) {
            return nullptr;
        }

        unordered_set<ListNode*> uset;

        while (head != nullptr) {
            if (uset.count(head)) {
                return head;
            }
            uset.insert(head);
            head = head->next;
        }

        return nullptr;
    }
};