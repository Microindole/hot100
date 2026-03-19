#include <string>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class Solution {
public:
    /**
     * @brief 判断两个字符串 s 和 t 是否是同构的。
     *
     * 算法核心：单向映射表 + 目标字符去重集合。
     * 仅维护一个从 s 到 t 的单向映射哈希表 s2t。
     * 为了防止多对一的冲突（即 s 中不同的字符映射到 t 中相同的字符），
     * 引入一个哈希集合 t_mapped 来记录 t 中哪些字符已经被“名花有主”。
     *
     * 映射核销逻辑图示：
     *   s = "badc", t = "baba"
     *   - i = 0: 'b' ➔ 'b' 建表。s2t['b']='b', t_mapped 塞入 'b'
     *   - i = 1: 'a' ➔ 'a' 建表。s2t['a']='a', t_mapped 塞入 'a'
     *   - i = 2: 'd' ➔ 'b' 准备建表。
     *            检查发现 'b' 已经在 t_mapped 中被占用了！立刻返回 false。
     *
     * @param s 源字符串
     * @param t 目标字符串
     * @return boolean 是否同构
     *
     * @complexity
     * - 时间复杂度: O(N) - 遍历一次字符串，哈希表的增查操作平均为 O(1)。
     * - 空间复杂度: O(N) - 两个容器最多存储字符集大小的键值对。
     */
    bool isIsomorphic(string s, string t) {
        unordered_map<char, char> s2t;
        unordered_set<char> t_mapped;

        int len = s.length();
        for (int i = 0; i < len; i++) {
            char x = s[i];
            char y = t[i];

            if (s2t.count(x)) {
                if (s2t[x] != y) {
                    return false;
                }
            }

            else {
                if (t_mapped.count(y)) {
                    return false;
                }

                s2t[x] = y;
                t_mapped.insert(y);
            }
        }

        return true;
    }
};