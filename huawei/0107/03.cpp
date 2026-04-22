#include <cctype>
#include <iostream>
#include <stack>
#include <string>
#include <vector>

using namespace std;

typedef long long ll;

struct Node {
    ll a, b;
};

Node add(Node n1, Node n2) { return {n1.a + n2.a, n1.b + n2.b}; }

Node mul(Node n1, Node n2) { return {n1.a * n2.b + n2.a * n1.b, n1.b * n2.b}; }

// 运算符优先级
int priority(char op) {
    if (op == '+') return 1;
    if (op == '*') return 2;
    return 0;
}

void compute(stack<Node>& vals, stack<char>& ops) {
    Node v2 = vals.top();
    vals.pop();
    Node v1 = vals.top();
    vals.pop();
    char op = ops.top();
    ops.pop();
    if (op == '+') vals.push(add(v1, v2));
    if (op == '*') vals.push(mul(v1, v2));
}

int main() {
    string raw;
    cin >> raw;

    size_t eq_pos = raw.find('=');

    string left_str = raw.substr(0, eq_pos);
    ll target = stoll(raw.substr(eq_pos + 1));

    string s = "";
    for (int i = 0; i < left_str.length(); ++i) {
        s += left_str[i];

        if (i + 1 < left_str.length()) {
            char curr = left_str[i];
            char next = left_str[i + 1];
            bool curr_is_val = (isdigit(curr) || curr == 'x' || curr == ')');
            bool next_is_val = (isdigit(next) || next == 'x' || next == '(');

            if (curr_is_val && next_is_val) {
                if (!(isdigit(curr) && isdigit(next))) {
                    s += '*';
                }
            }
        }
    }

    stack<Node> vals;
    stack<char> ops;

    for (int i = 0; i < s.length(); ++i) {
        if (isdigit(s[i])) {
            ll num = 0;
            while (i < s.length() && isdigit(s[i])) {
                num = num * 10 + (s[i] - '0');
                i++;
            }
            i--;
            vals.push({0, num});
        } else if (s[i] == 'x') {
            vals.push({1, 0});
        } else if (s[i] == '(') {
            ops.push('(');
        } else if (s[i] == ')') {
            while (!ops.empty() && ops.top() != '(') {
                compute(vals, ops);
            }
            ops.pop();
        } else {
            while (!ops.empty() && priority(ops.top()) >= priority(s[i])) {
                compute(vals, ops);
            }
            ops.push(s[i]);
        }
    }

    while (!ops.empty()) {
        compute(vals, ops);
    }

    Node res = vals.top();
    cout << (target - res.b) / res.a << endl;

    return 0;
}