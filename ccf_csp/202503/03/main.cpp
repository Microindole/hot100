#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

// 定义取模常数
const long long MOD = 1000000007;

// 定义变量结构体
struct Node {
    int type;             // 1: 直接赋值, 2: 间接赋值
    long long directLen;  // 类型 1 时存储预先算好的长度
    vector<string> expr;  // 类型 2 时存储操作数列表 (如 ["$a", "hello"])
};

// 变量池：变量名 -> 变量信息
unordered_map<string, Node> dict;

// 递归函数：计算变量 varName 的当前长度
long long getLen(string varName) {
    // 题目约定：未赋值的变量初始值为空字符串，长度为 0
    if (dict.find(varName) == dict.end()) {
        return 0;
    }

    Node& node = dict[varName];

    // 如果是直接赋值，直接返回存好的长度
    if (node.type == 1) {
        return node.directLen;
    }

    // 如果是间接赋值，动态计算表达式中所有操作数的长度和
    long long total = 0;
    for (const string& op : node.expr) {
        if (op[0] == '$') {
            // 操作数是变量，递归获取其长度（去除开头的$符号）
            total = (total + getLen(op.substr(1))) % MOD;
        } else {
            // 操作数是普通字符串，直接获取其长度
            total = (total + op.length()) % MOD;
        }
    }
    return total;
}

int main() {
    // 优化输入输出效率
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n;
    if (!(cin >> n)) return 0;
    string dummy;
    getline(cin, dummy);  // 吃掉 n 之后的回车换行符

    for (int i = 0; i < n; ++i) {
        string line;
        if (!getline(cin, line) || line.empty()) continue;

        stringstream ss(line);
        int opType;
        string varName;
        ss >> opType >> varName;

        if (opType == 1) {
            // 赋值语句 1：直接赋值（立即求值）
            vector<string> operands;
            string op;
            long long currentLen = 0;
            while (ss >> op) {
                if (op[0] == '$') {
                    currentLen = (currentLen + getLen(op.substr(1))) % MOD;
                } else {
                    currentLen = (currentLen + op.length()) % MOD;
                }
            }
            // 更新变量状态为类型 1
            dict[varName] = {1, currentLen, {}};
        } else if (opType == 2) {
            // 赋值语句 2：间接赋值（延迟求值）
            vector<string> operands;
            string op;
            while (ss >> op) {
                operands.push_back(op);
            }
            // 更新变量状态为类型 2，并保存操作数列表
            dict[varName] = {2, 0, operands};
        } else if (opType == 3) {
            // 输出语句 3：计算并打印当前长度
            cout << getLen(varName) << "\n";
        }
    }

    return 0;
}