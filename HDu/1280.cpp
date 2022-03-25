#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 3000 + 5;

int n, m, a[maxn], v[maxn * maxn];

int main(){
    while (~scanf("%d%d", &n, &m)){
        int tot = 0;
        for (int i = 0; i < n; i++) {
            scanf("%d", a + i);
            for (int j = 0; j < i; j++) v[tot++] = -a[i] - a[j];
        }
        nth_element(v, v + m, v + tot); sort(v, v + m);
        for (int i = 0; i < m; i++) printf("%d%c", -v[i], " \n"[i == m - 1]);
    }
    return 0;
}