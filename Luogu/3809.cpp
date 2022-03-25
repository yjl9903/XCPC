#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000000 + 5;

char s[maxn];

namespace SA {
    int n, m, sa[maxn], x[maxn], y[maxn], c[maxn];
    void rsort() {
        for (int i = 0; i <= m; i++) c[i] = 0;
        for (int i = 1; i <= n; i++) c[x[i]]++;
        for (int i = 1; i <= m; i++) c[i] += c[i - 1];
        for (int i = n; i >= 1; i--) sa[c[x[y[i]]]--] = y[i];
    }
    int cmp(int i, int j, int k) { return y[i] == y[j] && y[i + k] == y[j + k]; }
    void getsa(char* s) {
        n = strlen(s + 1); m = 127;
        for (int i = 1; i <= n; i++) x[i] = s[i], y[i] = i;
        rsort();
        for (int k = 1, p = 1; p < n; k += k, m = p) {
            p = 0;
            for (int i = n - k + 1; i <= n; i++) y[++p] = i;
            for (int i = 1; i <= n; i++) if (sa[i] > k) y[++p] = sa[i] - k;
            rsort(); swap(x, y); x[sa[1]] = p = 1;
            for (int i = 2; i <= n; i++) x[sa[i]] = cmp(sa[i], sa[i - 1], k) ? p : ++p;
        }
    }
    int height[maxn];
    void getHeight() {
        for (int i = 1, k = 0; i <= n; i++) {
            if (k) k--; int j = sa[x[i] - 1];
            while (i + k <= n && j + k <= n && s[i + k] == s[j + k]) k++;
            height[x[i]] = k;
        }
    }
}
using namespace SA;

int main(){
    scanf("%s", s + 1);
    int n = strlen(s + 1);
    getsa(s); getHeight();
    for (int i = 1; i <= n; i++) printf("%d%c", sa[i], " \n"[i == n]);
    // for (int i = 2; i <= n; i++) printf("%d%c", height[i], " \n"[i == n]);
    return 0;
}