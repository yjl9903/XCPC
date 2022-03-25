#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int mod = 998244353;
const int maxn = 100000 + 5;

int n, k;
char s[maxn];

int main() {
    scanf("%d%d%s", &n, &k, s);
    int mx = -1;
    for (int i = 0; i < n - 1; i++) {
        int flag = 1;
        for (int j = 0; j <= i; j++) {
            if (s[j] != s[n - 1 - i + j]) flag = 0;
        }
        if (flag) mx = i;
    }
    for (int i = 0; i <= mx; i++) putchar(s[i]);
    for (int i = 0; i < k; i++) printf("%s", s + mx + 1);
    // cout << mx << endl;
    return 0;
}