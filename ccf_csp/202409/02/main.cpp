// #include <algorithm>
// #include <iostream>
// #include <string>
// #include <unordered_map>
// #include <vector>

// using namespace std;

// void process(string& s, int k, unordered_map<char, char>& map, unordered_map<int, string>& processed) {
//     int size = s.size();

//     if (processed.count(k)) return;

//     int start_k = 0;
//     for (int i = k - 1; i >= 0; i--) {
//         if (processed.count(i)) {
//             s = processed[i];
//             start_k = i;
//             break;
//         }
//     }

//     int remain_k = k - start_k;
//     for (int i = 0; i < remain_k; i++) {
//         for (int j = 1; j < size - 1; j++) {
//             if (map.count(s[j])) {
//                 s[j] = map[s[j]];
//             }
//         }
//     }
// }

// int main() {
//     ios::sync_with_stdio(false);
//     cin.tie(0);

//     string s;
//     getline(cin, s);

//     int n;
//     if (!(cin >> n)) return 0;
//     string dummy;
//     getline(cin, dummy);

//     unordered_map<char, char> mp;
//     for (int i = 0; i < n; i++) {
//         string rule_line;
//         getline(cin, rule_line);
//         if (rule_line.length() >= 3) {
//             mp[rule_line[1]] = rule_line[2];
//         }
//     }

//     int m;
//     if (!(cin >> m)) return 0;
//     vector<int> times(m, 0), sorted_time(m, 0);
//     for (int i = 0; i < m; i++) {
//         cin >> times[i];
//         sorted_time[i] = times[i];
//     }

//     sort(sorted_time.begin(), sorted_time.end());

//     unordered_map<int, string> processed;
//     processed[0] = s;

//     for (int i = 0; i < m; i++) {
//         int current_k = sorted_time[i];
//         if (processed.count(current_k)) continue;

//         string temp_s = s;
//         process(temp_s, current_k, mp, processed);
//         processed[current_k] = temp_s;
//     }

//     for (int i = 0; i < m; i++) {
//         if (processed.count(times[i])) {
//             cout << processed[times[i]] << "\n";
//         }
//     }

//     return 0;
// }

// 最优解
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// f[p][c]：字符 c 经过 2^p 次变换后的 ASCII 码
// 31 层足够覆盖 k=10^9 (2^30 > 10^9)
int f[31][128];

int main() {
    // 1. 优化输入输出性能
    ios::sync_with_stdio(false);
    cin.tie(0);

    // 2. 读取初始字符串 #s#
    string s;
    if (!getline(cin, s)) return 0;

    // 3. 读取变换规则数量 n
    int n;
    if (!(cin >> n)) return 0;
    string dummy;
    getline(cin, dummy);  // 必须：吸收 cin>>n 留下的换行符

    // 初始化倍增表第 0 层：默认 f(c) = c
    for (int i = 0; i < 128; i++) f[0][i] = i;

    // 填充题目给出的 n 条变换规则
    for (int i = 0; i < n; i++) {
        string rule;
        getline(cin, rule);
        if (rule.length() >= 3) {
            // rule 格式为 #xy#，下标 1 是原字符，2 是目标字符
            f[0][(int)rule[1]] = (int)rule[2];
        }
    }

    // 4. 预处理倍增表 (状态转移)
    // 时间复杂度：O(30 * 128)
    for (int p = 1; p <= 30; p++) {
        for (int i = 0; i < 128; i++) {
            f[p][i] = f[p - 1][f[p - 1][i]];
        }
    }

    // 5. 处理 m 个查询
    int m;
    if (!(cin >> m)) return 0;
    while (m--) {
        int k;
        cin >> k;

        // 我们不需要改变原始 s，每次根据查询生成结果
        string res = s;
        for (int j = 1; j < res.size() - 1; j++) {
            int cur = (int)res[j];
            // 对 k 进行二进制拆分
            for (int p = 30; p >= 0; p--) {
                if ((k >> p) & 1) {
                    cur = f[p][cur];
                }
            }
            res[j] = (char)cur;
        }
        cout << res << "\n";
    }

    return 0;
}

/*
#Hello World#
6
#HH#
#e #
# r#
#re#
#oa#
#ao#
3
1 2 3
*/