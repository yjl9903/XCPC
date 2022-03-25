#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <utility>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 1000000 + 5;

int n, flag, deg[maxn], fa[maxn];

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) {
            deg[i] = 0;
        }
        for (int i = 2; i <= n; i++) {
            scanf("%d", fa + i);
            deg[fa[i]]++;
        }
        flag = 0; 
        for (int i = 1; i <= n; i++) {
            if (deg[i]) continue;
            int x = fa[i], c = 1;
            while (x && deg[x] == 1) {
                c++; x = fa[x];
            }
            if (c % 2) {
                flag = 1; break;
            }
        }
        if (flag) puts("Takeru");
        else puts("Meiya");
    }
    return 0;
}