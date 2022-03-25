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
const int maxn = 500000 + 5;

char s[maxn]; int n;

int main() {
    scanf("%s", s);
    int n = strlen(s), l = -1, r = -1, l2 = -1, r2 = -1;
    for (int i = 0; i < n; i++) {
        if (s[i] == '[') {
            l = i; break;
        } 
    }
    for (int i = n - 1; i >= 0; i--) {
        if (s[i] == ']') {
            r = i; break;
        }
    }
    if (l == -1 || r == -1) return puts("-1"), 0;
    for (int i = l; i <= r; i++) {
        if (s[i] == ':') {
            if (l2 == -1) l2 = i;
            else r2 = i;
        }
    }
    if (l2 == -1 || r2 == -1) return puts("-1"), 0;
    int cnt = 0;
    for (int i = l2; i <= r2; i++) if (s[i] == '|') cnt++;
    printf("%d", cnt + 4);
    return 0;
}