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
    ListNode* reverseKGroup(ListNode* head, int k) {
        ListNode dummy(0);
        dummy.next = head;

        ListNode* prev = &dummy;

        while (true) {
            // a = 当前组第一个节点
            ListNode* a = prev->next;
            if (a == nullptr) {
                break;
            }

            // b = 下一组第一个节点
            ListNode* b = a;
            for (int i = 0; i < k; i++) {
                if (b == nullptr) {
                    return dummy.next;
                }
                b = b->next;
            }

            // 把 a 后面的节点一个个插到 prev 后面
            while (a->next != b) {
                ListNode* curr = a->next;

                a->next = curr->next;
                curr->next = prev->next;
                prev->next = curr;
            }

            // a 已经变成当前组最后一个节点
            prev = a;
        }

        return dummy.next;
    }
};