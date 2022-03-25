#include <iostream>
#include <cstring>
#include <algorithm>
#include <functional>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 200 + 5;

int len[maxn], x[maxn], n, res = 0, sum, tag, cnt = 0;

int dfs(int d){
    if (d == n + 1){
        for (int i = 0; i < cnt; i++){
            if (x[i] != tag)
                return 0;
        }
        return 1;
    }
    for (int i = 0; i < cnt; i++){
        if (x[i] + len[d] <= tag){
            x[i] += len[d];
            if (dfs(d + 1))
                return 1;
            else 
                x[i] -= len[d];
            while (i + 1 < cnt && x[i + 1] == x[i]) i++;
        }
    }
    return 0;
}

int main(){
    while (cin >> n && n){
        sum = 0; int m = 0;
        for (int i = 1; i <= n; cin >> len[i], sum += len[i], m = max(m, len[i]), i++);
        sort(len + 1, len + n + 1, greater<int>());
        
        for (tag = m; tag <= sum; tag++){
            if (sum % tag) continue;
            cnt = sum / tag; ms(x, 0);
            if (dfs(1)) break;
        }
        cout << tag << endl;
    }
    return 0;
}