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

int n, w, a[maxn], b[maxn];

int nxt[maxn];
int kmp() {
    int slen = n, plen = w, i = 0, j = 0, ans = 0;
    while (i < slen && j < plen){
        if (j == -1 || a[i] == b[j]) i++, j++;
        else j = nxt[j];
        if (j == plen) {
            j = nxt[j]; ans++;
        }
    }
    return ans;
}

int main() {
    scanf("%d%d", &n, &w);
    for (int i = 0; i < n; i++) scanf("%d", a + i);
    for (int i = 0; i < w; i++) scanf("%d", b + i);
    n--; w--;
    for (int i = 0; i < n; i++) a[i] = a[i + 1] - a[i];
    for (int i = 0; i < w; i++) b[i] = b[i + 1] - b[i];
    if (n < w) return puts("0"), 0;
    int k = -1, i = 0; nxt[0] = -1;
    while (i < w){
        if (k == -1 || b[k] == b[i]) i++, k++, nxt[i] = k;
        else k = nxt[k];
    }
    if (w == 0) cout << 1 + n << endl;
    else cout << kmp() << endl;
    return 0;
}