## 1. 基础结构定义
所有遍历代码都基于这个结构：
```cpp
struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};
```

---

## 2. 深度优先搜索 (DFS) - 递归版
递归的精髓在于：**前、中、后序的区别仅仅是“处理当前节点”这一行代码的位置不同。**



### 模板代码
```cpp
void traversal(TreeNode* root) {
    if (root == nullptr) return;

    // 1. 前序遍历 (Pre-order)：中 -> 左 -> 右
    // cout << root->val << " "; 

    traversal(root->left);

    // 2. 中序遍历 (In-order)：左 -> 中 -> 右
    // cout << root->val << " "; 

    traversal(root->right);

    // 3. 后序遍历 (Post-order)：左 -> 右 -> 中
    // cout << root->val << " "; 
}
```

---

## 3. 深度优先搜索 (DFS) - 迭代版
迭代版需要手动维护一个 `std::stack`。

### A. 前序遍历 (中左右)
最简单。先把右孩子入栈，再把左孩子入栈（因为栈是后进先出）。
```cpp
void preOrderIterative(TreeNode* root) {
    if (!root) return;
    stack<TreeNode*> st;
    st.push(root);
    while (!st.empty()) {
        TreeNode* node = st.top(); st.pop();
        cout << node->val << " "; // 处理中间节点
        if (node->right) st.push(node->right); // 右孩子先入
        if (node->left) st.push(node->left);   // 左孩子后入
    }
}
```

### B. 中序遍历 (左中右)
稍微有点绕，需要一个指针 `cur` 帮你一路向左“钻”到底。
```cpp
void inOrderIterative(TreeNode* root) {
    stack<TreeNode*> st;
    TreeNode* cur = root;
    while (cur != nullptr || !st.empty()) {
        if (cur != nullptr) {
            st.push(cur);
            cur = cur->left; // 一路向左
        } else {
            cur = st.top(); st.pop();
            cout << cur->val << " "; // 处理中间节点
            cur = cur->right; // 转向右孩子
        }
    }
}
```

---

## 4. 广度优先搜索 (BFS) - 层序遍历
层序遍历是 BFS 在树上的应用。必须使用 `std::queue`。



### 模板代码
```cpp
void levelOrder(TreeNode* root) {
    if (!root) return;
    queue<TreeNode*> q;
    q.push(root);

    while (!q.empty()) {
        int size = q.size(); // 当前层的节点数
        // 这一层统一处理
        for (int i = 0; i < size; i++) {
            TreeNode* node = q.front(); q.pop();
            cout << node->val << " ";
            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }
        // cout << endl; // 如果需要换行显示层级
    }
}
```

---

## 5. 考试提速锦囊

* **中序遍历的特殊性**：如果是**二叉搜索树 (BST)**，中序遍历的结果一定是**升序**的。看到 BST 题，本能反应就是中序遍历。
* **复杂度**：所有遍历的时间复杂度都是 $O(N)$，因为每个点只访问常数次。
* **后序遍历的妙用**：如果题目涉及“自底向上”的信息传递（比如求树的高度、求最近公共祖先 LCA），通常用后序遍历。
* **迭代法的通用模板（颜色标记法）**：如果你觉得迭代法太难记，有一种“标记法”：进栈时加一个标记（比如用 `pair<TreeNode*, bool>`），`false` 表示还没处理过，`true` 表示处理过。这样前中后序的代码逻辑可以完全统一。





### 1. 通用迭代模板 (C++)

我们使用 `std::pair<TreeNode*, bool>`，其中 `bool` 为 `false` 表示第一次遇到（待处理其子节点），为 `true` 表示第二次遇到（该处理它的值了）。

```cpp
#include <iostream>
#include <vector>
#include <stack>

using namespace std;

// 统一迭代模板
vector<int> universalTraversal(TreeNode* root) {
    vector<int> res;
    if (!root) return res;
    
    // stack 存储 <节点指针, 是否已标记为待输出>
    stack<pair<TreeNode*, bool>> st;
    st.push({root, false});

    while (!st.empty()) {
        auto [node, visited] = st.top(); // C++17 结构化绑定
        st.pop();

        if (node == nullptr) continue;

        if (visited) {
            // 如果标记为 true，说明左右孩子都排好队了，轮到处理自己了
            res.push_back(node->val);
        } else {
            // 如果是首次遇到，按照【逆序】将 根、左、右 压入栈中
            // 因为栈是后进先出，所以想先出的要后压
            
            // --- 下面这三组 push 的顺序决定了是哪种遍历 ---
            
            // 1. 若是 【后序遍历】 (左右中)，顺序为：中(true) -> 右(false) -> 左(false)
            st.push({node, true}); 
            st.push({node->right, false});
            st.push({node->left, false});

            /* // 2. 若是 【中序遍历】 (左中右)，顺序为：右(false) -> 中(true) -> 左(false)
            st.push({node->right, false});
            st.push({node, true});
            st.push({node->left, false});
            */

            /* // 3. 若是 【前序遍历】 (中左右)，顺序为：右(false) -> 左(false) -> 中(true)
            st.push({node->right, false});
            st.push({node->left, false});
            st.push({node, true});
            */
        }
    }
    return res;
}
```

---

### 2. 为什么这个模板好记？

1.  **逻辑统一**：不管什么序，都是先把节点拿出来，判断一下。
2.  **“栈”的逆序性**：你想要什么样的输出顺序，就**反着**压入栈。
    * 想输出：**左 -> 中 -> 右**（中序）
    * 压栈顺：**右 -> 中 -> 左**
3.  **标记位的作用**：只有被标记为 `true` 的那个 `push` 动作，才是真正“轮到它输出”的时候。



---

### 3. 考前最后的回顾清单

为了防止明天大脑空白，再过一遍这几个关键点：

* **前缀和/差分**：区间加减查，下标从 1 开始能省掉很多 `if (i == 0)` 的判断。
* **二分答案**：`while (l <= r)`，`mid = l + (r - l) / 2`（防止溢出）。
* **DFS 回溯**：进去之前改状态，递归出来立刻改回来。
* **位运算**：`(n >> i) & 1` 检查第 $i$ 位是否为 1；`1 << i` 生成第 $i$ 位的掩码。
* **单调栈**：找“下一个大/小”，栈里存**下标**而不是值。
