#include<bits/stdc++.h>

using namespace std;


int main(){
    int b, c, l, r;
    cin>> b>> c>> l>> r;
    long long res = 0;
    if(l % 2 != 0){
        l += 1;
    }

    while(l <= r){
        res += 2 * (l*l +b*l +c);
        l += 2;
    }
    cout<<res<<endl;
}