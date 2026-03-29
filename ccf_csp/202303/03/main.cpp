#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

// 结构体：存储解析后的原子表达式，例如 1:2 或 3~1
struct Expr {
    int attr;
    char op;
    int val;
};

// 解析像 "123:456" 或 "1:2" 这样的字符串
Expr parseExpr(string s) {
    size_t pos = s.find(':');
    if (pos == string::npos) pos = s.find('~');

    Expr res;
    res.attr = stoi(s.substr(0, pos));
    res.op = s[pos];
    res.val = stoi(s.substr(pos + 1));
    return res;
}

// 匹配单个原子表达式
bool check(int dn, const Expr& e, map<int, unordered_map<int, int>>& info) {
    if (info[dn].find(e.attr) == info[dn].end()) return false;
    if (e.op == ':') return info[dn][e.attr] == e.val;
    if (e.op == '~') return info[dn][e.attr] != e.val;
    return false;
}

void solve() {
    int n;
    if (!(cin >> n)) return;

    // 使用 map<int, ...> 自动按 DN 从小到大排序
    map<int, unordered_map<int, int>> info;
    for (int i = 0; i < n; i++) {
        int dn, cnt;
        cin >> dn >> cnt;
        for (int j = 0; j < cnt; j++) {
            int attr, val;
            cin >> attr >> val;
            info[dn][attr] = val;
        }
    }

    int m;
    cin >> m;
    while (m--) {
        string s;
        cin >> s;
        vector<int> results;

        if (s[0] == '&' || s[0] == '|') {
            // 解析复合表达式，例如 &(1:2)(3:4)
            // 找到两个括号的内容
            size_t first_start = s.find('(');
            size_t first_end = s.find(')');
            size_t second_start = s.find('(', first_end);
            size_t second_end = s.find(')', second_start);

            Expr e1 = parseExpr(s.substr(first_start + 1, first_end - first_start - 1));
            Expr e2 = parseExpr(s.substr(second_start + 1, second_end - second_start - 1));

            for (auto const& [dn, attrs] : info) {
                bool res1 = check(dn, e1, info);
                bool res2 = check(dn, e2, info);
                if (s[0] == '&' && res1 && res2) results.push_back(dn);
                if (s[0] == '|' && (res1 || res2)) results.push_back(dn);
            }
        } else {
            // 普通表达式 1:2
            Expr e = parseExpr(s);
            for (auto const& [dn, attrs] : info) {
                if (check(dn, e, info)) results.push_back(dn);
            }
        }

        // 输出结果
        for (int i = 0; i < results.size(); i++) {
            cout << results[i] << (i == results.size() - 1 ? "" : " ");
        }
        cout << "\n";
    }
}

int main() {
    // 提速
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}

/*
2
1 2 1 2 2 3
2 2 2 3 3 1
4
1:2
3~1
&(1:2)(2:3)
|(1:2)(3:1)
*/

/*
以下是满分答案:
```cpp
#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

// 全局存储用户信息：DN -> {属性: 值}
map<int, unordered_map<int, int>> info;

// 辅助函数：计算两个 set 的交集
set<int> intersect(const set<int>& a, const set<int>& b) {
    set<int> res;
    set_intersection(a.begin(), a.end(), b.begin(), b.end(), inserter(res, res.begin()));
    return res;
}

// 辅助函数：计算两个 set 的并集
set<int> unite(const set<int>& a, const set<int>& b) {
    set<int> res;
    set_union(a.begin(), a.end(), b.begin(), b.end(), inserter(res, res.begin()));
    return res;
}

// 核心：递归解析函数
// s 是完整字符串，pos 是当前处理到的位置（引用传递，保证全局进度）
set<int> parse(const string& s, int& pos) {
    set<int> res;
    if (s[pos] == '&' || s[pos] == '|') {
        char op = s[pos];
        pos += 2; // 跳过 '&(' 或 '|('
        set<int> res1 = parse(s, pos);
        pos += 1; // 跳过 ')'
        pos += 1; // 跳 skip '('
        set<int> res2 = parse(s, pos);
        pos += 1; // 跳过 ')'

        if (op == '&') return intersect(res1, res2);
        else return unite(res1, res2);
    } else {
        // 原子表达式：解析数字:数字 或 数字~数字
        int start = pos;
        while (pos < s.size() && s[pos] != ')' && s[pos] != '(') pos++;
        string sub = s.substr(start, pos - start);

        size_t sep = sub.find(':');
        bool isEqual = true;
        if (sep == string::npos) {
            sep = sub.find('~');
            isEqual = false;
        }

        int attr = stoi(sub.substr(0, sep));
        int val = stoi(sub.substr(sep + 1));

        for (auto const& [dn, attrs] : info) {
            auto it = attrs.find(attr);
            if (it != attrs.end()) {
                if (isEqual && it->second == val) res.insert(dn);
                if (!isEqual && it->second != val) res.insert(dn);
            }
        }
        return res;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int dn, cnt;
        cin >> dn >> cnt;
        while (cnt--) {
            int a, v;
            cin >> a >> v;
            info[dn][a] = v;
        }
    }

    int m;
    cin >> m;
    while (m--) {
        string s;
        cin >> s;
        int pos = 0;
        set<int> ans = parse(s, pos);

        // 输出结果
        bool first = true;
        for (int dn : ans) {
            if (!first) cout << " ";
            cout << dn;
            first = false;
        }
        cout << "\n";
    }
    return 0;
}
```
*/