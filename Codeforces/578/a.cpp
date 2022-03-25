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
const int maxn = 100000 + 5;

char s[maxn];
int n, vis[20];

int main() {
    scanf("%d%s", &n, s + 1);
    for (int i = 1; i <= n; i++) {
        if (s[i] == 'L') {
            for (int j = 0; j < 10; j++) if (!vis[j]) {
                vis[j] = 1; break;
            }
        } else if (s[i] == 'R') {
            for (int j = 9; i >= 0; j--) if (!vis[j]) {
                vis[j] = 1; break;
            }
        } else {
            vis[s[i] - '0'] = 0;
        }
    }
    for (int i = 0; i < 10; i++) putchar(vis[i] + '0');
    return 0;
}