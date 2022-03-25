#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7;
const int maxn = 100000 + 5;

int l1, r1, l2, r2;

int main(){
    int T; scanf("%d", &T);
    while (T--){
        scanf("%d%d%d%d", &l1, &r1, &l2, &r2);
        if (l1 != r2)
            printf("%d %d\n", l1, r2);
        else if (l1 != l2)
            printf("%d %d\n", l1, l2);
        else if (r1 != l2)
            printf("%d %d\n", r1, l2);
        else 
            printf("%d %d\n", r1, r2);
    }
    return 0;
}