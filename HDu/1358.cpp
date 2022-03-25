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
const int inf = 1 << 30;
const int maxn = 1000000 + 5;

int n, fail[maxn]; char s[maxn];

int main() {
    int kase = 0;
    while (scanf("%d%s", &n, s + 1) == 2 && n) {
        printf("Test case #%d\n", ++kase);
        for (int i = 2; i <= n; i++) {
            int cur = fail[i - 1];
            while (cur && s[cur + 1] != s[i]) cur = fail[cur];
            if (s[cur + 1] == s[i]) cur++;
            fail[i] = cur;
            if (i % (i - fail[i]) == 0 && i / (i - fail[i]) > 1) printf("%d %d\n", i, i / (i - fail[i]));
        }
        puts("");
    }
    return 0;
}