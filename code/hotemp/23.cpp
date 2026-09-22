#include <algorithm>
#include <queue>

using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        auto cmp = [](const ListNode* a, const ListNode* b) {
            return a->val > b->val;
        };

        priority_queue<ListNode*, vector<ListNode*>, decltype(cmp)> pq(cmp);

        for (int i = 0; i < lists.size(); i++) {
            if (lists[i] != nullptr) {
                pq.push(lists[i]);
            }
        }

        ListNode dummy(0);
        ListNode* res = &dummy;

        while (!pq.empty()) {
            ListNode* temp = pq.top();
            pq.pop();

            res->next = temp;

            res = res->next;
            temp = temp->next;
            if (temp != nullptr) {
                pq.push(temp);
            }
        }

        return dummy.next;
    }
};