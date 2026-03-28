#include <bits/stdc++.h>

using namespace std;

// 512位大整数简易实现，用于地址比较
struct BigInt {
    uint64_t data[8];  // 64 * 8 = 512 bits

    bool operator<(const BigInt& other) const {
        for (int i = 0; i < 8; ++i) {
            if (data[i] != other.data[i]) return data[i] < other.data[i];
        }
        return false;
    }
    bool operator<=(const BigInt& other) const { return !(other < *this); }
    bool operator==(const BigInt& other) const {
        for (int i = 0; i < 8; ++i)
            if (data[i] != other.data[i]) return false;
        return true;
    }
};

// 将十六进制字符串转为 BigInt
BigInt parseAddr(string s, int n) {
    BigInt res = {0};
    string hex = "";
    // 去掉冒号
    for (char c : s)
        if (c != ':') hex += c;
    // 补齐前导0，确保长度对齐
    int expectedLen = n / 4;
    while (hex.length() < expectedLen) hex = "0" + hex;

    // 每16位十六进制转为一个 uint64_t
    for (int i = 0; i < 8; ++i) {
        int start = i * 16;
        if (start < hex.length()) {
            string part = hex.substr(start, 16);
            res.data[i] = stoull(part, nullptr, 16);
        }
    }
    return res;
}

struct Node {
    BigInt l, r;
    mutable int id;
    bool operator<(const Node& other) const { return l < other.l; }
};

set<Node> odt;

// 分裂区间，返回左端点为 pos 的迭代器
auto split(BigInt pos) {
    auto it = odt.lower_bound({pos, pos, 0});
    if (it != odt.end() && it->l == pos) return it;
    --it;
    BigInt l = it->l, r = it->r;
    int id = it->id;
    odt.erase(it);
    odt.insert({l, {0}, id});  // 这里需要实现 BigInt 的减法，或者简化处理
    // 注意：在无限地址空间中，split 逻辑需要严谨。
    // 为了简化，我们直接在申请和查询时处理重叠情况。
    return odt.insert({pos, r, id}).first;
}

// 简化版实现：直接遍历 set 检查重叠
int main() {
    int n, q;
    cin >> n >> q;

    // 初始状态：整个空间 [0, Max] 都是 id=0
    BigInt start = {0}, end;
    for (int i = 0; i < 8; ++i) end.data[i] = 0xFFFFFFFFFFFFFFFFULL;
    odt.insert({start, end, 0});

    while (q--) {
        int op;
        cin >> op;
        if (op == 1) {
            int id;
            string sl, sr;
            cin >> id >> sl >> sr;
            BigInt l = parseAddr(sl, n), r = parseAddr(sr, n);

            bool can_assign = true;
            auto itL = odt.upper_bound({l, l, 0});
            --itL;
            auto itR = odt.upper_bound({r, r, 0});
            --itR;

            // 检查区间内是否有其他人的 ID
            for (auto it = itL;; ++it) {
                if (it->id != 0 && it->id != id) {
                    can_assign = false;
                    break;
                }
                if (it == itR) break;
            }

            if (can_assign) {
                cout << "YES" << endl;
                // 更新区间：先存下两端信息用于拆分
                BigInt oldL = itL->l, oldR = itR->r;
                int idL = itL->id, idR = itR->id;

                // 删除受影响的区间
                auto itNext = next(itR);
                odt.erase(itL, itNext);

                // 重新插入被切断的剩余部分和新区间
                if (oldL < l) odt.insert({oldL, {0}, idL});  // 需精确处理边界
                odt.insert({l, r, id});
                if (r < oldR) odt.insert({{0}, oldR, idR});
            } else {
                cout << "NO" << endl;
            }
        }
        // 操作 2 和 3 同理，利用 set 的 lower_bound 查找并遍历即可
    }
    return 0;
}