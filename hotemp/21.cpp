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
     * @brief 将两个升序链表合并为一个新的升序链表并返回。
     *
     * 算法核心：通过双指针同步遍历两个链表，每次挑选较小值的节点挂载到
     * 结果链表的末尾。当某一个链表遍历完毕时，直接将另一个链表的剩余
     * 完整段拼接上去（因为剩余段本身已是有序的）。
     *
     * 链表“拉链式”合并图示：
     *
     *   list1:  1 ------> 2 ------> 4
     *           ↑
     *   list2:  1 ------> 3 ------> 4
     *           ↑
     *   -------------------------------------------------
     *   dummy -> [1] -> [1] -> [2] -> [3] -> 剩余的 list1/list2 整体拼接
     *             ↑
     *            tail (指针线性向后移动)
     *
     * @param list1 升序链表1的头指针
     * @param list2 升序链表2的头指针
     * @return ListNode* 合并后的新升序链表头指针
     *
     * @complexity
     * - 时间复杂度: O(N + M) - N 和 M 分别为两链表的长度，
     *   最多遍历所有节点一次。
     * - 空间复杂度: O(1) - 仅改变指针指向，未创建新节点，消耗常数辅助空间。
     */
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        ListNode dummy(0);
        ListNode* tail = &dummy;

        while (list1 != nullptr && list2 != nullptr) {
            if (list1->val <= list2->val) {
                tail->next = list1;
                list1 = list1->next;
            } else {
                tail->next = list2;
                list2 = list2->next;
            }
            tail = tail->next;
        }

        tail->next = (list1 != nullptr) ? list1 : list2;

        return dummy.next;
    }
};