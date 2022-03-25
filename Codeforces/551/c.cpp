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

int n; char s[maxn], ans[maxn];

int main() {
    scanf("%d%s", &n, s + 1);
    if (n % 2) return puts(":("), 0;
    int c = 0, l = 0;
    for (int i = 1; i <= n; i++) if (s[i] == '(') l++;
    for (int i = 1; i <= n; i++) {
        ans[i] = s[i];
        if (s[i] == '(') c++;
        else if (s[i] == ')') c--;
        else {
            if (l < n / 2) {
                ans[i] = '('; l++; c++;
            } else {
                ans[i] = ')'; c--;
            }
        }
        if (i < n && c <= 0) return puts(":("), 0;
    }
    if (c <= 0) cout << ans + 1 << endl;
    else puts(":(");
    return 0;
}