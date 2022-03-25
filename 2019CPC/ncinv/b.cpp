#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <map>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 100000 + 5;

int n, q, a[maxn];

int main() {
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i++) scanf("%d", a + i);
    char op[2]; int x;
    map<int,int> mp1, mp2;
    while (q--) {
        scanf("%s%d", op, &x);
        if (op[0] == '>') {
            mp1[x]++;
        } else {
            mp2[x]++;
        }
    }
    auto it = mp1.begin(), lit = mp1.begin(); it++;
    for (; it != mp1.end(); it++, lit++) {
        it->second += lit->second;
    }
    auto it2 = mp2.rbegin(), lit2 = mp2.rbegin(); it++;
    for (; it2 != mp2.rend(); it2++, lit2++) {
        it2->second += lit2->second;
    }
    for (int i = 1; i <= n; i++) {
        
    }
    return 0;
}