#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
public:
    /**
     * @brief 将给定的字符串数组按照“字母异位词”进行分组。
     *
     * 字母异位词（Anagram）是指由相同字母重排列形成的字符串（如 "eat" 和
     * "tea"）。本函数通过将每个字符串的字符进行**升序排序**，作为哈希表的
     * Key，从而将所有异位词归类到同一个 vector 中。
     *
     * @details
     * ### 算法流程图 (Data Flow)
     * @code
     * [输入] vector<string>: ["eat", "tea", "tan"]
     *    │
     *    ├─► 遍历 "eat" ──► 排序得到 "aet" ──► 哈希表["aet"].push("eat")
     *    ├─► 遍历 "tea" ──► 排序得到 "aet" ──► 哈希表["aet"].push("tea")
     *    └─► 遍历 "tan" ──► 排序得到 "ant" ──► 哈希表["ant"].push("tan")
     *    │
     * [哈希表状态]
     *    "aet" ──► ["eat", "tea"]
     *    "ant" ──► ["tan"]
     *    │
     *    ▼ (通过 std::move 收集结果)
     * [输出] [["eat", "tea"], ["tan"]]
     * @endcode
     *
     * ### 复杂度分析
     * - **时间复杂度**: O(N * K log K)，其中 N 是字符串数组的长度，K 是
     *   字符串的最大长度。遍历 N 个词，每个词排序耗时 O(K log K)。
     * - **空间复杂度**: O(N * K)，用于存储哈希表及最终返回的结果集。
     *
     * @param strs 输入的字符串数组引用，包含待分组的单词。
     * @return vector<vector<string>> 分组后的字母异位词二维数组。
     */
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        // 创建哈希表，Key 为排序后的特征字符串，Value 为原字符串集合
        unordered_map<string, vector<string>> same;

        // 1. 遍历并分类
        for (const string& str : strs) {
            string key = str;
            sort(key.begin(), key.end());
            same[key].push_back(str);
        }

        // 2. 收集结果
        vector<vector<string>> res;
        res.reserve(same.size());  // 提前预留空间，提升内存分配效率

        // 使用结构化绑定与 std::move 避免不必要的字符串拷贝
        for (auto& [key, value] : same) {
            res.push_back(std::move(value));
        }

        return res;
    }
};