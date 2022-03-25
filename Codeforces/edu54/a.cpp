#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 200000 + 5;

char s[maxn]; int n;

int main(){
    scanf("%d%s", &n, s);
    if (n == 2) return printf("%c", min(s[0], s[1])), 0;
    for (int i = 0; i + 1 < n; i++){
        if (s[i] > s[i + 1]){
            puts(s + i + 1); return 0;
        }
        putchar(s[i]);
    }
    return 0;
}