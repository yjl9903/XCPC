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
const int maxn = 200000 + 5;

char s[maxn];
int cnt[20];

int main() {
    scanf("%s", s + 1);
    for (int i = 1; s[i]; i++) cnt[s[i] - '0']++;
    int ans = min(cnt[1] / 3, min(cnt[4] / 2, cnt[5]));
    cout << ans;
    return 0;
}