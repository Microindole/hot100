#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
public:
    vector<string> removeInvalidParentheses(string s) {
        int l_rem = 0;  // 需要删除的左括号数量
        int r_rem = 0;  // 需要删除的右括号数量

        // 第一步：预处理，计算最少需要删除的左、右括号数量
        for (char c : s) {
            if (c == '(') {
                l_rem++;
            } else if (c == ')') {
                if (l_rem > 0) {
                    l_rem--;  // 匹配掉一个
                } else {
                    r_rem++;  // 无法匹配，说明该右括号必删
                }
            }
        }

        vector<string> res;
        dfs(s, 0, l_rem, r_rem, res);
        return res;
    }

private:
    /**
     * @param s 当前字符串
     * @param start 搜索的起始位置，避免重复搜索
     * @param l_rem 剩余需要删除的左括号数
     * @param r_rem 剩余需要删除的右括号数
     */
    void dfs(string s, int start, int l_rem, int r_rem, vector<string>& res) {
        // 递归出口：删够了
        if (l_rem == 0 && r_rem == 0) {
            if (isValid(s)) {
                res.push_back(s);
            }
            return;
        }

        for (int i = start; i < s.size(); ++i) {
            // 剪枝技巧 1：处理连续重复的括号，只尝试删除第一个，避免产生重复结果
            // 例如 "())"，删除第一个 ')' 和第二个 ')' 效果一样，这里只删第一个
            if (i > start && s[i] == s[i - 1]) continue;

            // 尝试删除一个右括号
            if (r_rem > 0 && s[i] == ')') {
                // 构造新字符串并递归，起始位置仍为 i
                dfs(s.substr(0, i) + s.substr(i + 1), i, l_rem, r_rem - 1, res);
            }
            // 尝试删除一个左括号
            else if (l_rem > 0 && s[i] == '(') {
                dfs(s.substr(0, i) + s.substr(i + 1), i, l_rem - 1, r_rem, res);
            }
        }
    }

    // 辅助函数：判断当前字符串是否合法
    bool isValid(const string& s) {
        int count = 0;
        for (char c : s) {
            if (c == '(')
                count++;
            else if (c == ')') {
                count--;
                if (count < 0) return false;  // 任何时刻右括号不能比左括号多
            }
        }
        return count == 0;
    }
};