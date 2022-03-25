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

char s[maxn], t[maxn];

int main(){
    scanf("%s%s", s, t);
    int n = strlen(s), m = strlen(t);
    if (n != m) return puts("No"), 0;
    for (int i = 0; i < n; i++) {
        if (s[i] == t[i]) continue;
        int cnt = 0;
        if (s[i] == 'a' || s[i] == 'e' || s[i] == 'i' || s[i] == 'o' || s[i] == 'u') cnt++;
        if (t[i] == 'a' || t[i] == 'e' || t[i] == 'i' || t[i] == 'o' || t[i] == 'u') cnt++;
        if (cnt == 1) return puts("No"), 0;
    }
    puts("Yes");
    return 0;
}