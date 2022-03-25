#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;

struct node{
    int a, b, c;
}f[maxn];
int n, m, k, l;

int main(){
    while (~scanf("%d%d%d%d", &n, &m, &k, &l)){
        for (int i = 0, a, b, c; i < n; i++) {
            // scanf("%d%d%d", &f[i].a, &f[i].b, &f[i].c);
            scanf("%d%d%d", &a, &b, &c);
            if (i % 2 == 0){
                // int tot = max(m + a, m - b);
                // if (c) tot = max(tot, -m);
                // int tot = -200, flag = 0;
                // if (a){
                //     tot = m + a; flag = 1;
                // }
                // if (c){
                //     if (-m > tot) tot = -m, flag = 1;
                // }
                // if (b && flag == 0){
                //     tot = m - b;
                // }
                // m = tot;
                int tot = max(m + a, m - b);
                if (tot == m) tot = -m;
                if (c) tot = max(tot, -m);
                m = tot;
            }
            else {
                // int tot = 200, flag = 0;
                // if (b){
                //     tot = m - b; flag = 1;
                // }
                // if (c){
                //     if (-m < tot) tot = -m, flag = 1;
                // }
                // if (a && flag == 0){
                //     tot = m + a;
                // }
                // m = tot;
                int tot = min(m + a, m - b);
                if (tot == m) tot = -m;
                if (c) tot = min(tot, -m);
                m = tot;
            }
            printf("%d\n", m);
        }
        if (m >= k) puts("Good Ending");
        else if (m <= l) puts("Bad Ending");
        else puts("Normal Ending");
    }
    return 0;
}