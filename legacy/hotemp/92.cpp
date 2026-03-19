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
    /**
     * @brief 反转链表中从位置 left 到 right 的局部区间
     *
     * 本算法采用“头插法”实现原地局部反转，只需一次遍历。
     * 通过固定 pre 和 cur 指针，不断将 cur 随后的 next 节点剔除并插入到 pre
     * 后面。
     *
     * @param head 链表的头节点指针
     * @param left 反转区间的起始位置（从 1 开始计数）
     * @param right 反转区间的结束位置
     * @return ListNode* 反转后的新链表头节点指针
     *
     * @note 核心头插法单步变换演示 (以反转 2->3->4 区间中的 3 为例):
     * @code
     *    初始状态:
     *      pre     cur    next
     *     [1] ->  [2] ->  [3] ->  [4]
     *      |               ^
     *      +---------------+ (即将把 3 移到 pre 后面)
     *
     *    步骤 1: cur->next = next->next (2 指向 4)
     *      pre     cur            next
     *     [1] ->  [2] --------->  [4]
     *                      [3] ----+
     *
     *    步骤 2: next->next = pre->next (3 指向 2)
     *      pre     cur            next
     *     [1] ->  [2] --------->  [4]
     *              ^               |
     *              +----- [3] -----+
     *
     *    步骤 3: pre->next = next (1 指向 3)
     *      pre    next     cur
     *     [1] ->  [3] ->  [2] ->  [4]
     * @endcode
     */
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
        ListNode* ans = dummy->next;
        delete dummy;
        return ans;
    }
};

/**
 * @brief 根据传入的整型 vector 数组动态构建一个单链表
 *
 * @param nums 包含节点数值的非负序列
 * @return ListNode* 生成的单链表头指针，若数组为空则返回 nullptr
 *
 * @code
 *    输入: {1, 2, 3}
 *    构建过程: dummy -> [1] -> [2] -> [3] -> nullptr
 *    返回: [1] 的地址
 * @endcode
 */
ListNode* createList(const vector<int>& nums) {
    ListNode dummy(0);
    ListNode* cur = &dummy;

    for (int x : nums) {
        cur->next = new ListNode(x);
        cur = cur->next;
    }

    return dummy.next;
}

/**
 * @brief 打印单链表结构到标准输出流
 *
 * @param head 链表头节点指针
 *
 * @code
 *    输出格式示例: 1 -> 2 -> 3 -> nullptr
 * @endcode
 */
void printList(ListNode* head) {
    ListNode* cur = head;
    while (cur) {
        cout << cur->val << (cur->next ? " -> " : "");
        cur = cur->next;
    }

    cout << " -> nullptr" << endl;
}

/**
 * @brief 递归或循环销毁堆上分配的链表内存，防止内存泄漏
 *
 * @param head 待释放链表的头节点指针
 *
 * @attention 释放后，传入的外部原生指针会变成野指针，建议在调用后手动置为
 * nullptr
 */
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