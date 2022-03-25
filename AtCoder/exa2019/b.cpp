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

int n; char s[maxn];

int main() {
    cin >> n >> s + 1;
    int c1 = 0, c2 = 0;
    for (int i = 1; i <= n; i++) if (s[i] == 'R') c1++; else c2++;
    if (c1 > c2) puts("Yes");
    else puts("No");
    return 0;
}