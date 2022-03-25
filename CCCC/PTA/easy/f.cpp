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
const int maxn = 100000 + 5;

int n, a, b;
char s[maxn];

int main() {
    scanf("%d", &n);
    while (n--) {
        scanf("%s%d%d", s, &a, &b);
        if (a < 15 || a > 20 || b < 50 || b > 70) puts(s);
    }
    return 0;
}