#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 20 + 5;

int n, k, l, a[maxn], res = 0, t[maxn], vis[maxn];
int check[maxn * 10], cnt = 0;

bool judge(){
    ms(check, 0);
    int mmax = t[0], x;
    for (int s = 1; s < (1 << k); s++){
        x = 0;
        for (int j = 0; (1 << j) <= s; j++){
            if ((1 << j) & s) x ^= t[j], check[x] = 1;
            mmax = max(mmax, x);
        }
    }
    int r = l;
    for (int i = l; i <= mmax; i++){
        if (check[i]) r = i;
        else break;
    }
    return r > res;
}

int cal(){
    ms(check, 0);
    for (int i = 0; i < k; cout << t[i++] << ' '); cout << endl;
    int mmin = t[0], mmax = t[0], x;
    for (int i = 0; i < k; i++){
        x = t[i]; mmax = max(x, mmax);
        check[x] = 1;
        for (int j = 1; j < k; j++){
            x ^= t[(i + j) % k]; mmax = max(x, mmax);
            check[x] = 1;
        }
    }
    for (int i = l; i <= mmax; i++){
        if (!check[i]) return -1;
    }
    return mmax;
}

int dfs(int d, int p){
    if (d == k){
        if (!judge()) return 0;
        int x[maxn]; memcpy(x, t, sizeof t);
        do{
            res = max(res, cal()); 
        } while (next_permutation(t, t + k));
        memcpy(t, x, sizeof t);
        return 1;
    }
    for (int i = p; i < n; i++){
        t[d] = a[i];
        dfs(d + 1, i + 1);
    }
    return 0;
}

int main(){
    while (~scanf("%d%d%d", &n, &k, &l)){
        for (int i = 0; i < n; scanf("%d", &a[i++]));
        res = l; ms(vis, 0);
        dfs(0, 0);
        printf("%d\n", res);
    }
    return 0;
}
