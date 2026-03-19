#include <iostream>
#include <unordered_map>

using namespace std;

class Node {
public:
    int val;
    Node* next;
    Node* random;

    Node(int _val) {
        val = _val;
        next = nullptr;
        random = nullptr;
    }
};

class Solution {
public:
    Node* copyRandomList(Node* head) {
        if (head == nullptr) {
            return nullptr;
        }

        Node* tempHead = head;
        unordered_map<Node*, Node*> f;

        Node* res = new Node(tempHead->val);
        f[tempHead] = res;
        Node* tempRes = res;

        tempHead = tempHead->next;

        while (tempHead != nullptr) {
            tempRes->next = new Node(tempHead->val);

            f[tempHead] = tempRes->next;

            tempHead = tempHead->next;
            tempRes = tempRes->next;
        }

        tempHead = head;
        tempRes = res;

        while (tempHead != nullptr) {
            tempRes->random = f[tempHead->random];

            tempHead = tempHead->next;
            tempRes = tempRes->next;
        }

        return res;
    }
};