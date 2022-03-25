#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <string>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int mod = 998244353;
const int maxn = 200000 + 5;

int n; char s[maxn];
int ans[5], vis[maxn];

int main(){
    scanf("%s", s); n = strlen(s);
    int cnt1 = 0, cnt2 = 0, c = n / 2 + n % 2;
    for (int i = 0; i < n; i++) if (s[i] == '1') cnt1++; else if (s[i] == '?') cnt2++;
    if (cnt1 + cnt2 > c) ans[3] = 1;
    if (n - cnt1 > n / 2) ans[0] = 1;

    if (cnt1 + cnt2 >= c && n - cnt1 >= n / 2) {
        if (s[n - 1] == '0') {
            ans[2] = 1;
        }
        if (s[n - 1] == '1') {
            ans[1] = 1;
        }
        if (s[n - 1] == '?') {
            if (cnt1 < c) ans[1] = 1;
            if (n - cnt1 - cnt2 < n / 2) ans[2] = 1;
        }
    }
    // if (cnt1 + cnt2 >= c && n - cnt1 >= n / 2 && s[n - 1] != '1') ans[2] = 1;
    // if (cnt1 + cnt2 >= c && n - cnt1 >= n / 2 && s[n - 1] != '0') ans[1] = 1;

    if (ans[0]) puts("00");
    if (ans[1]) puts("01");
    if (ans[2]) puts("10");
    if (ans[3]) puts("11");
    return 0;
}