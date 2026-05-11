#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    string reverseWords(string s) {
        string res = "";
        int n = s.size();
        int i = n - 1;

        while (i >= 0) {
            while (i >= 0 && s[i] == ' ') i--;
            if (i < 0) break;

            int end = i;
            while (i >= 0 && s[i] != ' ') i--;

            int start = i;
            string word = s.substr(start + 1, end - start);

            if (res.empty()) {
                res = word;
            } else {
                res += " " + word;
            }
        }

        return res;
    }

    /**
     * 以下是最优解 O(1) 的空间复杂度
     * 采用 全局翻转 + 局部翻转
     *
     * ```
     * string reverseWords(string s) {
     *     // 1. 移除多余空格 (原地操作)
     *     int slow = 0;
     *     for (int fast = 0; fast < s.size(); ++fast) {
     *         if (s[fast] != ' ') { // 遇到字符
     *             if (slow != 0) s[slow++] = ' '; // 单词间补一个空格
     *             while (fast < s.size() && s[fast] != ' ') {
     *                 s[slow++] = s[fast++];
     *             }
     *         }
     *     }
     *     s.erase(s.begin() + slow, s.end()); // 斩断后面多余的部分
     *
     *     // 2. 全局翻转
     *     reverse(s.begin(), s.end());
     *
     *  // 3. 局部翻转 (翻转每个单词)
     *  int start = 0;
     *  for (int end = 0; end <= s.size(); ++end) {
     *      // 当遇到空格或到达末尾时，说明一个单词结束了
     *      if (end == s.size() || s[end] == ' ') {
     *          reverse(s.begin() + start, s.begin() + end);
     *          start = end + 1; // 下一个单词的起点
     *      }
     *  }
     *
     *  return s;
     * ```
     */
};