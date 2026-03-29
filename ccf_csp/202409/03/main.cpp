#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

// 存储补丁块的结构体
struct Block {
    int NN, MM, nn, mm;
    vector<string> oldLines;  // 期望的原文件内容（- 和 空格）
    vector<string> newLines;  // 替换后的新内容（+ 和 空格）
};

// 辅助函数：解析 @@ 行中的四个数字
void parseHeader(string s, int& NN, int& MM, int& nn, int& mm) {
    // 将干扰字符替换为空格，方便 stringstream 读取
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == '@' || s[i] == '-' || s[i] == '+' || s[i] == ',') s[i] = ' ';
    }
    stringstream ss(s);
    ss >> NN >> MM >> nn >> mm;
}

int main() {
    // 本地测试可以使用这行： freopen("in.txt", "r", stdin);

    int n;
    if (!(cin >> n)) return 0;
    string line;
    getline(cin, line);  // 吸收 n 之后的回车

    vector<string> origin;
    origin.push_back("");  // 下标从 1 开始，放个占位符
    for (int i = 0; i < n; i++) {
        getline(cin, line);
        origin.push_back(line);
    }

    // 1. 读入补丁并移除注释
    vector<string> patchRaw;
    while (getline(cin, line)) {
        if (!line.empty() && line[0] == '#') continue;
        patchRaw.push_back(line);
    }

    if (patchRaw.empty()) return 0;  // 没补丁直接结束

    // 2. 将补丁切分成 Block
    vector<Block> blocks;
    for (int i = 0; i < patchRaw.size();) {
        if (patchRaw[i].substr(0, 2) == "@@") {
            Block b;
            parseHeader(patchRaw[i], b.NN, b.MM, b.nn, b.mm);
            int j = i + 1;
            while (j < patchRaw.size() && patchRaw[j].substr(0, 2) != "@@") {
                char prefix = patchRaw[j][0];
                string content = patchRaw[j].substr(1);
                if (prefix == '-') {
                    b.oldLines.push_back(content);
                } else if (prefix == '+') {
                    b.newLines.push_back(content);
                } else if (prefix == ' ') {
                    b.oldLines.push_back(content);
                    b.newLines.push_back(content);
                } else {
                    // 非法开头
                    cout << "Patch is damaged." << endl;
                    return 0;
                }
                j++;
            }
            // 校验行数
            if (b.oldLines.size() != b.MM || b.newLines.size() != b.mm) {
                cout << "Patch is damaged." << endl;
                return 0;
            }
            blocks.push_back(b);
            i = j;
        } else {
            i++;
        }
    }

    if (blocks.empty()) {
        cout << "Patch is damaged." << endl;
        return 0;
    }

    // 3. 校验块的顺序 (NN >= 前一块 NN + MM)
    for (int i = 1; i < blocks.size(); i++) {
        if (blocks[i].NN < blocks[i - 1].NN + blocks[i - 1].MM) {
            cout << "Patch is damaged." << endl;
            return 0;
        }
    }

    // 4. 寻找 delta 并应用补丁
    int currentTotalDelta = 0;
    int lastAppliedEnd = 0;  // 记录上一个块在原文件中匹配结束的位置

    for (int k = 0; k < blocks.size(); k++) {
        Block& b = blocks[k];
        int targetNN = b.NN + currentTotalDelta;

        int bestDelta = 2e9;  // 找绝对值最小的 delta
        int finalS = -1;

        // 遍历所有可能的 delta，范围 [-MM+1, MM-1]
        for (int delta = -(b.MM - 1); delta <= (b.MM - 1); delta++) {
            int S = b.NN + delta;  // 注意：根据题目描述，delta 是加在原始 NN 上的

            // 校验位置合法性
            if (S <= lastAppliedEnd || S + b.MM - 1 > origin.size() - 1) continue;

            // 检查内容是否匹配
            bool match = true;
            for (int i = 0; i < b.MM; i++) {
                if (origin[S + i] != b.oldLines[i]) {
                    match = false;
                    break;
                }
            }

            if (match) {
                // 比较逻辑：绝对值小优先；绝对值相同取数值小
                if (abs(delta) < abs(bestDelta)) {
                    bestDelta = delta;
                    finalS = S;
                } else if (abs(delta) == abs(bestDelta)) {
                    if (delta < bestDelta) {
                        bestDelta = delta;
                        finalS = S;
                    }
                }
            }
        }

        if (finalS == -1) {
            cout << "Patch is damaged." << endl;
            return 0;
        }

        // 执行替换：先删后插
        // erase 的参数是 (起始迭代器, 结束迭代器)
        origin.erase(origin.begin() + finalS, origin.begin() + finalS + b.MM);
        origin.insert(origin.begin() + finalS, b.newLines.begin(), b.newLines.end());

        // 更新状态
        lastAppliedEnd = finalS + b.mm - 1;
        currentTotalDelta += bestDelta;
    }

    // 5. 输出最终结果
    for (int i = 1; i < origin.size(); i++) {
        cout << origin[i] << "\n";
    }

    return 0;
}