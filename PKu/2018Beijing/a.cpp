#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <string>
#include <vector>
#include <map>
#include <set>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 50 + 5;

char s[maxn], t[maxn];
int n, tag;
vector<int> edge[maxn];

int dfs(int u){
    if (u == tag) return 1;
    for (auto& v : edge[u]){
        if (dfs(v)) return 1;
    }
    return 0;
}

int main(){
    while (~scanf("%d", &n)){
        for (int i = 0; i <= 2 * n; i++) edge[i].clear();
        vector<string> v;
        map<string,int> mp;
        int flag = 1;
        for (int i = 0; i < n; i++){
            scanf("%s%s", s, t);
            if (!flag) continue;
            int x, y;
            if (mp.count(s)) x = mp[s];
            else x = mp[s] = v.size(), v.emplace_back(s);
            if (mp.count(t)) y = mp[t];
            else y = mp[t] = v.size(), v.emplace_back(t);
            tag = x;
            if (dfs(y)) {
                printf("%s %s\n", s, t); flag = 0;
            }
            edge[x].push_back(y);
        }
        if (flag) puts("0");
    }
    return 0;
}