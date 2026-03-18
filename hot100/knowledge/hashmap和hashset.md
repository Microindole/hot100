### 1. `unordered_map` (哈希映射)
它存储的是“键值对” ($Key \to Value$)。你可以把它想象成一本字典。

#### 常用语法：
```cpp
#include <unordered_map>
using namespace std;

// 1. 定义对象 (使用 .)
unordered_map<string, int> scores;

// 2. 插入或更新
scores["Alice"] = 95; 
scores.insert({"Bob", 80});

// 3. 查找是否存在
if (scores.count("Alice")) { // count 返回 1 或 0
    cout << "找到了！";
}

// 4. 获取值
int s = scores["Alice"];

// 5. 如果是指针 (使用 ->)
unordered_map<string, int>* ptr = &scores;
ptr->insert({"Charlie", 90}); // 效果等同于 (*ptr).insert(...)
```



---

### 2. `unordered_set` (哈希集合)
它只存储唯一的“键” ($Key$)。你可以把它想象成一个黑名单，里面只存名字，不存多余信息。

#### 常用语法：
```cpp
#include <unordered_set>

unordered_set<int> visited;

// 1. 插入
visited.insert(10);
visited.insert(10); // 重复插入无效，集合里依然只有一个 10

// 2. 查询 (最常用的功能)
if (visited.count(10)) {
    // 说明 10 已经在集合里了
}

// 3. 删除
visited.erase(10);
```



---

### 3. 在 LeetCode 205 (同构字符串) 中的具体应用

这道题为什么要用 `map`？因为我们要建立字符之间的**映射关系**。

```cpp
bool isIsomorphic(string s, string t) {
    unordered_map<char, char> s2t; // 记录 s[i] 映射到哪个 t[i]
    unordered_map<char, char> t2s; // 记录 t[i] 映射回哪个 s[i] (防止多个对一个)

    for (int i = 0; i < s.length(); i++) {
        char a = s[i];
        char b = t[i];

        // 逻辑：如果 a 已经有映射了，但映射的不是 b，那就报错
        if (s2t.count(a) && s2t[a] != b) return false;
        if (t2s.count(b) && t2s[b] != a) return false;

        // 建立映射
        s2t[a] = b;
        t2s[b] = a;
    }
    return true;
}
```
