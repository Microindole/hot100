#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    /**
     * @brief 将给定的 Unix 风格绝对路径简化为规范路径。
     *
     * 该函数利用标准库 stringstream 按照 '/' 切分路径，并借助 vector
     * 模拟栈的行为。通过排除空目录与 '.'，并对 '..' 进行弹栈回溯，
     * 最终组合出最简的规范绝对路径。
     *
     * @b 路径回溯与栈状态示意图 (以 /a/b/../c 为例):
     * @code
     *   根目录 (/)
     *    └── a
     *        └── b  ─── (遇到 "..") ──> 弹栈 (回退到上一级 'a')
     *        :
     *        └── c  ─── (最终进入)  ──> 拼接结果: /a/c
     * @endcode
     *
     * @param path 输入的原始 Unix 风格绝对路径字符串。
     * @return string 简化后的规范绝对路径。
     *
     * @note
     * - 如果路径最终回到了根目录之外，则依然停留在根目录 '/'。
     * - 连续的多个斜杠（例如 //）将被视为单个斜杠。
     * - 类似 "..." 这样超过两个点的目录名将被视为合法文件夹名。
     */
    string simplifyPath(string path) {
        stringstream ss(path);
        string item;
        vector<string> st;

        while (getline(ss, item, '/')) {
            if (item == "" || item == ".") {
                continue;
            }

            else if (item == "..") {
                if (!st.empty()) {
                    st.pop_back();
                }
            } else {
                st.push_back(item);
            }
        }

        string res = "";

        for (const string& dir : st) {
            res += "/" + dir;
        }

        return res.empty() ? "/" : res;
    }
};