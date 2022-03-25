#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int maxn = 100000 + 5;
const int seed = 135;
const int p1 = 1e9 + 7;

char s[maxn]; int n, m, ans, ansp;

ull h[maxn], xp[maxn] = {1};
void Hash(){
    ull ans = 0; h[n] = 0;
    for (int i = n - 1; i >= 0; i--) ans = (ans * seed + s[i]) % p1, h[i] = ans;
}
ull cal(int l, int r){
    int len = r - l;
    return (h[l] - h[r] * xp[len] % p1 + p1) % p1; 
}
int check(int x){
    map<ull,int> mp; int p = -1;
    for (int i = 0; i + x <= n; i++){
        ull t = cal(i, i + x); mp[t]++;
        if (mp[t] >= m) {
            p = i;
        }
    }
    return p;
}

int main(){
    for (int i = 1; i < maxn; i++) xp[i] = xp[i - 1] * seed % p1; 
    while (~scanf("%d%s", &m, s)){
        if (!m) return 0;
        n = strlen(s); Hash();
        int l = 1, r = n; ans = -1;
        while (l <= r){
            int m = l + r >> 1, flag = check(m);
            if (flag != -1) ans = m, ansp = flag, l = m + 1;
            else r = m - 1;
        }
        if (ans == -1) puts("none");
        else printf("%d %d\n", ans, ansp);
    }
    return 0;
}