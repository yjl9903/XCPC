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

int n, fail[maxn], cnt[maxn]; char s[maxn];

int main() {
    scanf("%s", s + 1);
    n = strlen(s + 1);
    for (int i = 2; i <= n; i++) {
        int cur = fail[i - 1];
        while (cur && s[cur + 1] != s[i]) cur = fail[cur];
        if (s[cur + 1] == s[i]) cur++;
        fail[i] = cur;
    }
    for (int i = n; i >= 1; i--) {
        cnt[i]++; cnt[fail[i]] += cnt[i];
    }
    vector<int> v;
    int tot = n;
    while (tot) {
        v.push_back(tot); tot = fail[tot];
    }
    reverse(v.begin(), v.end());
    printf("%d\n", (int)v.size());
    for (int p: v) {
        printf("%d %d\n", p, cnt[p]);
    }
    return 0;
}