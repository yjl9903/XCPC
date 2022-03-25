#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7;
const int maxn = 1000000 + 5;

int n; char s[maxn];

int main(){
    int T; scanf("%d", &T);
    while (T--){
        scanf("%s", s + 1); n = strlen(s + 1);
        for (int i = 1; i < n; i++) {
            if (s[i] == '.' && s[i + 1] == '.') putchar('C');
            else putchar('D');
        }
        puts("");
    }
    return 0;
}