#include <unordered_map>

using namespace std;

class Node {
public:
    int val;
    Node* next;
    Node* random;

    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};

class Solution {
public:
    Node* copyRandomList(Node* head) {
        if (head == nullptr) {
            return nullptr;
        }

        unordered_map<Node*, Node*> umap;

        Node* curr = head;
        umap[curr] = new Node(curr->val);

        while (curr->next != nullptr) {
            umap[curr]->next = new Node(curr->next->val);

            umap[curr->next] = umap[curr]->next;

            curr = curr->next;
        }

        curr = head;
        while (curr != nullptr) {
            umap[curr]->random = umap[curr->random];

            curr = curr->next;
        }

        return umap[head];
    }
};