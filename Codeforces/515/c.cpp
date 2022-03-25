#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 400000 + 20;

int dq[maxn], q, loc[maxn];

int main(){
    scanf("%d", &q); char op[3]; int x, hd = 200000 + 6, tl = 200000 + 5; 
    while (q--){
        scanf("%s%d", op, &x); getchar();
        if (op[0] == 'L'){
            dq[--hd] = x; loc[x] = hd;
        }
        if (op[0] == 'R'){
            dq[tl++] = x; loc[x] = tl;
        }
        if (op[0] == '?'){
            int k = loc[x];
            printf("%d\n", min(k - hd, tl - k));
        }
    }
    return 0;
}