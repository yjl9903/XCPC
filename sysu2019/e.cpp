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
const int maxn = 300000 + 5;

char s[maxn], t[100 * maxn];

int main() {
    cin >> s;
    vector<int> v;
    int tot = 0, n = strlen(s);
    for (int i = 0; i < n; i++) {
        int x = (int)s[i];
        for (int i = 0; i < 8; i++) {
            t[tot++] = (x >> i & 1) + '0';
        }
    }
    for (int i = 0; i < tot; i += 6) {
        int x = 0;
        for (int j = i; j < i + 6; j++) {
            x = x * 2 + (t[j] - '0');
        }
        // if (i) putchar(' ');
        printf("%d ", x);
    }
    // puts("");
    return 0;
}