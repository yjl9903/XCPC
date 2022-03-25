#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int mod = 998244353;
const int maxn = 100000 + 5;

char s[maxn]; int n;

int main(){
    int T; scanf("%d", &T);
    while (T--){
        scanf("%d%s", &n, s);
        if (n == 2) {
            if (s[0] >= s[1]) puts("NO");
            else printf("YES\n2\n%c %c\n", s[0], s[1]);
        } else printf("YES\n2\n%c %s\n", s[0], s + 1);
    }    
    return 0;
}