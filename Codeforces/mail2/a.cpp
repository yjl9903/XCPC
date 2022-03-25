#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;

int n, s, a[maxn], b[maxn];

int main(){
    scanf("%d%d", &n, &s);
    for (int i = 1; i <= n; i++) scanf("%d", a + i);
    for (int i = 1; i <= n; i++) scanf("%d", b + i);
    if (!a[1]) return puts("NO"), 0;
    if (!a[s] && !b[s]) return puts("NO"), 0;
    if (a[s]) return puts("YES"), 0;
    for (int i = s + 1; i <= n; i++) if (a[i] && b[i]) return puts("YES"), 0;
    puts("NO");
    return 0;
} 