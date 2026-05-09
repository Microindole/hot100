#include <iostream>
#include <vector>

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
    ListNode* reverseBetween(ListNode* head, int left, int right) {
        ListNode* dummy = new ListNode(0);
        dummy->next = head;
        ListNode* pre = dummy;

        for (int i = 0; i < left - 1; i++) {
            pre = pre->next;
        }

        ListNode* cur = pre->next;
        ListNode* next;

        for (int i = 0; i < right - left; i++) {
            next = cur->next;
            cur->next = next->next;
            next->next = pre->next;
            pre->next = next;
        }

        return dummy->next;
    }
};

ListNode* createList(const vector<int>& nums) {
    ListNode dummy(0);
    ListNode* cur = &dummy;

    for (int x : nums) {
        cur->next = new ListNode(x);
        cur = cur->next;
    }

    return dummy.next;
}

void printList(ListNode* head) {
    ListNode* cur = head;
    while (cur) {
        cout << cur->val << (cur->next ? " -> " : "");
        cur = cur->next;
    }

    cout << " -> nullptr" << endl;
}

void deleteList(ListNode* head) {
    while (head) {
        ListNode* temp = head;
        head = head->next;
        delete temp;
    }
}

int main() {
    int n, val;
    while (cin >> n) {
        vector<int> nums;

        for (int i = 0; i < n; i++) {
            cin >> val;
            nums.push_back(val);
        }

        ListNode* head = createList(nums);

        Solution so;
        ListNode* result = so.reverseBetween(head, 2, 4);

        printList(result);

        deleteList(result);
    }

    return 0;
}