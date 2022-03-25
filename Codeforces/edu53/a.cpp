#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <string>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;

char s[maxn]; int n, cnt[100];
string ans;

int main(){
    scanf("%d%s", &n, s); 
    for (int i = 1; i < n; i++){
        if (s[i] != s[i - 1]) {
            puts("YES");
            putchar(s[i - 1]); putchar(s[i]);
            return 0;
        }
    }
    puts("NO");
    return 0;
}