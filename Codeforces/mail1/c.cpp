#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;

int n, l[maxn], r[maxn], a[maxn];

int main(){
    scanf("%d", &n);
    for (int i = 0; i < n; i++) scanf("%d", l + i);
    for (int i = 0; i < n; i++) scanf("%d", r + i);
    if (l[0] != 0 || r[n - 1] != 0) return puts("NO"), 0;
    for (int i = 0; i < n; i++){
        a[i] = n - l[i] - r[i];
        if (a[i] < 1) return puts("NO"), 0;
    }
    for (int i = 0; i < n; i++){
        int s1 = 0, s2 = 0;
        for (int j = 0; j < n; j++){
            if (j < i && a[i] < a[j]) s1++;
            if (j > i && a[i] < a[j]) s2++;
        }
        if (s1 != l[i] || s2 != r[i]) return puts("NO"), 0;
    }
    puts("YES");
    for (int i = 0; i < n; i++) printf("%d ", a[i]);
    return 0;
} 