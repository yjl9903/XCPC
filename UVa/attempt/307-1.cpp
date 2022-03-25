#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>
using namespace std;

int n,sum,tmax,s[100],used[100],ans;

bool Dfs(int num,int pos,int len){
    if(num * ans == sum)
        return true;
    for(int i = pos; i < n; ++i){
        if(used[i] || (i && s[i] == s[i - 1] && !used[i - 1])) continue;
        if(len + s[i] < ans){
            used[i] = 1;
            if(Dfs(num,i + 1,len + s[i])) return true;
            used[i] = 0;
            if(len == 0) return false;
        }
        else if(len + s[i] == ans){
            used[i] = 1;
            if(Dfs(num + 1,0,0)) return true;
            used[i] = 0;
            return false;
        }
    }
    return false;
}

int main(){
    while(scanf("%d",&n) == 1 && n){
        sum = 0;
        tmax = -1;
        for(int i = 0; i < n; ++i){
            scanf("%d",&s[i]);
            sum += s[i];
            tmax = max(tmax,s[i]);
        }
        sort(s,s + n,greater<int>());
        memset(used,0,sizeof(used));
        for(ans = tmax; ans <= sum; ++ans)
            if(sum % ans == 0)
                if(Dfs(0,0,0))
                    break;
        printf("%d\n",ans);
    }
    return 0;
}