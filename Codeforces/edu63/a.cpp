#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <string>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 100000 + 5;

int n; string s;

int main() {
    cin >> n >> s;
    int flag = 0;
    for (int i = 1; i < n; i++) {
        if (s[i] < s[i - 1]) {
            flag = i; break;
        }
    }
    if (!flag) puts("NO");
    else {
        puts("YES");
        printf("%d %d", flag, flag + 1);
    }
    return 0;
}