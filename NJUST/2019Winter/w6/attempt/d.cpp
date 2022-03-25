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
    if (n - cnt1 > c) ans[0] = 1;

    int s1 = 0;
    for (int i = 0; i < n && s1 < c - 1; i++) {
        if (s[i] != '0') vis[i] = 1, s1++;
    }
    for (int i = 0; i < n && s1 < n - 2; i++) {
        if (s[i] == '0') vis[i] = 1, s1++;
    }
    string str;
    for (int i = 0; i < n && (int)str.length() < 2; i++) if (!vis[i]) str += s[i];
    if (str == "??" || str == "10") ans[2] = 1;
    if (str[0] == '?' && str[1] == '0') ans[2] = 1;
    if (str[0] == '1' && str[1] == '?') ans[2] = 1;

    ms(vis, 0);
    int s2 = 0;
    for (int i = 0; i < n && s2 < c - 1; i++) {
        if (s[i] == '1') vis[i] = 1, s2++;
    }
    for (int i = 0; i < n && s2 < n - 2; i++) {
        if (s[i] != '1') vis[i] = 1, s2++;
    }
    str.clear();
    for (int i = 0; i < n && (int)str.length() < 2; i++) if (!vis[i]) str += s[i];
    if (str == "??" || str == "01") ans[1] = 1;
    if (str[0] == '?' && str[1] == '1') ans[1] = 1;
    if (str[0] == '0' && str[1] == '?') ans[1] = 1;

    if (ans[0]) puts("00");
    if (ans[1]) puts("01");
    if (ans[2]) puts("10");
    if (ans[3]) puts("11");
    return 0;
}