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

char s[100], t[100];

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        int a,b,c,y,m,d;
        scanf("%d-%d-%d %d:%d:%d", &y, &m, &d, &a, &b, &c);
        if (y < 2050) {
            int sum = 3600 - b * 60 - c + 100000;
            printf("%d\n", sum % 100);
        } else {
            int sum = b * 60 + c;
            printf("%d\n", sum % 100);    
        }
    }
    return 0;
}