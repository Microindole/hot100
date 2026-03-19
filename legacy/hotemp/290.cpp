#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
public:
    /**
     * @brief 判断字符串 s 是否遵循给定的规律 pattern。
     *
     * 算法核心：字符串流分词 + 单向映射表 + 单词去重集合。
     * 先将句子 s 按照空格切分为单词数组 words。
     * 若单词总数与规律长度不一致，直接判定失败。
     * 随后利用 p2w 映射表与 word_mapped 集合，进行双射一致性校验。
     *
     * 映射核销逻辑图示：
     *   pattern = "abba", words = ["dog", "cat", "cat", "dog"]
     *   - i = 0: 'a' ➔ "dog" 注册。p2w['a']="dog", word_mapped 塞入 "dog"
     *   - i = 1: 'b' ➔ "cat" 注册。p2w['b']="cat", word_mapped 塞入 "cat"
     *   - i = 2: 'b' ➔ 历史记录为 "cat"，当前也是 "cat"，通过！
     *   - i = 3: 'a' ➔ 历史记录为 "dog"，当前也是 "dog"，通过！
     *
     * @param pattern 规律字符串（如 "abba"）
     * @param s 包含空格的句子（如 "dog cat cat dog"）
     * @return boolean 是否完全匹配
     *
     * @complexity
     * - 时间复杂度: O(N + M) - N 为 s 的长度（用于分词），M 为 pattern 的长度。
     * - 空间复杂度: O(N + M) - 存储单词数组、哈希表及去重集合所需的空间。
     */
    bool wordPattern(string pattern, string s) {
        stringstream ss(s);
        string word;
        vector<string> words;
        while (ss >> word) {
            words.push_back(word);
        }

        if (pattern.length() != words.size()) {
            return false;
        }

        unordered_map<char, string> p2w;
        unordered_set<string> word_mapped;

        for (int i = 0; i < pattern.length(); i++) {
            char ch = pattern[i];
            string curr_word = words[i];

            if (p2w.count(ch)) {
                if (p2w[ch] != curr_word) {
                    return false;
                }
            } else {
                if (word_mapped.count(curr_word)) {
                    return false;
                }

                p2w[ch] = curr_word;
                word_mapped.insert(curr_word);
            }
        }

        return true;
    }
};