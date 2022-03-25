#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int maxn = 200000 + 5;

char s[maxn];
int n, m, tag[maxn], vis[maxn];

int main() {
    scanf("%s%d", s + 1, &m); n = strlen(s + 1);
    for (int i = 1, a; i <= m; i++) {
        scanf("%d", &a);
        tag[a]++; if (tag[a] >= 2) tag[a] -= 2;
    }
    for (int i = 1; 2 * i <= n; i++) {
        tag[i] += tag[i - 1];
        if (tag[i] >= 2) tag[i] -= 2;
    }
    for (int i = 1; i <= n; i++) {
        if (2 * i <= n) {
            if (tag[i]) putchar(s[n - i + 1]);
            else putchar(s[i]);
        } else {
            if (tag[n - i + 1]) putchar(s[n - i + 1]);
            else putchar(s[i]);
        } 
    }
    return 0;
}