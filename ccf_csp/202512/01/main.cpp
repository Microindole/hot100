#include <bits/stdc++.h>

using namespace std;

int main(){
    int n, m;
    cin >> n >> m;
    vector<int> aset(n);
    vector<vector<int>> a(m, vector<int>(n+1, 0));
    vector<vector<int>> b(m, vector<int>(n+1, 0));
    
    for (int i = 0; i < n; i++){
        cin >> aset[i];
    }
    
    for (int i = 0; i < m; i++){
        int times;
        cin >> times;
        a[i][0] = times;
        for (int j = 0; j < times; j++){
            int num;
            cin >> num;
            a[i][j + 1] = num; 
        }
    }
    
    for (int i = 0; i < m; i++){
        int times;
        cin >> times;
        b[i][0] = times;
        for (int j = 0; j < times; j++){
            int num;
            cin >> num;
            b[i][j + 1] = num; 
        }
    }
    
    for(int i = 0; i < m; i++){
        bool real = true, xiaoc = true;
        
        // 因为集合 a 和 b 的长度可能不一样，所以必须分开循环算，不能放在一个循环里。
        // 初始值设为 0（0 异或任何数等于那个数本身），从第 1 个元素开始遍历。
        int ayi = 0, byi = 0;
        for(int j = 1; j <= a[i][0]; j++){
            // 在这里才去查 aset 映射表
            ayi ^= aset[a[i][j] - 1]; 
        }
        for(int j = 1; j <= b[i][0]; j++){
            // 在这里才去查 aset 映射表
            byi ^= aset[b[i][j] - 1]; 
        }
        xiaoc = (ayi == byi) ? true : false;
        if (a[i][0] != b[i][0]) {
            real = false; // 长度都不一样，客观上肯定不相等
        } else {
            // 长度一样时，逐个比对原始数字
            for(int j = 1; j <= a[i][0]; j++){
                if(a[i][j] != b[i][j]){
                    real = false;
                    break; // 只要发现一个不一样，就可以提前结束比对了
                }
            }
        }
        
        // 你的这部分逻辑非常完美，完全保留
        if(real && xiaoc || (!real) && (!xiaoc)){
            cout<<"correct"<<endl;
        }else{
            cout<<"wrong"<<endl;
        }
    }
    return 0;
}