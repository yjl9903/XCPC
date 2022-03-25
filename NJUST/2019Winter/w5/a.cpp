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

char f[30], a[30], b[30];
char s[maxn];

int main(){
    scanf("%s%s%s", a, b, s);
    for (int i = 0; i < 26; i++) f[a[i] - 'a'] = b[i];
    int n = strlen(s);
    for (int i = 0; i < n; i++) {
        if (s[i] >= '0' && s[i] <= '9') {
            putchar(s[i]);
        } else {
            if (s[i] >= 'a' && s[i] <= 'z')
                putchar(f[s[i] - 'a']);
            else
                putchar(f[s[i] - 'A'] - 'a' + 'A');
        }
    }
    return 0;
}