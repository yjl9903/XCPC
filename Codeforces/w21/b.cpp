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

int n;

int main() {
    cin >> n;
    for (int i = 0; 1234567ll * i <= n; i++) {
        int tot = n - 1234567ll * i;
        for (int j = 0; 123456ll * j <= tot; j++) {
            if ((tot - 123456ll * j) % 1234 == 0) return puts("YES"), 0;
        }
    }
    puts("NO");
    return 0;
}