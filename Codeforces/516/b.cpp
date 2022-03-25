#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;

int a;

int main(){
    int T; scanf("%d", &T);
    while (T--){
        scanf("%d", &a); int ans = 1, ans1 = 0;
        // for (int i = 0; i <= a; i++){
        //     if (a - i == (a ^ i)) ans1++;
        // }   
        while (a){
            if (a & 1) ans *= 2;
            a /= 2;
        }
        printf("%d\n", ans);
    }
    return 0;
}