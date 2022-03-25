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

struct node {
    vector<int> v;
    bool operator<(const node& b) {
        for (int i = 0; i < 26; i++) if (v[i] < b.v[i]) return 1;
        return 0;
    }
} a[maxn];

int n, q, cnt[30];
char s[maxn], t[maxn];

int main() {
    scanf("%d%s%d", &n, s + 1, &q);
    for (int i = 1; i <= n; i++) {
        cnt[s[i] - 'a']++;
        for (int j = 0; j < 26; j++) a[i].v.push_back(cnt[j]);
    }
    while (q--) {
        scanf("%s", t);
        for (int i = 0; i < 26; i++) cnt[i] = 0;
        for (int i = 0; t[i]; i++) cnt[t[i] - 'a']++;
        node que;
        for (int i = 0; i < 26; i++) que.v.push_back(cnt[i]);
        int rk = lower_bound(a + 1, a + 1 + n, que) - a;
        printf("%d\n", rk);
    }
    return 0;
}