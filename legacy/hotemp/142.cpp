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
        unordered_set<ListNode*> visited;
        ListNode* curr = head;

        while (curr != nullptr) {
            if (visited.count(curr)) {
                return curr;
            }

            visited.insert(curr);
            curr = curr->next;
        }

        return nullptr;
    }
};