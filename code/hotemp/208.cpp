#include <iostream>

using namespace std;

class Trie {
    struct Node {
        Node* child[26] = {};
        bool isEnd = false;
    };

    Node* root;

public:
    Trie() { root = new Node(); }

    void insert(string word) {
        Node* curr = root;

        for (char c : word) {
            int i = c - 'a';

            if (curr->child[i] == nullptr) {
                curr->child[i] = new Node();
            }

            curr = curr->child[i];
        }

        curr->isEnd = true;
    }

    bool search(string word) {
        Node* curr = root;

        for (char c : word) {
            int i = c - 'a';

            if (curr->child[i] == nullptr) {
                return false;
            }
            curr = curr->child[i];
        }

        return curr->isEnd;
    }

    bool startsWith(string prefix) {
        Node* curr = root;

        for (char c : prefix) {
            int i = c - 'a';

            if (curr->child[i] == nullptr) {
                return false;
            }
            curr = curr->child[i];
        }

        return true;
    }
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */