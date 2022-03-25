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
const int maxn = 200000 + 5;

int n, f[20];
char s[maxn];

int main() {
    scanf("%d%s", &n, s);
    for (int i = 1; i <= 9; i++) scanf("%d", f + i);
    for (int i = 0; i < n; i++) {
        if (f[s[i] - '0'] > s[i] - '0') {
            for (; i < n; i++) {
                if (f[s[i] - '0'] >= s[i] - '0') {
                    s[i] = f[s[i] - '0'] + '0';
                } else break;
            }
            break;
        }
    }
    cout << s;
    return 0;
}