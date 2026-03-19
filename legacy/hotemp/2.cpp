#include <iostream>

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
     * @brief 逆序存储的两个非负整数链表相加。
     *
     * 算法模拟经典竖式加法，从个位（链表头）开始逐位相加，并动态维护进位 add。
     * 引入哑节点（Dummy Head）作为辅助头节点，避免对首个节点的特殊处理。
     *
     * 链表对齐与按位加法图示 (例如: 342 + 465 = 807)：
     *
     *   l1:     2 -> 4 -> 3   (逆序表示 342)
     *   l2:     5 -> 6 -> 4   (逆序表示 465)
     *          -----------
     *   相加:   7   10    7
     *   进位:   0    1    0   (add 变量动态传递)
     *          -----------
     *   结果:   7 -> 0 -> 8   (逆序表示 807)
     *
     * @param l1 指向第一个非负整数链表的头指针
     * @param l2 指向第二个非负整数链表的头指针
     * @return ListNode* 相加后新链表的真正头指针
     *
     * @complexity
     * - 时间复杂度: O(max(M, N)) - M 和 N 为两链表长度，只需遍历最长链表一次。
     * - 空间复杂度: O(1) - 除去存储返回结果的链表外，仅消耗常数级别指针。
     */
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode dummy(0);
        ListNode* tail = &dummy;

        int add = 0;

        // 只要 l1、l2 未走完，或者最后仍有进位没加完，循环就必须继续
        while (l1 != nullptr || l2 != nullptr || add != 0) {
            int sum = add;

            if (l1 != nullptr) {
                sum += l1->val;
                l1 = l1->next;
            }

            if (l2 != nullptr) {
                sum += l2->val;
                l2 = l2->next;
            }

            add = sum / 10;

            // 按需实时创建新节点，彻底杜绝悬空指针和多余的零节点
            tail->next = new ListNode(sum % 10);
            tail = tail->next;
        }

        return dummy.next;
    }
};